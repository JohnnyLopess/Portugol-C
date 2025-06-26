#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "simbolos.h"
#include "tipos.h"

extern int escopo_atual;

AST* ast_cria(ASTTipo tipo, char* valor, int n_filhos, ...) {
    printf("[DEBUG] Criando nó tipo=%d, valor=%s, n_filhos=%d\n", tipo, valor ? valor : "NULL", n_filhos);
    AST* no = malloc(sizeof(AST));
    no->tipo = tipo;
    no->tipo_expr = -1; // Inicializa tipo de expressão como indefinido
    no->valor = valor ? strdup(valor) : NULL;
    no->n_filhos = n_filhos;
    no->filhos = n_filhos > 0 ? malloc(sizeof(AST*) * n_filhos) : NULL;
    va_list args;
    va_start(args, n_filhos);
    for (int i = 0; i < n_filhos; i++) {
        no->filhos[i] = va_arg(args, AST*);
        if (!no->filhos[i]) {
            printf("[ERRO] Filho %d nulo em nó tipo=%d\n", i, tipo);
        }
    }
    va_end(args);
    return no;
}

void ast_libera(AST* no) {
    if (!no) return;
    for (int i = 0; i < no->n_filhos; i++)
        ast_libera(no->filhos[i]);
    free(no->filhos);
    free(no->valor);
    free(no);
}

void ast_gera_c(AST *no, FILE *saida, int nivel_indent)
{
    if (!no)
    {
        fprintf(stderr, "[ERRO] Nó AST nulo em ast_gera_c!\n");
        return;
    }

    switch (no->tipo)
    {
        case AST_PROGRAMA:
            fprintf(saida, "#include <stdio.h>\n\n");
            // Se tiver funções, gere-as antes do main
            if (no->n_filhos > 1) { // Alterado de == 2 para > 1
                ast_gera_c(no->filhos[0], saida, 0); // funções
                fprintf(saida, "int main() {\n");
                ast_gera_c(no->filhos[1], saida, 1); // bloco principal
                fprintf(saida, "    return 0;\n}\n");
            } else {
                fprintf(saida, "int main() {\n");
                ast_gera_c(no->filhos[0], saida, 1); // bloco principal
                fprintf(saida, "    return 0;\n}\n");
            }
            break;

        case AST_BLOCO:
            escopo_atual++;
            for (int i = 0; i < no->n_filhos; i++) {
                if (!no->filhos[i]) continue;
                ast_gera_c(no->filhos[i], saida, nivel_indent);
            }
            escopo_atual--;
            break;

        case AST_DECLARACAO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos == 2 && no->filhos[1]->tipo == AST_ATRIBUICAO) {
                // Declaração com inicialização
                fprintf(saida, "%s %s = ", no->filhos[0]->valor, no->filhos[1]->filhos[0]->valor);
                ast_gera_c(no->filhos[1]->filhos[1], saida, 0);
                fprintf(saida, ";\n");
            } else {
                // Declaração simples
                fprintf(saida, "%s ", no->filhos[0]->valor);
                for (int i = 0; i < no->filhos[1]->n_filhos; i++) {
                    fprintf(saida, "%s", no->filhos[1]->filhos[i]->valor);
                    if (i < no->filhos[1]->n_filhos - 1) fprintf(saida, ", ");
                }
                fprintf(saida, ";\n");
            }
            break;

        case AST_LEITURA:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 1 && no->filhos[0]) {
                char *nome = no->filhos[0]->valor;
                Simbolo *s = buscarSimbolo(no->filhos[0]->valor, escopo_atual);
                int tipo = s ? s->tipo : 0;
                if (tipo == 0)
                    fprintf(saida, "scanf(\"%%d\", &%s);\n", nome);
                else if (tipo == 1)
                    fprintf(saida, "scanf(\"%%f\", &%s);\n", nome);
                else if (tipo == 2)
                    fprintf(saida, "scanf(\" %%c\", &%s);\n", nome); // espaço antes do %c
                else
                    fprintf(saida, "scanf(\"%%d\", &%s);\n", nome); // padrão seguro
            }
            break;

        case AST_ESCRITA:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 1 && no->filhos[0]) {
                if (no->filhos[0]->tipo == AST_STRING) {
                    fprintf(saida, "printf(%s);\n", no->filhos[0]->valor);
                } else {
                    // Usa o tipo propagado na AST
                    int tipo = no->filhos[0]->tipo_expr;
                    if (tipo == TIPO_FLOAT)
                        fprintf(saida, "printf(\"%%f\\n\", ");
                    else if (tipo == TIPO_CHAR)
                        fprintf(saida, "printf(\"%%c\\n\", ");
                    else
                        fprintf(saida, "printf(\"%%d\\n\", ");
                    ast_gera_c(no->filhos[0], saida, 0);
                    fprintf(saida, ");\n");
                }
            }
            break;

        case AST_ATRIBUICAO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1]) {
                fprintf(saida, "%s = ", no->filhos[0]->valor);
                ast_gera_c(no->filhos[1], saida, 0);
                fprintf(saida, ";\n");
            }
            break;

        case AST_IF:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1]) {
                fprintf(saida, "if (");
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, ") {\n");
                ast_gera_c(no->filhos[1], saida, nivel_indent + 1);
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "}");
                if (no->n_filhos > 2 && no->filhos[2]) { // Bloco ELSE ou ELSE IF
                    if (no->filhos[2]->tipo == AST_IF) { // É um "else if"
                        fprintf(saida, " else ");
                        ast_gera_c(no->filhos[2], saida, nivel_indent); // Não adiciona indentação extra aqui, pois o IF interno já se encarrega
                    } else { // É um "else" simples
                        fprintf(saida, " else {\n");
                        ast_gera_c(no->filhos[2], saida, nivel_indent + 1);
                        for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                        fprintf(saida, "}");
                    }
                }
                fprintf(saida, "\n");
            }
            break;

        case AST_WHILE:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1]) {
                fprintf(saida, "while (");
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, ") {\n");
                ast_gera_c(no->filhos[1], saida, nivel_indent + 1);
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "}\n");
            }
            break;

            case AST_FOR:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 4 && no->filhos[0] && no->filhos[1] && no->filhos[2] && no->filhos[3]) {
                fprintf(saida, "for (");
                if (no->filhos[0]->tipo == AST_DECLARACAO &&
                    no->filhos[0]->n_filhos == 2 &&
                    no->filhos[0]->filhos[1]->tipo == AST_ATRIBUICAO) {

                    AST* type_node = no->filhos[0]->filhos[0]; // AST_TIPO node (e.g., "int")
                    AST* assign_node = no->filhos[0]->filhos[1]; // AST_ATRIBUICAO node
                    AST* id_node_in_assign = assign_node->filhos[0]; // AST_ID node (variable name)
                    AST* init_expr_node = assign_node->filhos[1]; // Expression node for initial value

                    // Print type
                    if (type_node && type_node->valor) {
                        fprintf(saida, "%s ", type_node->valor);
                    } else {
                         // Default to "int" if type is not found (shouldn't happen with proper parsing)
                         fprintf(saida, "int ");
                    }

                    // Print variable name
                    if (id_node_in_assign && id_node_in_assign->valor) {
                        fprintf(saida, "%s = ", id_node_in_assign->valor);
                    } else {
                        fprintf(stderr, "[ERRO] ID não encontrado na inicialização do FOR.\n");
                    }

                    // Print initial expression
                    ast_gera_c(init_expr_node, saida, 0); // Generate the expression (e.g., "0")

                } else {
                    fprintf(stderr, "[ERRO] Formato inesperado para a inicialização do loop 'para'.\n");
                    ast_gera_c(no->filhos[0], saida, 0);
                }

                fprintf(saida, "; ");
                // Condition part
                ast_gera_c(no->filhos[1], saida, 0);
                fprintf(saida, "; ");

                // Increment/Decrement part: gera inline sem indentação e sem ';' ou nova linha
                ast_gera_c(no->filhos[2], saida, -1); 
                fprintf(saida, ") {\n");

                // Body of the loop
                ast_gera_c(no->filhos[3], saida, nivel_indent + 1); // Generate the block content
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "}\n");
            }
            break;

        case AST_EXPRESSAO:
            if (no->valor && strcmp(no->valor, "return") == 0) {
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "return ");
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, ";\n");
            } else if (no->n_filhos == 2 && no->filhos[0] && no->filhos[1]
                    && no->filhos[0]->tipo == AST_ID && no->valor == NULL) {
                // Chamada de função em expressão: ID + lista_args
                fprintf(saida, "%s(", no->filhos[0]->valor);
                AST *args = no->filhos[1];
                for (int i = 0; i < args->n_filhos; i++) {
                    if (i > 0) fprintf(saida, ", ");
                    ast_gera_c(args->filhos[i], saida, 0);
                }
                fprintf(saida, ")");
            } else if (no->n_filhos == 1 && no->filhos[0]) {
                ast_gera_c(no->filhos[0], saida, 0);
            } else if (no->n_filhos == 2 && no->filhos[0] && no->filhos[1]) {
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, " %s ", no->valor);
                ast_gera_c(no->filhos[1], saida, 0);
            }
            break;

        case AST_NUM:
        case AST_ID:
            if (no->valor)
                fprintf(saida, "%s", no->valor);
            break;

        case AST_STRING:
            if (no->valor)
                fprintf(saida, "%s", no->valor);
            break;

        case AST_FUNCAO: {
            // Busca símbolo da função para pegar tipo de retorno e parâmetros
            Simbolo *s = buscarSimbolo(no->valor, 0); // escopo global
            const char *tipo_str = "int";
            if (s) {
                if (s->tipo_retorno == 0) tipo_str = "int";
                else if (s->tipo_retorno == 1) tipo_str = "float";
                else if (s->tipo_retorno == 2) tipo_str = "char";
                else if (s->tipo_retorno == 4) tipo_str = "void";
            }
            fprintf(saida, "%s %s(", tipo_str, no->valor);
            // Parâmetros
            for (int i = 0; i < no->filhos[0]->n_filhos; i++) {
                if (i > 0) fprintf(saida, ", ");
                AST *param = no->filhos[0]->filhos[i];
                Simbolo *sp = buscarSimbolo(param->valor, escopo_atual+1); // Parâmetros estão no escopo da função
                const char *param_tipo = "int";
                if (sp) {
                    if (sp->tipo == 0) param_tipo = "int";
                    else if (sp->tipo == 1) param_tipo = "float";
                    else if (sp->tipo == 2) param_tipo = "char";
                    else if (sp->tipo == 3) param_tipo = "bool";
                    else if (sp->tipo == 4) param_tipo = "void";
                }
                if (sp && sp->referencia)
                    fprintf(saida, "%s *%s", param_tipo, param->valor); // por referência
                else
                    fprintf(saida, "%s %s", param_tipo, param->valor);  // por valor
            }
            fprintf(saida, ") {\n");
            ast_gera_c(no->filhos[1], saida, 1); // corpo da função
            fprintf(saida, "}\n");
            break;
        }
        case AST_CHAMADA_FUNCAO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->valor) {
                fprintf(saida, "%s(", no->valor);
                if (no->n_filhos >= 1 && no->filhos[0]) {
                    for (int i = 0; i < no->filhos[0]->n_filhos; i++) {
                        if (i > 0) fprintf(saida, ", ");
                        ast_gera_c(no->filhos[0]->filhos[i], saida, 0);
                    }
                }
                fprintf(saida, ");\n");
            }
            break;

            case AST_COMENTARIO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->valor) {
                if (strstr(no->valor, "\n")) {
                    fprintf(saida, "/*%s*/\n", no->valor); // Comentário de bloco
                } else {
                    fprintf(saida, "//%s\n", no->valor); // Comentário de linha
                }
            }
            break;

            case AST_ESCOLHA:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            fprintf(saida, "switch(");
            ast_gera_c(no->filhos[0], saida, 0);
            fprintf(saida, ") {\n");
            ast_gera_c(no->filhos[1], saida, nivel_indent + 1);
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            fprintf(saida, "}\n");
            break;
            
        case AST_CASO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            fprintf(saida, "case ");
            ast_gera_c(no->filhos[0], saida, 0);
            fprintf(saida, ":\n");
            ast_gera_c(no->filhos[1], saida, nivel_indent + 1);
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            fprintf(saida, "break;\n");
            break;
            
        case AST_CASO_CONTRARIO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            fprintf(saida, "default:\n");
            ast_gera_c(no->filhos[0], saida, nivel_indent + 1);
            break;

        case AST_INCREMENTO:
            if (nivel_indent >= 0) {
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                if (no->n_filhos >= 1 && no->filhos[0] && no->filhos[0]->tipo == AST_ID) {
                    fprintf(saida, "%s++;\n", no->filhos[0]->valor);
                } else {
                    fprintf(stderr, "[ERRO] Incremento aplicado a não-ID na AST.\n");
                }
            } else {
                if (no->n_filhos >= 1 && no->filhos[0] && no->filhos[0]->tipo == AST_ID) {
                    fprintf(saida, "%s++", no->filhos[0]->valor);
                } else {
                    fprintf(stderr, "[ERRO] Incremento aplicado a não-ID na AST.\n");
                }
            }
            break;

        case AST_DECREMENTO:
            if (nivel_indent >= 0) {
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                if (no->n_filhos >= 1 && no->filhos[0] && no->filhos[0]->tipo == AST_ID) {
                    fprintf(saida, "%s--;\n", no->filhos[0]->valor);
                } else {
                    fprintf(stderr, "[ERRO] Decremento aplicado a não-ID na AST.\n");
                }
            } else {
                if (no->n_filhos >= 1 && no->filhos[0] && no->filhos[0]->tipo == AST_ID) {
                    fprintf(saida, "%s--", no->filhos[0]->valor);
                } else {
                    fprintf(stderr, "[ERRO] Decremento aplicado a não-ID na AST.\n");
                }
            }
            break;

        default:
            for (int i = 0; i < no->n_filhos; i++)
                if (no->filhos[i])
                    ast_gera_c(no->filhos[i], saida, nivel_indent);
    }
}


//Parte destinada a otimização de código

AST* otimiza_ast_propagacao_constantes(AST* no) {
    if (!no) return NULL;

    // Otimiza filhos primeiro
    for (int i = 0; i < no->n_filhos; i++) {
        no->filhos[i] = otimiza_ast_propagacao_constantes(no->filhos[i]);
    }

    // Constant folding para operações aritméticas simples
    if (no->tipo == AST_EXPRESSAO && no->n_filhos == 2 && no->filhos[0] && no->filhos[1]) {
        AST *esq = no->filhos[0];
        AST *dir = no->filhos[1];
        if (esq->tipo == AST_NUM && dir->tipo == AST_NUM && no->valor) {
            int v1 = atoi(esq->valor);
            int v2 = atoi(dir->valor);
            int resultado = 0;
            int pode_otimizar = 1;

            if (strcmp(no->valor, "+") == 0) resultado = v1 + v2;
            else if (strcmp(no->valor, "-") == 0) resultado = v1 - v2;
            else if (strcmp(no->valor, "*") == 0) resultado = v1 * v2;
            else if (strcmp(no->valor, "/") == 0 && v2 != 0) resultado = v1 / v2;
            else pode_otimizar = 0;

            if (pode_otimizar) {
                ast_libera(esq);
                ast_libera(dir);
                free(no->filhos);

                char buf[32];
                sprintf(buf, "%d", resultado);
                free(no->valor);
                no->valor = strdup(buf);
                no->tipo = AST_NUM;
                no->n_filhos = 0;
                no->filhos = NULL;
                printf("[DEBUG] Redução de constante: %d %s %d = %d\n", v1, no->valor, v2, resultado);
            }
        }
    }
    return no;
}


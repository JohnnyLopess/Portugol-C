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

    // String temporária para construir o formato da printf
    char format_buffer[1024] = "";
    int format_len = 0;
    // Flag para controlar se precisa de vírgula antes dos argumentos
    int needs_comma_for_args = 0;

    switch (no->tipo)
    {
        case AST_PROGRAMA:
            // Adiciona includes necessários, como string.h para strcpy
            fprintf(saida, "#include <stdio.h>\n");
            fprintf(saida, "#include <string.h>\n\n"); // <-- Adicionado
            if (no->n_filhos > 1) {
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, "int main() {\n");
                ast_gera_c(no->filhos[1], saida, 1);
                fprintf(saida, "    return 0;\n}\n");
            } else {
                fprintf(saida, "int main() {\n");
                ast_gera_c(no->filhos[0], saida, 1);
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
            
            char* tipo_portugol = no->filhos[0]->valor;
            AST* decl_content = no->filhos[1];

            char c_type[20];
            int is_cadeia = (strcmp(tipo_portugol, "cadeia") == 0);

            if (is_cadeia) strcpy(c_type, "char");
            else if (strcmp(tipo_portugol, "real") == 0) strcpy(c_type, "float");
            else strcpy(c_type, tipo_portugol);

            fprintf(saida, "%s ", c_type);

            if (decl_content->tipo == AST_ATRIBUICAO) {
                fprintf(saida, "%s", decl_content->filhos[0]->valor);
                if (is_cadeia) fprintf(saida, "[256]"); // Declara como array
                fprintf(saida, " = ");
                ast_gera_c(decl_content->filhos[1], saida, 0);
            } else if (decl_content->tipo == AST_BLOCO) {
                for (int i = 0; i < decl_content->n_filhos; i++) {
                    if (i > 0) fprintf(saida, ", ");
                    AST* item = decl_content->filhos[i];

                    if (item->tipo == AST_ID) {
                        fprintf(saida, "%s", item->valor);
                        if (is_cadeia) fprintf(saida, "[256]");
                    } else if (item->tipo == AST_ATRIBUICAO) {
                        fprintf(saida, "%s", item->filhos[0]->valor);
                        if (is_cadeia) fprintf(saida, "[256]");
                        fprintf(saida, " = ");
                        ast_gera_c(item->filhos[1], saida, 0);
                    }
                }
            }
            fprintf(saida, ";\n");
            break;

        case AST_LEITURA:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 1 && no->filhos[0]) {
                if (no->filhos[0]->tipo == AST_VETOR_ACESSO) {
                    // Leitura de elemento de vetor
                    char *nome = no->filhos[0]->filhos[0]->valor;
                    Simbolo *s = buscarSimbolo(nome, escopo_atual);
                    int tipo = s ? s->tipo : 0;
                    if (tipo == 0)
                        fprintf(saida, "scanf(\"%%d\", &");
                    else if (tipo == 1)
                        fprintf(saida, "scanf(\"%%f\", &");
                    else if (tipo == 2)
                        fprintf(saida, "scanf(\" %%c\", &"); // espaço antes do %c
                    else
                        fprintf(saida, "scanf(\"%%d\", &"); // padrão seguro
                    ast_gera_c(no->filhos[0], saida, 0);
                    fprintf(saida, ");\n");
                } else {
                    // Leitura de variável normal
                    char *nome = no->filhos[0]->valor;
                    Simbolo *s = buscarSimbolo(nome, escopo_atual);
                    int tipo = s ? s->tipo : -1;

                    switch (tipo) {
                        case TIPO_INT:
                            fprintf(saida, "scanf(\"%%d\", &%s);\n", nome);
                            break;
                        case TIPO_FLOAT:
                            fprintf(saida, "scanf(\"%%f\", &%s);\n", nome);
                            break;
                        case TIPO_CHAR:
                            fprintf(saida, "scanf(\" %%c\", &%s);\n", nome);
                            break;
                        case TIPO_CAD:
                            // Para strings em C (arrays de char), não se usa '&' com scanf
                            fprintf(saida, "scanf(\"%%s\", %s);\n", nome);
                            break;
                        default:
                            fprintf(saida, "scanf(\"%%d\", &%s);\n", nome); // Padrão seguro
                            break;
                    }
                }
            }
            break;

            case AST_ESCRITA:  // Refatorado para suportar 'cadeia'
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "printf(");

                AST* args_block = no->filhos[0];
                if (args_block && args_block->tipo == AST_BLOCO) {
                    strncat(format_buffer, "\"", sizeof(format_buffer) - strlen(format_buffer) - 1);

                    int tem_variavel = 0; // Flag para verificar se há variáveis no printf

                    for (int i = 0; i < args_block->n_filhos; i++) {
                        AST* arg = args_block->filhos[i];
                        if (arg->tipo == AST_STRING) {
                            // Adiciona a string literal ao buffer
                            char* temp_str = strdup(arg->valor);
                            if (temp_str[0] == '"') { // Remove aspas externas
                                temp_str[strlen(temp_str) - 1] = '\0';
                                strncat(format_buffer, temp_str + 1, sizeof(format_buffer) - strlen(format_buffer) - 1);
                            } else {
                                strncat(format_buffer, temp_str, sizeof(format_buffer) - strlen(format_buffer) - 1);
                            }
                            free(temp_str);
                        } else {
                            // Adiciona o especificador de formato para variáveis
                            int tipo = arg->tipo_expr;
                            if (arg->tipo == AST_ID) {
                                Simbolo* s = buscarSimbolo(arg->valor, escopo_atual);
                                if (s) tipo = s->tipo;
                            } else if (arg->tipo == AST_NUM) {
                                tipo = (strchr(arg->valor, '.') != NULL) ? TIPO_FLOAT : TIPO_INT;
                            }

                            if (tipo == TIPO_FLOAT) strncat(format_buffer, "%f", sizeof(format_buffer) - strlen(format_buffer) - 1);
                            else if (tipo == TIPO_CAD) strncat(format_buffer, "%s", sizeof(format_buffer) - strlen(format_buffer) - 1);
                            else if (tipo == TIPO_CHAR) strncat(format_buffer, "%c", sizeof(format_buffer) - strlen(format_buffer) - 1);
                            else if (tipo == TIPO_BOOL) strncat(format_buffer, "%d", sizeof(format_buffer) - strlen(format_buffer) - 1);
                            else strncat(format_buffer, "%d", sizeof(format_buffer) - strlen(format_buffer) - 1);

                            tem_variavel = 1; // Marca que há uma variável
                        }
                    }

                    // Adiciona \n ao final apenas se houver variáveis
                    if (tem_variavel) {
                        strncat(format_buffer, "\\n", sizeof(format_buffer) - strlen(format_buffer) - 1);
                    }

                    strncat(format_buffer, "\"", sizeof(format_buffer) - strlen(format_buffer) - 1);
                    fprintf(saida, "%s", format_buffer);

                    // Gera os argumentos (variáveis) para o printf
                    int first_arg_printed = 0;
                    for (int i = 0; i < args_block->n_filhos; i++) {
                        if (args_block->filhos[i]->tipo != AST_STRING) {
                            if (!first_arg_printed) {
                                fprintf(saida, ", ");
                                first_arg_printed = 1;
                            } else {
                                fprintf(saida, ", ");
                            }
                            ast_gera_c(args_block->filhos[i], saida, 0);
                        }
                    }
                }
                fprintf(saida, ");\n");
                break;

                case AST_ATRIBUICAO:  // Refatorado para suportar 'cadeia'
                    for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                    if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1]) {
                        Simbolo* s = NULL;
                        if (no->filhos[0]->tipo == AST_ID) {
                            s = buscarSimbolo(no->filhos[0]->valor, escopo_atual);
                        }
        
                        // Se a variável for do tipo cadeia e a expressão for uma string literal,
                        // usamos strcpy para a atribuição.
                        if (s && s->tipo == TIPO_CAD && no->filhos[1]->tipo == AST_STRING) {
                            fprintf(saida, "strcpy(%s, ", no->filhos[0]->valor);
                            ast_gera_c(no->filhos[1], saida, 0);
                            fprintf(saida, ");\n");
                        } else {
                            // Lógica original para outros tipos de atribuição
                            if (no->filhos[0]->tipo == AST_VETOR_ACESSO) {
                                ast_gera_c(no->filhos[0], saida, 0);
                            } else {
                                fprintf(saida, "%s", no->filhos[0]->valor);
                            }
                            fprintf(saida, " = ");
                            ast_gera_c(no->filhos[1], saida, 0);
                            fprintf(saida, ";\n");
                        }
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

                    AST* type_node = no->filhos[0]->filhos[0]; // Nó AST_TIPO (ex: "int")
                    AST* assign_node = no->filhos[0]->filhos[1]; // Nó AST_ATRIBUICAO
                    AST* id_node_in_assign = assign_node->filhos[0]; // Nó AST_ID (nome da variável)
                    AST* init_expr_node = assign_node->filhos[1]; // Nó da expressão para o valor inicial

                    // Imprime o tipo
                    if (type_node && type_node->valor) {
                        fprintf(saida, "%s ", type_node->valor);
                    } else {
                         // Padrão para "int" se o tipo não for encontrado (não deve acontecer com análise correta)
                         fprintf(saida, "int ");
                    }

                    // Imprime o nome da variável
                    if (id_node_in_assign && id_node_in_assign->valor) {
                        fprintf(saida, "%s = ", id_node_in_assign->valor);
                    } else {
                        fprintf(stderr, "[ERRO] ID não encontrado na inicialização do FOR.\n");
                    }

                    // Imprime a expressão inicial
                    ast_gera_c(init_expr_node, saida, 0); // Gera a expressão (ex: "0")

                } else {
                    fprintf(stderr, "[ERRO] Formato inesperado para a inicialização do loop 'para'.\n");
                    ast_gera_c(no->filhos[0], saida, 0);
                }

                fprintf(saida, "; ");
                // Parte da condição
                ast_gera_c(no->filhos[1], saida, 0);
                fprintf(saida, "; ");

                // Parte de incremento/decremento: gera inline sem indentação e sem ';' ou nova linha
                ast_gera_c(no->filhos[2], saida, -1); 
                fprintf(saida, ") {\n");

                // Corpo do loop
                ast_gera_c(no->filhos[3], saida, nivel_indent + 1); // Gera o conteúdo do bloco
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
            } else if (no->n_filhos == 1 && (strcmp(no->valor, "~") == 0 || strcmp(no->valor, "-") == 0) ) { // possível implementação de operador unário negativo
                // Gera código para operador unário ~ ou -
                fprintf(saida, no->valor);
                ast_gera_c(no->filhos[0], saida, 0);
            } else if (no->n_filhos == 1 && no->filhos[0]) {
                ast_gera_c(no->filhos[0], saida, 0);
            } else if (no->n_filhos == 2 && no->filhos[0] && no->filhos[1]) {
                ast_gera_c(no->filhos[0], saida, 0);
                fprintf(saida, " %s ", no->valor);
                ast_gera_c(no->filhos[1], saida, 0);
            }
            break;
        case AST_AND: // Adicionado para AND lógico
            ast_gera_c(no->filhos[0], saida, 0);
            fprintf(saida, " && ");
            ast_gera_c(no->filhos[1], saida, 0);
            break;
        case AST_OR: // Adicionado para OR lógico
            ast_gera_c(no->filhos[0], saida, 0);
            fprintf(saida, " || ");
            ast_gera_c(no->filhos[1], saida, 0);
            break;
        case AST_NOT: // Adicionado para NOT lógico
            fprintf(saida, "!");
            ast_gera_c(no->filhos[0], saida, 0);
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

        case AST_VETOR_DECLARACAO:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 3 && no->filhos[0] && no->filhos[1] && no->filhos[2]) {
                // Filhos: [0] = tipo, [1] = nome, [2] = tamanho
                fprintf(saida, "%s %s[%s];\n", 
                       no->filhos[0]->valor,     // tipo (int, float, char)
                       no->filhos[1]->valor,     // nome do vetor
                       no->filhos[2]->valor);    // tamanho
            }
            break;

        case AST_VETOR_ACESSO:
            if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1]) {
                // Filhos: [0] = nome do vetor, [1] = índice
                fprintf(saida, "%s[", no->filhos[0]->valor);
                ast_gera_c(no->filhos[1], saida, 0);
                fprintf(saida, "]");
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
            // Verifica operações com ponto flutuante
            if (esq->tipo_expr == TIPO_FLOAT || dir->tipo_expr == TIPO_FLOAT) {
                float v1 = atof(esq->valor);
                float v2 = atof(dir->valor);
                float resultado_f = 0.0f;
                int pode_otimizar_f = 1;

                if (strcmp(no->valor, "+") == 0) resultado_f = v1 + v2;
                else if (strcmp(no->valor, "-") == 0) resultado_f = v1 - v2;
                else if (strcmp(no->valor, "*") == 0) resultado_f = v1 * v2;
                else if (strcmp(no->valor, "/") == 0 && v2 != 0) resultado_f = v1 / v2;
                else pode_otimizar_f = 0;

                if (pode_otimizar_f) {
                    ast_libera(esq);
                    ast_libera(dir);
                    free(no->filhos);

                    char buf[64]; // Aumenta o tamanho do buffer para floats
                    sprintf(buf, "%f", resultado_f);
                    free(no->valor);
                    no->valor = strdup(buf);
                    no->tipo = AST_NUM;
                    no->tipo_expr = TIPO_FLOAT;
                    no->n_filhos = 0;
                    no->filhos = NULL;
                    printf("[DEBUG] Redução de constante float: %f %s %f = %f\n", v1, no->valor, v2, resultado_f);
                    return no;
                }
            } else { // Operações com inteiros
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
                    no->tipo_expr = TIPO_INT;
                    no->n_filhos = 0;
                    no->filhos = NULL;
                    printf("[DEBUG] Redução de constante int: %d %s %d = %d\n", v1, no->valor, v2, resultado);
                    return no;
                }
            }
        }
    }
    if ((no->tipo == AST_AND || no->tipo == AST_OR) && no->n_filhos == 2 && no->filhos[0] && no->filhos[1]) {
        AST *esq = no->filhos[0];
        AST *dir = no->filhos[1];
        if (esq->tipo == AST_NUM && dir->tipo == AST_NUM) { // Assumindo 0 para falso, diferente de zero para verdadeiro
            int v1 = atoi(esq->valor);
            int v2 = atoi(dir->valor);
            int resultado_logico = 0;
            if (no->tipo == AST_AND) {
                resultado_logico = v1 && v2;
                printf("[DEBUG] Redução de constante lógica AND: %d && %d = %d\n", v1, v2, resultado_logico);
            } else if (no->tipo == AST_OR) {
                resultado_logico = v1 || v2;
                printf("[DEBUG] Redução de constante lógica OR: %d || %d = %d\n", v1, v2, resultado_logico);
            }
            ast_libera(esq);
            ast_libera(dir);
            free(no->filhos);

            char buf[32];
            sprintf(buf, "%d", resultado_logico);
            free(no->valor);
            no->valor = strdup(buf);
            no->tipo = AST_NUM;
            no->tipo_expr = TIPO_BOOL;
            no->n_filhos = 0;
            no->filhos = NULL;
            return no;
        }
    } else if (no->tipo == AST_NOT && no->n_filhos == 1 && no->filhos[0]) {
        AST *operand = no->filhos[0];
        if (operand->tipo == AST_NUM) {
            int v = atoi(operand->valor);
            int resultado_logico = !v;
            printf("[DEBUG] Redução de constante lógica NOT: !%d = %d\n", v, resultado_logico);
            ast_libera(operand);
            free(no->filhos);

            char buf[32];
            sprintf(buf, "%d", resultado_logico);
            free(no->valor);
            no->valor = strdup(buf);
            no->tipo = AST_NUM;
            no->tipo_expr = TIPO_BOOL;
            no->n_filhos = 0;
            no->filhos = NULL;
            return no;
        }
    }


    return no;
}

AST* otimiza_ast_dead_code(AST* no) {
    if (!no) return NULL;

    // Otimiza filhos primeiro
    for (int i = 0; i < no->n_filhos; i++) {
        no->filhos[i] = otimiza_ast_dead_code(no->filhos[i]);
    }

    // 1. Remove comandos após 'return' em blocos
    if (no->tipo == AST_BLOCO && no->n_filhos > 0) {
        int novo_n = no->n_filhos;
        for (int i = 0; i < no->n_filhos; i++) {
            if (no->filhos[i] && no->filhos[i]->tipo == AST_EXPRESSAO && no->filhos[i]->valor && strcmp(no->filhos[i]->valor, "return") == 0) {
                printf("[DEBUG] Removendo código morto após return no bloco\n");
                novo_n = i + 1;
                break;
            }
        }
        if (novo_n < no->n_filhos) {
            // Libera filhos mortos
            for (int i = novo_n; i < no->n_filhos; i++) {
                ast_libera(no->filhos[i]);
            }
            no->n_filhos = novo_n;
            no->filhos = realloc(no->filhos, sizeof(AST*) * novo_n);
        }
    }

    // 2. Remove blocos de if/while com condição constante
    if (no->tipo == AST_IF && no->n_filhos >= 2 && no->filhos[0] && no->filhos[0]->tipo == AST_NUM) {
        int cond = atoi(no->filhos[0]->valor);
        if (cond) {
            // if (true): substitui pelo bloco "then"
            printf("[DEBUG] Removendo if com condição sempre verdadeira.\n");
            AST* bloco = no->filhos[1];
            ast_libera(no->filhos[0]);
            if (no->n_filhos > 2) ast_libera(no->filhos[2]);
            free(no->filhos);
            free(no->valor);
            AST* novo = bloco;
            free(no);
            return novo;
        } else {
            // if (false): substitui pelo bloco "else" se existir, senão remove
            printf("[DEBUG] Removendo if com condição sempre falsa.\n");
            AST* bloco = (no->n_filhos > 2) ? no->filhos[2] : NULL;
            ast_libera(no->filhos[0]);
            ast_libera(no->filhos[1]);
            if (no->n_filhos > 2 && bloco) {
                free(no->filhos);
                free(no->valor);
                AST* novo = bloco;
                free(no);
                return novo;
            } else {
                free(no->filhos);
                free(no->valor);
                free(no);
                return NULL;
            }
        }
    }

    if (no->tipo == AST_WHILE && no->n_filhos >= 2 && no->filhos[0] && no->filhos[0]->tipo == AST_NUM) {
        int cond = atoi(no->filhos[0]->valor);
        if (!cond) {
            // while (false): remove o laço
            printf("[DEBUG] Removendo while com condição sempre falsa.\n");
            ast_libera(no->filhos[0]);
            ast_libera(no->filhos[1]);
            free(no->filhos);
            free(no->valor);
            free(no);
            return NULL;
        }
        // while (true): laço infinito, mantém
    }

    return no;
}

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "simbolos.h"

extern int escopo_atual;

AST* ast_cria(ASTTipo tipo, char* valor, int n_filhos, ...) {
    printf("[DEBUG] Criando nó tipo=%d, valor=%s, n_filhos=%d\n", tipo, valor ? valor : "NULL", n_filhos);
    AST* no = malloc(sizeof(AST));
    no->tipo = tipo;
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

void ast_gera_c(AST* no, FILE* saida, int nivel_indent) {
    if (!no) {
        fprintf(stderr, "[ERRO] Nó AST nulo em ast_gera_c!\n");
        return;
    }

    switch(no->tipo) {
        case AST_PROGRAMA:
            fprintf(saida, "#include <stdio.h>\n\nint main() {\n");
            ast_gera_c(no->filhos[0], saida, 1);
            fprintf(saida, "    return 0;\n}\n");
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
            if (no->n_filhos >= 2 && no->filhos[0] && no->filhos[1])
                fprintf(saida, "%s %s;\n", no->filhos[0]->valor, no->filhos[1]->valor);
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
                    fprintf(saida, "scanf(\"%%d\", &%s);\n", nome); // padrão seguro, sem comentário
            }
            break;

        case AST_ESCRITA:
            for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
            if (no->n_filhos >= 1 && no->filhos[0]) {
                if (no->filhos[0]->tipo == AST_STRING) {
                    fprintf(saida, "printf(%s);\n", no->filhos[0]->valor);
                } else if (no->filhos[0]->tipo == AST_NUM) {
                    fprintf(saida, "printf(\"%%d\\n\", %s);\n", no->filhos[0]->valor);
                } else if (no->filhos[0]->tipo == AST_ID) {
                    Simbolo *s = buscarSimbolo(no->filhos[0]->valor, escopo_atual);
                    int tipo = s ? s->tipo : 0;
                    if (tipo == 0)
                        fprintf(saida, "printf(\"%%d\\n\", %s);\n", no->filhos[0]->valor);
                    else if (tipo == 1)
                        fprintf(saida, "printf(\"%%f\\n\", %s);\n", no->filhos[0]->valor);
                    else if (tipo == 2)
                        fprintf(saida, "printf(\"%%c\\n\", %s);\n", no->filhos[0]->valor);
                    else
                        fprintf(saida, "printf(\"%%d\\n\", %s);\n", no->filhos[0]->valor); 
                } else {
                    ast_gera_c(no->filhos[0], saida, 0);
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
                if (no->n_filhos > 2 && no->filhos[2]) {
                    fprintf(saida, " else {\n");
                    ast_gera_c(no->filhos[2], saida, nivel_indent + 1);
                    for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                    fprintf(saida, "}");
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
                fprintf(saida, "for (%s = ", no->filhos[0]->valor);
                ast_gera_c(no->filhos[1], saida, 0);
                fprintf(saida, "; %s <= ", no->filhos[0]->valor);
                ast_gera_c(no->filhos[2], saida, 0);
                fprintf(saida, "; %s++) {\n", no->filhos[0]->valor);
                ast_gera_c(no->filhos[3], saida, nivel_indent + 1);
                for (int i = 0; i < nivel_indent; i++) fprintf(saida, "    ");
                fprintf(saida, "}\n");
            }
            break;

        case AST_EXPRESSAO:
            if (no->n_filhos == 1 && no->filhos[0]) {
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

        default:
            for (int i = 0; i < no->n_filhos; i++)
                if (no->filhos[i])
                    ast_gera_c(no->filhos[i], saida, nivel_indent);
    }
}


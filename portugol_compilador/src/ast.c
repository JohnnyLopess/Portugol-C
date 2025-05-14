#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

AST* ast_cria(ASTTipo tipo, char* valor, int n_filhos, ...) {
    AST* no = malloc(sizeof(AST));
    no->tipo = tipo;
    no->valor = valor ? strdup(valor) : NULL;
    no->n_filhos = n_filhos;
    no->filhos = n_filhos > 0 ? malloc(sizeof(AST*) * n_filhos) : NULL;
    va_list args;
    va_start(args, n_filhos);
    for (int i = 0; i < n_filhos; i++)
        no->filhos[i] = va_arg(args, AST*);
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


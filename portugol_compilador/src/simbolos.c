#include "simbolos.h"
#include <string.h>

static Variavel tabela[MAX_VARS];
static int num_vars = 0;

void simbolos_init() { num_vars = 0; }

int simbolos_adiciona(const char* nome, int tipo) {
    if (num_vars >= MAX_VARS) return -1;
    strcpy(tabela[num_vars].nome, nome);
    tabela[num_vars].tipo = tipo;
    return num_vars++;
}

int simbolos_busca_tipo(const char* nome) {
    for (int i = 0; i < num_vars; i++)
        if (strcmp(tabela[i].nome, nome) == 0)
            return tabela[i].tipo;
    return -1;
}
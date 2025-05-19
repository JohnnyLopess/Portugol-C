#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#define MAX_VARS 100

typedef struct {
    char nome[50];
    int tipo;
} Variavel;

void simbolos_init();
int simbolos_adiciona(const char* nome, int tipo);
int simbolos_busca_tipo(const char* nome);

#endif
#ifndef SIMBOLOS_H
#define SIMBOLOS_H

typedef struct simbolo {
    char nome[32];
    int tipo; 
    struct simbolo *proximo;
} Simbolo;

void inserirSimbolo(char *nome, int tipo); 
Simbolo *buscarSimbolo(char *nome);
void imprimirTabela();

#endif
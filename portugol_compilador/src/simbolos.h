#ifndef SIMBOLOS_H
#define SIMBOLOS_H

typedef struct simbolo {
    char nome[32];
    int tipo;
    int escopo; //nível de escopo(0 é o globall, 1,2... escopos de funções)
    struct simbolo *proximo;
} Simbolo;

void inserirSimbolo(char *nome, int tipo, int escopo); 
Simbolo *buscarSimbolo(char *nome, int escopo);        
void imprimirTabela();

#endif
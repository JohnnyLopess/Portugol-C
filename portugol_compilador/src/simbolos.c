#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "simbolos.h"

#define TAM 211

Simbolo *tabela[TAM] = {NULL}; // Inicializa a tabela

unsigned hash(char *s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;
    return h % TAM;
}

void inserirSimbolo(char *nome, int tipo, int escopo) {
    unsigned i = hash(nome);
    // Evita inserir duplicatas
    Simbolo *existente = buscarSimbolo(nome, escopo);
    if (existente) return;
    Simbolo *s = malloc(sizeof(Simbolo));
    strncpy(s->nome, nome, sizeof(s->nome));
    s->nome[sizeof(s->nome)-1] = '\0';
    s->tipo = tipo;
    s->escopo = escopo;
    s->proximo = tabela[i];
    tabela[i] = s;
}

Simbolo *buscarSimbolo(char *nome, int escopo) {
    unsigned i = hash(nome);
    // Procura do escopo atual até o global
    for (int e = escopo; e >= 0; e--) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (strcmp(s->nome, nome) == 0 && s->escopo == e)
                return s;
        }
    }
    return NULL;
}

void imprimirTabela() {
    for (int i = 0; i < TAM; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            const char *tipo_str = "desconhecido";
            if (s->tipo == 0) tipo_str = "int";
            else if (s->tipo == 1) tipo_str = "float";
            else if (s->tipo == 2) tipo_str = "char";
            printf("Nome: %s, Tipo: %s\n", s->nome, tipo_str);
        }
    }
}
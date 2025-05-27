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

// Função genérica para inserir qualquer símbolo
Simbolo *criaSimbolo(
    char *nome,
    int tipo,
    int escopo,
    CategoriaSimbolo categoria,
    int inicializada,
    int linha_decl,
    int tipo_retorno,
    int n_parametros,
    Simbolo **parametros,
    int referencia
) {
    unsigned i = hash(nome);
    // Evita duplicatas no mesmo escopo
    Simbolo *existente = buscarSimbolo(nome, escopo);
    if (existente) return NULL;
    Simbolo *s = malloc(sizeof(Simbolo));
    strncpy(s->nome, nome, sizeof(s->nome));
    s->nome[sizeof(s->nome)-1] = '\0';
    s->tipo = tipo;
    s->escopo = escopo;
    s->categoria = categoria;
    s->inicializada = inicializada;
    s->linha_decl = linha_decl;
    s->tipo_retorno = tipo_retorno;
    s->n_parametros = n_parametros;
    s->parametros = parametros;
    s->referencia = referencia;
    s->proximo = tabela[i];
    tabela[i] = s;
    return s;
}

// Função de conveniência para inserir variável
void inserirSimbolo(char *nome, int tipo, int escopo) {
    criaSimbolo(nome, tipo, escopo, SIMBOLO_VARIAVEL, 0, 0, -1, 0, NULL, 0);
}

// Função de conveniência para inserir função
Simbolo *inserirFuncao(char *nome, int tipo_retorno, int escopo, int n_parametros, Simbolo **parametros) {
    return criaSimbolo(nome, -1, escopo, SIMBOLO_FUNCAO, 1, 0, tipo_retorno, n_parametros, parametros, 0);
}

// Função de conveniência para inserir parâmetro
Simbolo *inserirParametro(char *nome, int tipo, int escopo, int referencia) {
    return criaSimbolo(nome, tipo, escopo, SIMBOLO_PARAMETRO, 1, 0, -1, 0, NULL, referencia);
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
            const char *cat_str = "VAR";
            if (s->categoria == SIMBOLO_FUNCAO) cat_str = "FUNCAO";
            else if (s->categoria == SIMBOLO_PARAMETRO) cat_str = "PARAM";
            else if (s->categoria == SIMBOLO_CONST) cat_str = "CONST";
            printf("Nome: %s, Tipo: %s, Escopo: %d, Categoria: %s, Inicializada: %d, Linha: %d\n",
                s->nome, tipo_str, s->escopo, cat_str, s->inicializada, s->linha_decl);
            if (s->categoria == SIMBOLO_FUNCAO) {
                printf("  Retorno: %s, Params: %d\n", 
                    s->tipo_retorno == 0 ? "int" : s->tipo_retorno == 1 ? "float" : s->tipo_retorno == 2 ? "char" : "void",
                    s->n_parametros);
            }
        }
    }
}
#ifndef SIMBOLOS_H
#define SIMBOLOS_H

typedef enum {
    SIMBOLO_VARIAVEL,
    SIMBOLO_FUNCAO,
    SIMBOLO_PARAMETRO,
    SIMBOLO_CONST
} CategoriaSimbolo;

typedef struct simbolo {
    char nome[32];
    int tipo;
    int escopo;
    CategoriaSimbolo categoria; // tipo do símbolo
    int inicializada;           // 1 se já foi inicializada
    int linha_decl;             // linha da declaração
    // Para funções:
    int tipo_retorno;           // se for função
    int n_parametros;           // se for função
    struct simbolo **parametros;// lista de parâmetros (ponteiros para símbolos)
    int referencia;            // 1 se for referência 0 se não for
    struct simbolo *proximo;
} Simbolo;

void inserirSimbolo(char *nome, int tipo, int escopo); 
Simbolo *buscarSimbolo(char *nome, int escopo); 
int buscar_tipo_funcao(char *nome);       
int buscar_tipo_variavel(const char *nome);
void checar_declaracao(const char* nome);
void imprimirTabela();

#endif
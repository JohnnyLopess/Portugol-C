#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "simbolos.h"
#include "tipos.h"

#define TAM 211

extern int escopo_atual;

Simbolo *tabela[TAM] = {NULL}; // Inicializa a tabela

unsigned hash(char *s)
{
    unsigned h = 0;
    while (*s)
        h = (h << 4) + *s++;
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
    int referencia)
{
    unsigned i = hash(nome);
    // Evita duplicatas no mesmo escopo
    Simbolo *existente = buscarSimbolo(nome, escopo);
    if (existente)
        return NULL;
    Simbolo *s = malloc(sizeof(Simbolo));
    strncpy(s->nome, nome, sizeof(s->nome));
    s->nome[sizeof(s->nome) - 1] = '\0';
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
void inserirSimbolo(char *nome, int tipo, int escopo)
{
    criaSimbolo(nome, tipo, escopo, SIMBOLO_VARIAVEL, 0, 0, -1, 0, NULL, 0);
}

// Função de conveniência para inserir função
Simbolo *inserirFuncao(char *nome, int tipo_retorno, int escopo, int n_parametros, Simbolo **parametros)
{
    return criaSimbolo(nome, -1, escopo, SIMBOLO_FUNCAO, 1, 0, tipo_retorno, n_parametros, parametros, 0);
}

// Função de conveniência para inserir parâmetro
Simbolo *inserirParametro(char *nome, int tipo, int escopo, int referencia)
{
    return criaSimbolo(nome, tipo, escopo, SIMBOLO_PARAMETRO, 1, 0, -1, 0, NULL, referencia);
}

Simbolo *buscarSimbolo(char *nome, int escopo)
{
    unsigned i = hash(nome);
    // Procura do escopo atual até o global
    for (int e = escopo; e >= 0; e--)
    {
        for (Simbolo *s = tabela[i]; s; s = s->proximo)
        {
            if (strcmp(s->nome, nome) == 0 && s->escopo == e)
                return s;
        }
    }
    return NULL;
}

int buscar_tipo_funcao(char *nome)
{
    Simbolo *s = buscarSimbolo(nome, 0); // escopo global
    return s ? s->tipo_retorno : TIPO_INT;
}

int buscar_tipo_variavel(const char *nome)
{
    Simbolo *s = buscarSimbolo((char *)nome, escopo_atual);
    if (s)
        return s->tipo;
    return TIPO_INT; // padrão seguro
}

void checar_declaracao(const char *nome)
{
    extern int escopo_atual;
    if (!buscarSimbolo((char *)nome, escopo_atual))
    {
        fprintf(stderr, "[ERRO SEMÂNTICO] Variável '%s' não declarada!\n", nome);
        exit(1);
    }
}

void marcarVariavelInicializada(char *nome, int escopo)
{
    Simbolo *s = buscarSimbolo(nome, escopo);
    if (s)
    {
        if (s->categoria == SIMBOLO_VARIAVEL)
        {
            s->inicializada = 1;
        }
    }
}

void verificar_variaveis()
{
    for (int i = 0; i < TAM; i++)
    {
        for (Simbolo *s = tabela[i]; s; s = s->proximo)
        {
            if (s->inicializada == 0)
            {
                fprintf(stderr, "[ERRO] Variável '%s' não incializada!\n", s->nome);
                exit(1);
            }
        }
    }
}

void imprimirTabela()
{
    for (int i = 0; i < TAM; i++)
    {
        for (Simbolo *s = tabela[i]; s; s = s->proximo)
        {
            const char *tipo_str = "desconhecido";
            if (s->tipo == 0)
                tipo_str = "int";
            else if (s->tipo == 1)
                tipo_str = "float";
            else if (s->tipo == 2)
                tipo_str = "char";
            else if (s->tipo == 5) // <-- Adicionado para o tipo CADEIA
                tipo_str = "cadeia";
                
            const char *cat_str = "VAR";
            if (s->categoria == SIMBOLO_FUNCAO)
                cat_str = "FUNCAO";
            else if (s->categoria == SIMBOLO_PARAMETRO)
                cat_str = "PARAM";
            else if (s->categoria == SIMBOLO_CONST)
                cat_str = "CONST";
            printf("Nome: %s, Tipo: %s, Escopo: %d, Categoria: %s, Inicializada: %d, Linha: %d\n",
                   s->nome, tipo_str, s->escopo, cat_str, s->inicializada, s->linha_decl);
            if (s->categoria == SIMBOLO_FUNCAO)
            {
                printf("  Retorno: %s, Params: %d\n",
                       s->tipo_retorno == 0 ? "int" : s->tipo_retorno == 1 ? "float"
                                                  : s->tipo_retorno == 2   ? "char"
                                                                           : "void",
                       s->n_parametros);
            }
        }
    }
}
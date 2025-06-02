%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "simbolos.h"

int yylex();
void yyerror(const char *s);

FILE *saida;

int escopo_atual = 0;

AST* raiz_ast = NULL;

Simbolo *inserirFuncao(char *nome, int tipo_retorno, int escopo, int n_parametros, Simbolo **parametros);
Simbolo *inserirParametro(char *nome, int tipo, int escopo, int referencia);

#define TIPO_INT 0
#define TIPO_FLOAT 1
#define TIPO_CHAR 2
#define TIPO_BOOL 3
#define TIPO_VOID 4

%}

%union {
    char* str;
    int inteiro;
    struct {
        char* valor;
        int tipo;
    } expr;
    struct AST* ast; // novo campo para AST
}

%token INICIO FIM LEIA ESCREVA VAR
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTERE TIPO_LOGICO TIPO_VAZIO
%token SE SENAO ENTAO FIMSE
%token ENQUANTO FACA FIMENQUANTO
%token IGUAL COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token SOMA SUB MUL DIV
%token ABREPAR FECHAPAR PONTOEVIRGULA
%token PARA DE ATE FIMPARA
%token DOISPONTOS
%token FIMFUNCAO
%token <str> NUM ID STRING
%token FUNCAO RETORNE
%token <str> COMENTARIO_LINHA COMENTARIO_BLOCO
%type <ast> programa  lista_funcoes funcao lista_args args bloco bloco_conteudo comando declaracao leitura escrita atribuicao expressao lista_parametros parametros parametro chamada_funcao
%type <inteiro> tipo
%type <ast> comentario

%left SOMA SUB


%%

programa:
    lista_funcoes INICIO bloco FIM {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 2, $1, $3);
        $$ = raiz_ast;
    }
    | INICIO bloco FIM {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 1, $2);
        $$ = raiz_ast;
    }
;


funcao:
    FUNCAO tipo ID ABREPAR lista_parametros FECHAPAR bloco FIMFUNCAO {
        inserirFuncao($3, $2, escopo_atual, $5->n_filhos, NULL);
        $$ = ast_cria(AST_FUNCAO, strdup($3), 2, $5, $7);
    }   
;

lista_args:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | args { $$ = $1; }
;

args:
    expressao { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | args PONTOEVIRGULA expressao {
        int n = $1->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
        filhos[n-1] = $3;
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        $$ = novo;
    }
;

lista_funcoes:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | lista_funcoes funcao { 
        int n = $1->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
        filhos[n-1] = $2;
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        $$ = novo;
    }
;

bloco:
    {
        escopo_atual++; // Entra em novo escopo
    }
    bloco_conteudo
    {
        escopo_atual--; // Sai do escopo ao final do bloco
        $$ = $2;
    }
;

bloco_conteudo:
    comando { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | bloco_conteudo comando {
        if (!$2) {
            fprintf(stderr, "[ERRO] Comando nulo em bloco!\n");
            $$ = $1;
        } else {
            int n = $1->n_filhos + 1;
            AST** filhos = malloc(sizeof(AST*) * n);
            for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
            filhos[n-1] = $2;
            AST* novo_bloco = ast_cria(AST_BLOCO, NULL, 0);
            novo_bloco->n_filhos = n;
            novo_bloco->filhos = filhos;
            $$ = novo_bloco;
        }
    }
;
comando:
    declaracao { $$ = $1; }
    | leitura { $$ = $1; }
    | escrita { $$ = $1; }
    | atribuicao { $$ = $1; }
    | comentario { $$ = $1; }
    | SE expressao ENTAO bloco SENAO comando FIMSE {
        $$ = ast_cria(AST_IF, NULL, 3, $2, $4, $6);
    }
    | SE expressao ENTAO bloco FIMSE {
        $$ = ast_cria(AST_IF, NULL, 2, $2, $4);
    }
    | ENQUANTO expressao FACA bloco FIMENQUANTO {
        $$ = ast_cria(AST_WHILE, NULL, 2, $2, $4);
    }
    | PARA ID DE expressao ATE expressao FACA bloco FIMPARA {
        AST* id = ast_cria(AST_ID, strdup($2), 0);
        $$ = ast_cria(AST_FOR, NULL, 4, id, $4, $6, $8);
    }
    | RETORNE expressao PONTOEVIRGULA {
        $$ = ast_cria(AST_EXPRESSAO, strdup("return"), 1, $2);
    }
    | chamada_funcao PONTOEVIRGULA { $$ = $1; }
;

chamada_funcao:
    ID ABREPAR lista_args FECHAPAR { $$ = ast_cria(AST_CHAMADA_FUNCAO, strdup($1), 1, $3); }
;

declaracao:
    VAR DOISPONTOS tipo ID PONTOEVIRGULA {
        inserirSimbolo($4, $3, escopo_atual); // Agora inclui o escopo!
        AST* tipo_no = ast_cria(AST_ID, strdup($4), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup($3 == TIPO_INT ? "int" : $3 == TIPO_FLOAT ? "float" : "char"), 0);
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
    | tipo ID PONTOEVIRGULA {
        inserirSimbolo($2, $1, escopo_atual);
        AST* tipo_no = ast_cria(AST_ID, strdup($2), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup($1 == TIPO_INT ? "int" : $1 == TIPO_FLOAT ? "float" : "char"), 0);
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
;

tipo:
    TIPO_INTEIRO     { $$ = TIPO_INT; }
    | TIPO_REAL      { $$ = TIPO_FLOAT; }
    | TIPO_CARACTERE { $$ = TIPO_CHAR; }
    | TIPO_LOGICO    { $$ = TIPO_BOOL; }
    | TIPO_VAZIO     { $$ = TIPO_VOID; }
;

leitura:
    LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        $$ = ast_cria(AST_LEITURA, NULL, 1, id);
    }
;

escrita:
    ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        $$ = ast_cria(AST_ESCRITA, NULL, 1, id);
    }
    | ESCREVA ABREPAR STRING FECHAPAR PONTOEVIRGULA {
        AST* str = ast_cria(AST_STRING, strdup($3), 0);
        $$ = ast_cria(AST_ESCRITA, NULL, 1, str);
    }
    | ESCREVA ABREPAR expressao FECHAPAR PONTOEVIRGULA {
        $$ = ast_cria(AST_ESCRITA, NULL, 1, $3);
    }
    | ESCREVA ABREPAR NUM FECHAPAR PONTOEVIRGULA {
        AST* num = ast_cria(AST_NUM, strdup($3), 0);
        $$ = ast_cria(AST_ESCRITA, NULL, 1, num);
    }
;

atribuicao:
    ID IGUAL expressao PONTOEVIRGULA {
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_ATRIBUICAO, NULL, 2, id, $3);
    }
;

expressao:
    NUM { $$ = ast_cria(AST_NUM, strdup($1), 0); }
    | ID { $$ = ast_cria(AST_ID, strdup($1), 0); }
    | expressao SOMA expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("+"), 2, $1, $3);
    }
    | expressao SUB expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("-"), 2, $1, $3);
    }
    | expressao COMPARA expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("=="), 2, $1, $3);
    }
    | expressao MENOR expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("<"), 2, $1, $3);
    }
    | expressao MAIOR expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup(">"), 2, $1, $3);
    }
    | expressao MENOR_IGUAL expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("<="), 2, $1, $3);
    }
    | expressao MAIOR_IGUAL expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup(">="), 2, $1, $3);
    }
    | expressao DIFERENTE expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("!="), 2, $1, $3);
    }
    | ID ABREPAR lista_args FECHAPAR {
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_EXPRESSAO, NULL, 2, id, $3);
    }
;

lista_parametros:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | parametros { $$ = $1; }
;

parametros:
    parametro { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | parametros PONTOEVIRGULA parametro {
        int n = $1->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
        filhos[n-1] = $3;
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        $$ = novo;
    }
;

parametro:
    tipo ID { inserirParametro($2, $1, escopo_atual, 0); $$ = ast_cria(AST_DECLARACAO, strdup($2), 0); }
    | tipo '&' ID { inserirParametro($3, $1, escopo_atual, 1); $$ = ast_cria(AST_DECLARACAO, strdup($3), 0); }
;

comentario:
    COMENTARIO_LINHA { $$ = ast_cria(AST_COMENTARIO, strdup($1), 0); }
    | COMENTARIO_BLOCO { $$ = ast_cria(AST_COMENTARIO, strdup($1), 0); }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
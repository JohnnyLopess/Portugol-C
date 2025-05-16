%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex();
void yyerror(const char *s);

FILE *saida;

#define MAX_VARS 100

struct variavel {
    char nome[50];
    int tipo;  
};

struct variavel variaveis[MAX_VARS];
int num_vars = 0;

AST* raiz_ast = NULL;

int buscar_tipo_variavel(char *nome) {
    for(int i = 0; i < num_vars; i++) {
        if(strcmp(variaveis[i].nome, nome) == 0) {
            return variaveis[i].tipo;
        }
    }
    return -1;
}

// Add these variable type definitions
#define TIPO_INT 0
#define TIPO_FLOAT 1
#define TIPO_CHAR 2

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
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTERE
%token SE SENAO ENTAO FIMSE
%token ENQUANTO FACA FIMENQUANTO
%token IGUAL COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token SOMA SUB MUL DIV
%token ABREPAR FECHAPAR PONTOEVIRGULA
%token PARA DE ATE FIMPARA
%token DOISPONTOS
%token <str> NUM ID STRING
%type <ast> programa bloco comando declaracao leitura escrita atribuicao expressao
%type <inteiro> tipo


%left SOMA SUB

%%

programa:
    INICIO bloco FIM {
        raiz_ast = ast_cria(AST_PROGRAMA, NULL, 1, $2);
        $$ = raiz_ast;
    }
;

bloco:
    comando { 
        $$ = ast_cria(AST_BLOCO, NULL, 1, $1); 
    }
    | bloco comando {
        if (!$2) {
            fprintf(stderr, "[ERRO] Comando nulo em bloco!\n");
            $$ = $1; // Retorna o bloco anterior sem adicionar comando nulo
        } else {
            int n = $1->n_filhos + 1;
            AST** filhos = malloc(sizeof(AST*) * n);
            for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
            filhos[n-1] = $2;
            AST* novo_bloco = ast_cria(AST_BLOCO, NULL, 0); // cria vazio
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
    | SE expressao ENTAO bloco SENAO bloco FIMSE {
        $$ = ast_cria(AST_IF, NULL, 3, $2, $4, $6);
    }
    | ENQUANTO expressao FACA bloco FIMENQUANTO {
        $$ = ast_cria(AST_WHILE, NULL, 2, $2, $4);
    }
    | PARA ID DE expressao ATE expressao FACA bloco FIMPARA {
        AST* id = ast_cria(AST_ID, strdup($2), 0);
        $$ = ast_cria(AST_FOR, NULL, 4, id, $4, $6, $8);
    }
;

declaracao:
    VAR DOISPONTOS tipo ID PONTOEVIRGULA {
        strcpy(variaveis[num_vars].nome, $4);
        variaveis[num_vars].tipo = $3;
        num_vars++;
        AST* tipo_no = ast_cria(AST_ID, strdup($4), 0);
        AST* tipo_tipo = ast_cria(AST_NUM, strdup($3 == TIPO_INT ? "int" : $3 == TIPO_FLOAT ? "float" : "char"), 0);
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, tipo_tipo, tipo_no);
    }
;

tipo:
    TIPO_INTEIRO     { $$ = TIPO_INT; }
    | TIPO_REAL      { $$ = TIPO_FLOAT; }
    | TIPO_CARACTERE { $$ = TIPO_CHAR; }
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
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
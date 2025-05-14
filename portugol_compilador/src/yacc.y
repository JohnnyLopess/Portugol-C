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
%type <expr> expressao

%left SOMA SUB

%%

programa:
    INICIO bloco FIM {
        saida = fopen("saida.c", "w");
        fprintf(saida, "#include <stdio.h>\n\nint main() {\n");
        fprintf(saida, "%s", $2);
        fprintf(saida, "    return 0;\n}\n");
        fclose(saida);
        $$ = $2;
    }
;

bloco:
    bloco comando {
        char *temp = malloc(1000);
        sprintf(temp, "%s%s", $1, $2);  // Remove \n extra
        $$ = temp;
    }
    | comando {
        $$ = $1;
    }
;

comando:
    declaracao { 
        $$ = $1;
    }
    | leitura { $$ = $1; }
    | escrita { $$ = $1; }
    | atribuicao { $$ = $1; }
    | SE expressao ENTAO bloco SENAO bloco FIMSE {
        char *temp = malloc(1000);
        char *bloco_if = malloc(1000);
        char *bloco_else = malloc(1000);
        
        // Processa o bloco if
        char *linha_if = strtok($4, "\n");
        strcpy(bloco_if, "");
        while (linha_if != NULL) {
            char temp_linha[1000];
            sprintf(temp_linha, "        %s\n", linha_if + 4);
            strcat(bloco_if, temp_linha);
            linha_if = strtok(NULL, "\n");
        }
        
        // Processa o bloco else
        char *linha_else = strtok($6, "\n");
        strcpy(bloco_else, "");
        while (linha_else != NULL) {
            char temp_linha[1000];
            sprintf(temp_linha, "        %s\n", linha_else + 4);
            strcat(bloco_else, temp_linha);
            linha_else = strtok(NULL, "\n");
        }
        
        sprintf(temp, "    if (%s) {\n%s    } else {\n%s    }\n", 
                $2.valor, bloco_if, bloco_else);
        
        free(bloco_if);
        free(bloco_else);
        $$ = temp;
    }
    | ENQUANTO expressao FACA bloco FIMENQUANTO {
    char *temp = malloc(1000);
    char *bloco_indentado = malloc(1000);
    char *linha = strtok($4, "\n");
    strcpy(bloco_indentado, "");
    while (linha != NULL) {
        char temp_linha[1000];
        sprintf(temp_linha, "        %s\n", linha + 4);
        strcat(bloco_indentado, temp_linha);  // Fixed: trcat -> strcat
        linha = strtok(NULL, "\n");
    }
    sprintf(temp, "    while (%s) {\n%s    }\n", $2.valor, bloco_indentado);
    free(bloco_indentado);
    $$ = temp;
}
       | PARA ID DE expressao ATE expressao FACA bloco FIMPARA {
        char *temp = malloc(1000);
        char *bloco_indentado = malloc(1000);
        
        // Processa o bloco do loop (usa $8, que é o bloco)
        char *linha = strtok($8, "\n");
        strcpy(bloco_indentado, "");
        while (linha != NULL) {
            char temp_linha[1000];
            sprintf(temp_linha, "        %s\n", linha + 4);  // Remove 4 espaços
            strcat(bloco_indentado, temp_linha);
            linha = strtok(NULL, "\n");
        }
        
        // Gera o for em C
        sprintf(temp, 
            "    for (%s = %s; %s <= %s; %s++) {\n%s    }\n", 
            $2, $4.valor, $2, $6.valor, $2, bloco_indentado);
        
        free(bloco_indentado);
        $$ = temp;
    }
;

declaracao:
    VAR DOISPONTOS tipo ID PONTOEVIRGULA {
        char *temp = malloc(100);
        // Store variable type information
        strcpy(variaveis[num_vars].nome, $4);
        variaveis[num_vars].tipo = $3;
        num_vars++;
        
        switch($3) {
            case TIPO_INT:
                sprintf(temp, "    int %s;\n", $4);
                break;
            case TIPO_FLOAT:
                sprintf(temp, "    float %s;\n", $4);
                break;
            case TIPO_CHAR:
                sprintf(temp, "    char %s;\n", $4);
                break;
        }
        $$ = temp;
    }
;

tipo:
    TIPO_INTEIRO     { $$ = TIPO_INT; }
    | TIPO_REAL      { $$ = TIPO_FLOAT; }
    | TIPO_CARACTERE { $$ = TIPO_CHAR; }
;

leitura:
    LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        int tipo = buscar_tipo_variavel($3);
        
        switch(tipo) {
            case TIPO_INT:
                sprintf(temp, "    scanf(\"%%d\", &%s);\n", $3);
                break;
            case TIPO_FLOAT:
                sprintf(temp, "    scanf(\"%%f\", &%s);\n", $3);
                break;
            case TIPO_CHAR:
                sprintf(temp, "    scanf(\" %%c\", &%s);\n", $3);
                break;
            default:
                sprintf(temp, "    // Erro: variável %s não declarada\n", $3);
        }
        $$ = temp;
    }
;

escrita:
    ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        int tipo = buscar_tipo_variavel($3);
        
        switch(tipo) {
            case TIPO_INT:
                sprintf(temp, "    printf(\"%%d\\n\", %s);\n", $3);
                break;
            case TIPO_FLOAT:
                sprintf(temp, "    printf(\"%%f\\n\", %s);\n", $3);
                break;
            case TIPO_CHAR:
                sprintf(temp, "    printf(\"%%c\\n\", %s);\n", $3);
                break;
            default:
                sprintf(temp, "    // Erro: variável %s não declarada\n", $3);
        }
        $$ = temp;
    }
    | ESCREVA ABREPAR STRING FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    printf(%s);\n", $3);
        $$ = temp;
    }
    | ESCREVA ABREPAR expressao FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        if ($3.tipo == 0)
            sprintf(temp, "    printf(\"%%d\\n\", %s);\n", $3.valor);
        else
            sprintf(temp, "    printf(\"%%s\\n\", %s);\n", $3.valor);
        $$ = temp;
    }
    | ESCREVA ABREPAR NUM FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    printf(\"%%d\\n\", %s);\n", $3);
        $$ = temp;
    }
;

atribuicao:
    ID IGUAL expressao PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    %s = %s;\n", $1, $3.valor);
        $$ = temp;
    }
;

expressao:
    NUM {
        $$.valor = strdup($1);
        $$.tipo = 0;
    }
    | ID {
        $$.valor = strdup($1);
        $$.tipo = 0;
    }
    | expressao SOMA expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s + %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao SUB expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s - %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao COMPARA expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s == %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao MENOR expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s < %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao MAIOR expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s > %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao MENOR_IGUAL expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s <= %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao MAIOR_IGUAL expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s >= %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
    | expressao DIFERENTE expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s != %s", $1.valor, $3.valor);
        $$.valor = temp;
        $$.tipo = 0;
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
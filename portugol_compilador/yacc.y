%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

// Arquivo de saída em C
FILE *saida;
%}

%union {
    char* str;
    int inteiro;
    struct {
        char* valor;
        int tipo;
    } expr;
    char* codigo;
}

%token INICIO FIM LEIA ESCREVA VAR
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTERE
%token SE SENAO ENTAO FIMSE
%token ENQUANTO FACA FIMENQUANTO
%token IGUAL COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token SOMA SUB MUL DIV
%token ABREPAR FECHAPAR PONTOEVIRGULA
%token DOISPONTOS
%token <str> NUM ID
%type <codigo> programa bloco comando declaracao leitura escrita atribuicao
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
    | SE expressao ENTAO bloco FIMSE {
        char *temp = malloc(1000);
        sprintf(temp, "    if (%s) {\n%s    }\n", $2.valor, $4);
        $$ = temp;
    }
    | SE expressao ENTAO bloco SENAO bloco FIMSE {
        char *temp = malloc(1000);
        sprintf(temp, "    if (%s) {\n%s    } else {\n%s    }\n", $2.valor, $4, $6);
        $$ = temp;
    }
;

declaracao:
    VAR ID DOISPONTOS tipo PONTOEVIRGULA {
        char *temp = malloc(100);
        if ($4 == 0) sprintf(temp, "    int %s;\n", $2);
        else if ($4 == 1) sprintf(temp, "    float %s;\n", $2);
        else if ($4 == 2) sprintf(temp, "    char %s;\n", $2);
        $$ = temp;
    }
;

tipo:
    TIPO_INTEIRO     { $$ = 0; }
    | TIPO_REAL      { $$ = 1; }
    | TIPO_CARACTERE { $$ = 2; }
;

leitura:
    LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    scanf(\"%%d\", &%s);\n", $3);
        $$ = temp;
    }
;

escrita:
    ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    printf(\"%%d\\n\", %s);\n", $3);
        $$ = temp;
    }
    | ESCREVA ABREPAR expressao FECHAPAR PONTOEVIRGULA {
        char *temp = malloc(100);
        sprintf(temp, "    printf(\"%%d\\n\", %s);\n", $3.valor);
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

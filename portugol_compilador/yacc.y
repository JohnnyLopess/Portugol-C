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

%type <inteiro> tipo
%type <str> expressao

%%

programa:
    INICIO {
        saida = fopen("saida.c", "w");
        fprintf(saida, "#include <stdio.h>\n\nint main() {\n");
    }
    bloco
    FIM {
        fprintf(saida, "return 0;\n}\n");
        fclose(saida);
    }
;

bloco:
    bloco comando
    | comando
;

comando:
    declaracao
    | leitura
    | escrita
    | atribuicao
;

declaracao:
    VAR ID DOISPONTOS tipo PONTOEVIRGULA {
        if ($4 == 0) fprintf(saida, "int %s;\n", $2);
        else if ($4 == 1) fprintf(saida, "float %s;\n", $2);
        else if ($4 == 2) fprintf(saida, "char %s;\n", $2);
    }
;

tipo:
    TIPO_INTEIRO     { $$ = 0; }
    | TIPO_REAL      { $$ = 1; }
    | TIPO_CARACTERE { $$ = 2; }
;

leitura:
    LEIA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        fprintf(saida, "scanf(\"%%d\", &%s);\n", $3);
    }
;

escrita:
    ESCREVA ABREPAR ID FECHAPAR PONTOEVIRGULA {
        fprintf(saida, "printf(\"%%d\", %s);\n", $3);
    }
;

atribuicao:
    ID IGUAL expressao PONTOEVIRGULA {
        fprintf(saida, "%s = %s;\n", $1, $3);
    }
;

expressao:
    NUM { $$ = strdup($1); }
    | ID { $$ = strdup($1); }
    | expressao SOMA expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s + %s", $1, $3);
        $$ = temp;
    }
    | expressao SUB expressao {
        char *temp = malloc(100);
        sprintf(temp, "%s - %s", $1, $3);
        $$ = temp;
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

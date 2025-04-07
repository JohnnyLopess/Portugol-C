%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}

%%

"inicio"        { printf("[TOKEN] INICIO\n"); return INICIO; }
"fim"           { printf("[TOKEN] FIM\n"); return FIM; }

"leia"          { printf("[TOKEN] LEIA\n"); return LEIA; }
"escreva"       { printf("[TOKEN] ESCREVA\n"); return ESCREVA; }
"var"           { printf("[TOKEN] VAR\n"); return VAR; }

"se"            { printf("[TOKEN] SE\n"); return SE; }
"senao"         { printf("[TOKEN] SENAO\n"); return SENAO; }
"entao"         { printf("[TOKEN] ENTAO\n"); return ENTAO; }
"fimse"         { printf("[TOKEN] FIMSE\n"); return FIMSE; }

"enquanto"      { printf("[TOKEN] ENQUANTO\n"); return ENQUANTO; }
"faca"          { printf("[TOKEN] FACA\n"); return FACA; }
"fimenquanto"   { printf("[TOKEN] FIMENQUANTO\n"); return FIMENQUANTO; }

"inteiro"       { yylval.str = strdup(yytext); return TIPO_INTEIRO; }
"real"          { yylval.str = strdup(yytext); return TIPO_REAL; }
"caractere"     { yylval.str = strdup(yytext); return TIPO_CARACTERE; }

"para"          {printf("[TOKEN] PARA\n"); return PARA;}
"de"            {printf("[TOKEN] DE\n"); return DE;}
"ate"           {printf("[TOKEN] ATE\n"); return ATE;}
"fimpara"       {printf("[TOKEN] FIMPARA\n"); return FIMPARA;}

"=="            { printf("[TOKEN] COMPARA\n"); return COMPARA; }
"="             { printf("[TOKEN] IGUAL\n"); return IGUAL; }
"<>"            { return DIFERENTE; }
"<="            { return MENOR_IGUAL; }
">="            { return MAIOR_IGUAL; }
"<"             { return MENOR; }
">"             { return MAIOR; }

"+"             { return SOMA; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }

"("             { return ABREPAR; }
")"             { return FECHAPAR; }
";"             { return PONTOEVIRGULA; }
":"             { return DOISPONTOS; }

[0-9]+          { yylval.str = strdup(yytext); printf("[TOKEN] NUMERO (%s)\n", yytext); return NUM; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    printf("[TOKEN] ID (%s)\n", yytext);
    return ID;
}

[ \t\n\r]+      ;   // Ignora espaços e quebras de linha
"//".*          ;   // Ignora comentários de linha
"{"[^}]*"}"     ;   // Ignora comentários de bloco

.               { printf("[LEXER] Caractere inválido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

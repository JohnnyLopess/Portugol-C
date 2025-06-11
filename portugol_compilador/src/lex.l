%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}

%%

\"[^\"]*\"      { 
    yylval.str = strdup(yytext); 
    printf("[TOKEN] STRING (%s)\n", yytext);
    return STRING; 
}

"programa"        { printf("[TOKEN] PROGRAMA\n"); return PROGRAMA; }
"retorne"       { printf("[TOKEN] RETORNE\n"); return RETORNE; }

"leia"          { printf("[TOKEN] LEIA\n"); return LEIA; }
"escreva"       { printf("[TOKEN] ESCREVA\n"); return ESCREVA; }
"limpa"       { printf("[TOKEN] LIMPA\n"); return LIMPA; }
"const"       { printf("[TOKEN] CONST\n"); return CONST; }
"funcao"        { printf("[TOKEN] FUNCAO\n"); return FUNCAO; }

"se"            { printf("[TOKEN] SE\n"); return SE; }
"senao"         { printf("[TOKEN] SENAO\n"); return SENAO; }
"escolha"         { printf("[TOKEN] ESCOLHA\n"); return ESCOLHA; }
"caso"         { printf("[TOKEN] CASO\n"); return CASO; }
"pare"         { printf("[TOKEN] PARE\n"); return PARE; }

"enquanto"      { printf("[TOKEN] ENQUANTO\n"); return ENQUANTO; }
"faca"          { printf("[TOKEN] FACA\n"); return FACA; }
"fimenquanto"   { printf("[TOKEN] FIMENQUANTO\n"); return FIMENQUANTO; }

"inteiro"       { printf("[TOKEN] TIPO_INTEIRO\n"); yylval.str = strdup(yytext); return TIPO_INTEIRO; }
"real"          { printf("[TOKEN] TIPO_REAL\n"); yylval.str = strdup(yytext); return TIPO_REAL; }
"caracter"     { printf("[TOKEN] TIPO_CARACTERE\n"); yylval.str = strdup(yytext); return TIPO_CARACTERE; }
"cadeia"        { printf("[TOKEN] TIPO_CADEIA\n"); yylval.str = strdup(yytext); return TIPO_CADEIA; }
"logico"        { printf("[TOKEN] TIPO_LOGICO\n"); yylval.str = strdup(yytext); return TIPO_LOGICO; }
"vazio"         { printf("[TOKEN] TIPO_VAZIO\n"); yylval.str = strdup(yytext); return TIPO_VAZIO; }

"para"          {printf("[TOKEN] PARA\n"); return PARA;}

"=="            { printf("[TOKEN] COMPARA\n"); return COMPARA; }
"="             { printf("[TOKEN] IGUAL\n"); return IGUAL; }
"!="            { return DIFERENTE; }
"<="            { return MENOR_IGUAL; }
">="            { return MAIOR_IGUAL; }
"<"             { return MENOR; }
">"             { return MAIOR; }

"+"             { return SOMA; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"%"             { return MOD; }
"+="              { printf("[TOKEN] OP_MAIS_IGUAL\n"); return OP_MAIS_IGUAL; }
"-="              { printf("[TOKEN] OP_MENOS_IGUAL\n"); return OP_MENOS_IGUAL; }
"*="              { printf("[TOKEN] OP_MULTIPLICACAO_IGUAL\n"); return OP_MULTIPLICACAO_IGUAL; }
"/="              { printf("[TOKEN] OP_DIVISAO_IGUAL\n"); return OP_DIVISAO_IGUAL; }
"++"              { printf("[TOKEN] OP_INCREMENTO_UNARIO\n"); return OP_INCREMENTO_UNARIO; }
"--"              { printf("[TOKEN] OP_DECREMENTO_UNARIO\n"); return OP_DECREMENTO_UNARIO; }

"e"              { printf("[TOKEN] OP_LOGICO_E\n"); return OP_LOGICO_E; }
"ou"              { printf("[TOKEN] OP_LOGICO_OU\n"); return OP_LOGICO_OU; }
"nao"              { printf("[TOKEN] OP_LOGICO_NAO\n"); return OP_LOGICO_NAO; }

"&"              { printf("[TOKEN] OP_BITWISE_AND\n"); return OP_BITWISE_AND; }
"|"              { printf("[TOKEN] OP_BITWISE_OR\n"); return OP_BITWISE_OR; }
"~"              { printf("[TOKEN] OP_BITWISE_NOT\n"); return OP_BITWISE_NOT; }
"^"              { printf("[TOKEN] OP_BITWISE_XOR\n"); return OP_BITWISE_XOR; }
"<<"              { printf("[TOKEN] OP_BITWISE_SHIFT\n"); return OP_BITWISE_SHIFT; }

"("             { return ABREPAR; }
")"             { return FECHAPAR; }
";"             { return PONTOEVIRGULA; }
","             { return VIRGULA; }
":"             { return DOISPONTOS; }
"["             { return ABRECOL; }
"]"             { return FECHACOL; }
"{"             { return ABRECHA; }
"}"             { return FECHACHA; }

[0-9]+          { yylval.str = strdup(yytext); printf("[TOKEN] NUMERO (%s)\n", yytext); return NUM; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    printf("[TOKEN] ID (%s)\n", yytext);
    return ID;
}

[ \t\n\r]+      ;   // Ignora espaços e quebras de linha
"//".* {
    char* texto = yytext + 2;
    while (*texto == ' ') texto++;
    yylval.str = strdup(texto);
    printf("[TOKEN] COMENTARIO_LINHA (%s)\n", texto);
    return COMENTARIO_LINHA;
}

/\*([^*]|\*+[^*/])*\*+/ {
    char* texto = strdup(yytext + 2); // Remove /*
    texto[strlen(texto) - 2] = '\0';  // Remove */
    yylval.str = texto;
    printf("[TOKEN] COMENTARIO_BLOCO (%s)\n", texto);
    return COMENTARIO_BLOCO;
}

.               { printf("[LEXER] Caractere inválido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

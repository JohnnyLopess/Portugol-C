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

"programa"      { printf("[TOKEN] PROGRAMA\n"); return PROGRAMA; }

"inicio"        { printf("[TOKEN] INICIO\n"); return INICIO; }
"retorne"       { printf("[TOKEN] RETORNE\n"); return RETORNE; }

"leia"          { printf("[TOKEN] LEIA\n"); return LEIA; }
"escreva"       { printf("[TOKEN] ESCREVA\n"); return ESCREVA; }
"funcao"        { printf("[TOKEN] FUNCAO\n"); return FUNCAO; }
"fimfuncao"        { printf("[TOKEN] FIMFUNCAO\n"); return FIMFUNCAO; }

"se"            { printf("[TOKEN] SE\n"); return SE; }
"senao"         { printf("[TOKEN] SENAO\n"); return SENAO; }
"entao"         { printf("[TOKEN] ENTAO\n"); return ENTAO; }

"escolha"       { printf("[TOKEN] ESCOLHA\n"); return ESCOLHA; }
"caso"          { printf("[TOKEN] CASO\n"); return CASO; }
"pare"          { printf("[TOKEN] PARE\n"); return PARE; }
"caso contrario" { printf("[TOKEN] CASO_CONTRARIO\n"); return CASO_CONTRARIO; }

"enquanto"      { printf("[TOKEN] ENQUANTO\n"); return ENQUANTO; }
"faca"          { printf("[TOKEN] FACA\n"); return FACA; }

"inteiro"       { printf("[TOKEN] TIPO_INTEIRO\n"); yylval.str = strdup(yytext); return TIPO_INTEIRO; }
"real"          { printf("[TOKEN] TIPO_REAL\n"); yylval.str = strdup(yytext); return TIPO_REAL; }
"caractere"     { printf("[TOKEN] TIPO_CARACTERE\n"); yylval.str = strdup(yytext); return TIPO_CARACTERE; }
"logico"        { printf("[TOKEN] TIPO_LOGICO\n"); yylval.str = strdup(yytext); return TIPO_LOGICO; }
"vazio"         { printf("[TOKEN] TIPO_VAZIO\n"); yylval.str = strdup(yytext); return TIPO_VAZIO; }

"para"          {printf("[TOKEN] PARA\n"); return PARA;}
"de"            {printf("[TOKEN] DE\n"); return DE;}
"ate"           {printf("[TOKEN] ATE\n"); return ATE;}
"fimpara"       {printf("[TOKEN] FIMPARA\n"); return FIMPARA;}

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

"("             { return ABREPAR; }
")"             { return FECHAPAR; }
"{"             { printf("[TOKEN] ABRECHAVE\n"); return ABRECHAVE; }
"}"             { printf("[TOKEN] FECHACHAVE\n"); return FECHACHAVE; }
";"             { return PONTOEVIRGULA; }
","             { return VIRGULA; }
":"             { return DOISPONTOS; }

[0-9]+          { yylval.str = strdup(yytext); printf("[TOKEN] NUMERO (%s)\n", yytext); return NUM; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    printf("[TOKEN] ID (%s)\n", yytext);
    return ID;
}

[ \t\n\r]+      ;   // Ignora espaços e quebras de linha
"//".* {
    char* texto = yytext + 2; // Ignora "//"
    while (*texto == ' ') texto++; // Remove espaços iniciais
    yylval.str = strdup(texto);
    printf("[TOKEN] COMENTARIO_LINHA (%s)\n", texto);
    return COMENTARIO_LINHA;
}

"/*"([^*]|\*+[^/])*\*+"/" {
    yylval.str = strdup(yytext + 2); // Remove "/*"
    yylval.str[strlen(yylval.str) - 2] = '\0'; // Remove "*/"
    printf("[TOKEN] COMENTARIO_BLOCO (%s)\n", yytext);
    return COMENTARIO_BLOCO;
}

.               { printf("[LEXER] Caractere inválido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

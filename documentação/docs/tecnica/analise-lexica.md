# Análise Léxica

A análise léxica é a primeira fase do compilador Portugol-C, responsável por transformar o código fonte em uma sequência de tokens. Este documento descreve o analisador léxico implementado usando Flex (lex).

## Visão Geral

### Arquivo Principal
- **Localização**: `src/lex.l`
- **Ferramenta**: Flex (Fast Lexical Analyzer Generator)
- **Saída**: `lex.yy.c` (código C gerado)

### Função Principal
```c
int yylex(void)
```
- Retorna o próximo token do código fonte
- Atualiza a variável global `yylval` com o valor do token
- Incrementa contadores de linha e coluna para mensagens de erro

## Estrutura do Arquivo `lex.l`

### 1. Seção de Definições

#### Inclusões e Declarações
```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"  // Tokens definidos pelo parser

extern int yylval;
int linha = 1;      // Contador de linhas
int coluna = 1;     // Contador de colunas
%}
```

#### Definições de Padrões
```flex
DIGITO          [0-9]
LETRA           [a-zA-Z_]
IDENTIFICADOR   {LETRA}({LETRA}|{DIGITO})*
INTEIRO         {DIGITO}+
REAL            {DIGITO}+\.{DIGITO}+
CARACTER        '([^'\\]|\\.|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2})'
ESPACO          [ \t]+
NOVA_LINHA      \n
COMENTARIO_LINHA "//".*
COMENTARIO_BLOCO "/*"([^*]|\*+[^*/])*\*+"/"
```

### 2. Seção de Regras

#### Palavras-chave
```flex
"programa"      { return PROGRAMA; }
"funcao"        { return FUNCAO; }
"inicio"        { return INICIO; }
"se"            { return SE; }
"senao"         { return SENAO; }
"para"          { return PARA; }
"enquanto"      { return ENQUANTO; }
"faca"          { return FACA; }
"escolha"       { return ESCOLHA; }
"caso"          { return CASO; }
"padrao"        { return PADRAO; }
"pare"          { return PARE; }
"retorne"       { return RETORNE; }
"leia"          { return LEIA; }
"escreva"       { return ESCREVA; }
```

#### Tipos de Dados
```flex
"inteiro"       { return TIPO_INTEIRO; }
"real"          { return TIPO_REAL; }
"caracter"      { return TIPO_CARACTER; }
"logico"        { return TIPO_LOGICO; }
"verdadeiro"    { yylval = 1; return VERDADEIRO; }
"falso"         { yylval = 0; return FALSO; }
```

#### Operadores Aritméticos
```flex
"+"             { return MAIS; }
"-"             { return MENOS; }
"*"             { return MULTIPLICACAO; }
"/"             { return DIVISAO; }
"%"             { return MODULO; }
"++"            { return INCREMENTO; }
"--"            { return DECREMENTO; }
```

#### Operadores de Atribuição
```flex
"="             { return ATRIBUICAO; }
"+="            { return MAIS_IGUAL; }
"-="            { return MENOS_IGUAL; }
"*="            { return MULT_IGUAL; }
"/="            { return DIV_IGUAL; }
"%="            { return MOD_IGUAL; }
```

#### Operadores Relacionais
```flex
"=="            { return IGUAL; }
"!="            { return DIFERENTE; }
"<"             { return MENOR; }
"<="            { return MENOR_IGUAL; }
">"             { return MAIOR; }
">="            { return MAIOR_IGUAL; }
```

#### Operadores Lógicos
```flex
"&&"            { return E_LOGICO; }
"||"            { return OU_LOGICO; }
"!"             { return NAO_LOGICO; }
```

#### Operadores Bitwise
```flex
"&"             { return E_BITWISE; }
"|"             { return OU_BITWISE; }
"^"             { return XOR_BITWISE; }
"~"             { return COMPLEMENTO; }
"<<"            { return DESLOC_ESQUERDA; }
">>"            { return DESLOC_DIREITA; }
```

#### Delimitadores
```flex
"("             { return ABRE_PARENTESES; }
")"             { return FECHA_PARENTESES; }
"{"             { return ABRE_CHAVES; }
"}"             { return FECHA_CHAVES; }
"["             { return ABRE_COLCHETES; }
"]"             { return FECHA_COLCHETES; }
";"             { return PONTO_VIRGULA; }
","             { return VIRGULA; }
":"             { return DOIS_PONTOS; }
```

#### Literais
```flex
{INTEIRO}       { 
                  yylval = atoi(yytext); 
                  return NUM_INTEIRO; 
                }

{REAL}          { 
                  yylval = (int)(atof(yytext) * 1000); // Para preservar decimais
                  return NUM_REAL; 
                }

{CARACTER}      { 
                  yylval = yytext[1]; // Caractere entre aspas
                  return CARACTER_LITERAL; 
                }

{IDENTIFICADOR} { 
                  yylval = (int)strdup(yytext);
                  return IDENTIFICADOR; 
                }
```

#### Tratamento de Espaços e Comentários
```flex
{ESPACO}        { coluna += yyleng; }
{NOVA_LINHA}    { linha++; coluna = 1; }
{COMENTARIO_LINHA}      { /* Ignora comentários de linha */ }
{COMENTARIO_BLOCO}      { 
                          // Conta linhas em comentários de bloco
                          char *p = yytext;
                          while (*p) {
                              if (*p == '\n') linha++;
                              p++;
                          }
                        }
```

### 3. Seção de Código do Usuário

```c
int yywrap() {
    return 1; // Indica fim do arquivo
}

void yyerror(const char *msg) {
    fprintf(stderr, "Erro léxico na linha %d, coluna %d: %s\n", 
            linha, coluna, msg);
}
```

## Tokens Definidos

### Classificação dos Tokens

| Categoria | Tokens | Quantidade |
|-----------|--------|------------|
| **Palavras-chave** | `programa`, `funcao`, `inicio`, `se`, `senao`, etc. | 14 |
| **Tipos** | `inteiro`, `real`, `caracter`, `logico` | 4 |
| **Operadores** | `+`, `-`, `*`, `/`, `==`, `!=`, `&&`, `||`, etc. | 25 |
| **Delimitadores** | `(`, `)`, `{`, `}`, `[`, `]`, `;`, `,` | 8 |
| **Literais** | Números, caracteres, booleanos | 4 |
| **Identificadores** | Nomes de variáveis e funções | 1 |

### Códigos de Token (em `y.tab.h`)

```c
// Palavras-chave
#define PROGRAMA        256
#define FUNCAO          257
#define INICIO          258
#define SE              259
#define SENAO           260
// ... outros tokens

// Tipos
#define TIPO_INTEIRO    300
#define TIPO_REAL       301
#define TIPO_CARACTER   302
#define TIPO_LOGICO     303

// Operadores
#define MAIS            400
#define MENOS           401
#define MULTIPLICACAO   402
// ... outros operadores

// Literais
#define NUM_INTEIRO     500
#define NUM_REAL        501
#define CARACTER_LITERAL 502
#define VERDADEIRO      503
#define FALSO           504
#define IDENTIFICADOR   505
```

## Tratamento de Caracteres Especiais

### Escape Sequences em Caracteres

```c
// Sequências de escape suportadas
'a'     // Caractere normal
'\n'    // Nova linha
'\t'    // Tab
'\\'    // Barra invertida
'\''    // Aspas simples
'\"'    // Aspas duplas (em strings)
'\0'    // Caractere nulo
'\123'  // Octal (até 3 dígitos)
'\x41'  // Hexadecimal (até 2 dígitos)
```

### Implementação no Lexer

```flex
CARACTER        '([^'\\]|\\.|\\[0-7]{1,3}|\\x[0-9a-fA-F]{1,2})'

{CARACTER}      { 
                  char c = yytext[1];
                  if (c == '\\') {
                      // Tratar escape sequences
                      switch (yytext[2]) {
                          case 'n': c = '\n'; break;
                          case 't': c = '\t'; break;
                          case '\\': c = '\\'; break;
                          case '\'': c = '\''; break;
                          case '0': c = '\0'; break;
                          // Casos octais e hexadecimais...
                      }
                  }
                  yylval = (int)c;
                  return CARACTER_LITERAL;
                }
```

## Tratamento de Números

### Números Inteiros

```flex
INTEIRO         [0-9]+
INTEIRO_NEG     -[0-9]+

{INTEIRO}       { 
                  yylval = atoi(yytext);
                  return NUM_INTEIRO;
                }

{INTEIRO_NEG}   {
                  yylval = atoi(yytext);
                  return NUM_INTEIRO;
                }
```

### Números Reais

```flex
REAL            [0-9]+\.[0-9]+
REAL_NEG        -[0-9]+\.[0-9]+

{REAL}          {
                  // Multiplica por 1000 para preservar 3 casas decimais
                  double valor = atof(yytext);
                  yylval = (int)(valor * 1000);
                  return NUM_REAL;
                }
```

### Validação de Números

```c
// Função auxiliar para validar limites
int validar_inteiro(const char* texto) {
    long valor = strtol(texto, NULL, 10);
    if (valor > INT_MAX || valor < INT_MIN) {
        yyerror("Número inteiro fora dos limites");
        return 0;
    }
    return (int)valor;
}
```

## Tratamento de Comentários

### Comentários de Linha

```flex
COMENTARIO_LINHA    "//".*$

{COMENTARIO_LINHA}  { 
                      // Ignora até o final da linha
                      coluna += yyleng;
                    }
```

### Comentários de Bloco

```flex
COMENTARIO_BLOCO    "/*"([^*]|\*+[^*/])*\*+"/"

{COMENTARIO_BLOCO}  {
                      // Conta linhas dentro do comentário
                      for (int i = 0; i < yyleng; i++) {
                          if (yytext[i] == '\n') {
                              linha++;
                              coluna = 1;
                          } else {
                              coluna++;
                          }
                      }
                    }
```

### Comentários Aninhados (Não Suportado)

```c
// Comentários aninhados não são suportados
/* Comentário externo /* interno */ ainda externo */ // ERRO!
```

## Gerenciamento de Estados

### Estados do Lexer

```flex
%x COMENTARIO_BLOCO

%%

"/*"                { BEGIN(COMENTARIO_BLOCO); }
<COMENTARIO_BLOCO>"*/"  { BEGIN(INITIAL); }
<COMENTARIO_BLOCO>\n    { linha++; coluna = 1; }
<COMENTARIO_BLOCO>.     { coluna++; }
<COMENTARIO_BLOCO><<EOF>> { 
                          yyerror("Comentário de bloco não fechado"); 
                          return 0; 
                        }
```

## Tratamento de Erros Léxicos

### Caracteres Inválidos

```flex
.               { 
                  char msg[100];
                  sprintf(msg, "Caractere inválido: '%c' (ASCII %d)", 
                          yytext[0], yytext[0]);
                  yyerror(msg);
                  coluna++;
                }
```

### Strings Não Fechadas

```flex
"               { 
                  yyerror("String literal não fechada");
                  return 0;
                }
```

### Função de Erro Personalizada

```c
void erro_lexico(const char* mensagem, const char* token) {
    fprintf(stderr, "ERRO LÉXICO [%d:%d]: %s\n", linha, coluna, mensagem);
    if (token) {
        fprintf(stderr, "Token problemático: '%s'\n", token);
    }
    exit(1);
}
```

## Interface com o Parser

### Variáveis Globais Compartilhadas

```c
extern YYSTYPE yylval;  // Valor semântico do token
extern int yylineno;    // Número da linha atual
extern char* yytext;    // Texto do token atual
extern int yyleng;      // Tamanho do token atual
```

### Função Principal do Lexer

```c
int yylex(void) {
    int token = flex_yylex();
    
    // Log de debugging (opcional)
    #ifdef DEBUG_LEXER
    printf("Token: %d, Texto: '%s', Linha: %d, Coluna: %d\n", 
           token, yytext, linha, coluna);
    #endif
    
    return token;
}
```

## Otimizações e Performance

### Buffering

```c
// Flex usa buffering automático, mas pode ser configurado
#define YY_BUF_SIZE 16384  // Tamanho do buffer (padrão: 8192)
```

### Compilação Otimizada

```makefile
# Flags para otimização do lexer
FLEX_FLAGS = -8 -f -i -s
# -8: Gerar tabelas de 8 bits
# -f: Scanner mais rápido
# -i: Case-insensitive (se necessário)
# -s: Suprimir warnings
```

### Medição de Performance

```c
#include <time.h>

void medir_performance_lexer(const char* arquivo) {
    clock_t inicio = clock();
    
    FILE* fp = fopen(arquivo, "r");
    yyin = fp;
    
    int token;
    int contador = 0;
    
    while ((token = yylex()) != 0) {
        contador++;
    }
    
    fclose(fp);
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("Tokens processados: %d\n", contador);
    printf("Tempo de análise: %.4f segundos\n", tempo);
    printf("Tokens/segundo: %.0f\n", contador / tempo);
}
```

## Exemplo de Uso

### Código Portugol de Entrada

```portugol
programa {
    funcao inicio() {
        inteiro idade = 25;
        real salario = 3500.50;
        caracter inicial = 'J';
        logico ativo = verdadeiro;
        
        se (idade >= 18 && ativo) {
            escreva("Usuário válido\n");
        } senao {
            escreva("Usuário inválido\n");
        }
    }
}
```

### Sequência de Tokens Gerados

```
PROGRAMA (256)
ABRE_CHAVES (123)
FUNCAO (257)
IDENTIFICADOR (505) -> "inicio"
ABRE_PARENTESES (40)
FECHA_PARENTESES (41)
ABRE_CHAVES (123)
TIPO_INTEIRO (300)
IDENTIFICADOR (505) -> "idade"
ATRIBUICAO (61)
NUM_INTEIRO (500) -> 25
PONTO_VIRGULA (59)
TIPO_REAL (301)
IDENTIFICADOR (505) -> "salario"
ATRIBUICAO (61)
NUM_REAL (501) -> 3500500  // (3500.50 * 1000)
PONTO_VIRGULA (59)
// ... continuação
```

## Debugging e Testes

### Modo Debug

```bash
# Compilar com debug
flex -d lex.l
gcc -DDEBUG_LEXER lex.yy.c -o lexer_debug

# Executar teste
echo "inteiro x = 42;" | ./lexer_debug
```

### Testes Unitários do Lexer

```c
// Teste individual de tokens
void teste_token(const char* entrada, int token_esperado) {
    yy_scan_string(entrada);
    int token = yylex();
    
    if (token == token_esperado) {
        printf("✓ '%s' -> %d\n", entrada, token);
    } else {
        printf("✗ '%s' -> %d (esperado %d)\n", entrada, token, token_esperado);
    }
}

int main() {
    teste_token("programa", PROGRAMA);
    teste_token("123", NUM_INTEIRO);
    teste_token("3.14", NUM_REAL);
    teste_token("'A'", CARACTER_LITERAL);
    teste_token("verdadeiro", VERDADEIRO);
    return 0;
}
```

## Manutenção e Extensões

### Adicionando Novos Tokens

1. **Definir padrão em `lex.l`**:
```flex
"nova_palavra"  { return NOVA_PALAVRA; }
```

2. **Adicionar token em `yacc.y`**:
```yacc
%token NOVA_PALAVRA
```

3. **Atualizar gramática conforme necessário**

### Modificando Comportamento

```flex
// Exemplo: Tornar palavras-chave case-insensitive
(?i:programa)   { return PROGRAMA; }
(?i:funcao)     { return FUNCAO; }
```

O analisador léxico é fundamental para o funcionamento do compilador, transformando o texto source em tokens que o parser pode processar. Sua implementação robusta garante que todos os elementos da linguagem Portugol sejam corretamente reconhecidos e categorizados.

# Análise Sintática

A análise sintática é a segunda fase do compilador Portugol-C, responsável por verificar se a sequência de tokens segue a gramática da linguagem e construir a árvore sintática abstrata (AST). Este documento descreve o analisador sintático implementado usando Yacc/Bison.

## Visão Geral

### Arquivo Principal
- **Localização**: `src/yacc.y`
- **Ferramenta**: GNU Bison (Yet Another Compiler Compiler)
- **Saída**: `y.tab.c` e `y.tab.h` (código C gerado)

### Função Principal
```c
int yyparse(void)
```
- Analisa a sequência de tokens do lexer
- Constrói a árvore sintática abstrata (AST)
- Retorna 0 em caso de sucesso, 1 em caso de erro
## Estrutura do Arquivo `yacc.y`
### 1. Seção de Declarações
#### Inclusões e Definições
```c
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"        // Estruturas da AST
#include "simbolos.h"   // Tabela de símbolos
#include "tipos.h"      // Definições de tipos
extern int yylex();
extern int yylineno;
extern char* yytext;
void yyerror(const char* msg);
AST_Node* raiz_programa = NULL;
%}
```

#### União de Valores Semânticos
```c
%union {
    int intval;              // Valores inteiros
    float realval;           // Valores reais
    char charval;            // Valores de caractere
    char* strval;            // Strings/identificadores
    struct AST_Node* node;   // Nós da AST
    struct Lista_Params* params;  // Lista de parâmetros
    struct Lista_Args* args;      // Lista de argumentos
    int tipo;                     // Códigos de tipo
}
```

#### Declaração de Tokens
```yacc
// Tokens básicos
%token <intval> NUM_INTEIRO
%token <realval> NUM_REAL
%token <charval> CARACTER_LITERAL
%token <strval> IDENTIFICADOR
%token <intval> VERDADEIRO FALSO
// Palavras-chave
%token PROGRAMA FUNCAO INICIO
%token SE SENAO PARA ENQUANTO FACA
%token ESCOLHA CASO PADRAO PARE
%token RETORNE LEIA ESCREVA
// Tipos
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTER TIPO_LOGICO
// Operadores
%token MAIS MENOS MULTIPLICACAO DIVISAO MODULO
%token INCREMENTO DECREMENTO
%token ATRIBUICAO MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL MOD_IGUAL
%token IGUAL DIFERENTE MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL
%token E_LOGICO OU_LOGICO NAO_LOGICO
%token E_BITWISE OU_BITWISE XOR_BITWISE COMPLEMENTO
%token DESLOC_ESQUERDA DESLOC_DIREITA
// Delimitadores
%token ABRE_PARENTESES FECHA_PARENTESES
%token ABRE_CHAVES FECHA_CHAVES
%token ABRE_COLCHETES FECHA_COLCHETES
%token PONTO_VIRGULA VIRGULA DOIS_PONTOS
```

#### Tipos de Não-Terminais
```yacc
%type <node> programa
%type <node> lista_funcoes funcao
%type <node> lista_parametros parametro
%type <node> bloco lista_comandos comando
%type <node> declaracao_variavel inicializacao_vetor
%type <node> comando_atribuicao comando_se comando_para
%type <node> comando_enquanto comando_escolha
%type <node> comando_retorne comando_escreva comando_leia
%type <node> expressao expressao_logica expressao_relacional
%type <node> expressao_aritmetica termo fator
%type <node> chamada_funcao lista_argumentos
%type <tipo> tipo especificador_tipo
```

#### Precedência e Associatividade
```yacc
// Precedência (menor para maior)
%right ATRIBUICAO MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL MOD_IGUAL
%left OU_LOGICO
%left E_LOGICO
%left OU_BITWISE
%left XOR_BITWISE
%left E_BITWISE
%left IGUAL DIFERENTE
%left MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL
%left DESLOC_ESQUERDA DESLOC_DIREITA
%left MAIS MENOS
%left MULTIPLICACAO DIVISAO MODULO
%right NAO_LOGICO COMPLEMENTO MENOS_UNARIO
%left INCREMENTO DECREMENTO
%left ABRE_COLCHETES
%left ABRE_PARENTESES
```

### 2. Gramática da Linguagem

#### Programa Principal
```yacc
programa: PROGRAMA ABRE_CHAVES lista_funcoes FECHA_CHAVES
        {
            $$ = criar_no_programa($3);
            raiz_programa = $$;
        }
        ;
lista_funcoes: funcao
             {
                 $$ = criar_lista_funcoes($1);
             }
             | lista_funcoes funcao
             {
                 $$ = adicionar_funcao($1, $2);
             }
             ;
```

#### Declaração de Funções
```yacc
funcao: tipo IDENTIFICADOR ABRE_PARENTESES lista_parametros FECHA_PARENTESES bloco
      {
          $$ = criar_no_funcao($1, $2, $4, $6);
          adicionar_simbolo($2, $1, SIMBOLO_FUNCAO);
      }
      | FUNCAO IDENTIFICADOR ABRE_PARENTESES lista_parametros FECHA_PARENTESES bloco
      {
          $$ = criar_no_funcao(TIPO_VOID, $2, $4, $6);
          adicionar_simbolo($2, TIPO_VOID, SIMBOLO_FUNCAO);
      }
      ;
lista_parametros: /* vazio */
                {
                    $$ = NULL;
                }
                | parametro
                {
                    $$ = criar_lista_parametros($1);
                }
                | lista_parametros VIRGULA parametro
                {
                    $$ = adicionar_parametro($1, $3);
                }
                ;
parametro: tipo IDENTIFICADOR
         {
             $$ = criar_no_parametro($1, $2);
             adicionar_simbolo($2, $1, SIMBOLO_PARAMETRO);
         }
         | tipo IDENTIFICADOR ABRE_COLCHETES FECHA_COLCHETES
         {
             $$ = criar_no_parametro_vetor($1, $2);
             adicionar_simbolo($2, $1 | TIPO_VETOR, SIMBOLO_PARAMETRO);
         }
         ;
```

#### Tipos e Declarações
```yacc
tipo: especificador_tipo
    {
        $$ = $1;
    }
    ;
especificador_tipo: TIPO_INTEIRO    { $$ = TIPO_INT; }
                  | TIPO_REAL       { $$ = TIPO_FLOAT; }
                  | TIPO_CARACTER   { $$ = TIPO_CHAR; }
                  | TIPO_LOGICO     { $$ = TIPO_BOOL; }
                  ;
declaracao_variavel: tipo IDENTIFICADOR PONTO_VIRGULA
                   {
                       $$ = criar_no_declaracao($1, $2, NULL);
                       adicionar_simbolo($2, $1, SIMBOLO_VARIAVEL);
                   }
                   | tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_VIRGULA
                   {
                       $$ = criar_no_declaracao($1, $2, $4);
                       adicionar_simbolo($2, $1, SIMBOLO_VARIAVEL);
                   }
                   | tipo IDENTIFICADOR ABRE_COLCHETES NUM_INTEIRO FECHA_COLCHETES PONTO_VIRGULA
                   {
                       $$ = criar_no_declaracao_vetor($1, $2, $4, NULL);
                       adicionar_simbolo($2, $1 | TIPO_VETOR, SIMBOLO_VARIAVEL);
                   }
                   | tipo IDENTIFICADOR ABRE_COLCHETES NUM_INTEIRO FECHA_COLCHETES ATRIBUICAO inicializacao_vetor PONTO_VIRGULA
                   {
                       $$ = criar_no_declaracao_vetor($1, $2, $4, $7);
                       adicionar_simbolo($2, $1 | TIPO_VETOR, SIMBOLO_VARIAVEL);
                   }
                   ;
inicializacao_vetor: ABRE_CHAVES lista_expressoes FECHA_CHAVES
                   {
                       $$ = criar_no_inicializacao_vetor($2);
                   }
                   ;
```

#### Comandos e Estruturas de Controle
```yacc
comando: declaracao_variavel
       | comando_atribuicao
       | comando_se
       | comando_para
       | comando_enquanto
       | comando_escolha
       | comando_retorne
       | comando_escreva
       | comando_leia
       | chamada_funcao PONTO_VIRGULA
       | bloco
       ;
comando_se: SE ABRE_PARENTESES expressao FECHA_PARENTESES comando
          {
              $$ = criar_no_se($3, $5, NULL);
          }
          | SE ABRE_PARENTESES expressao FECHA_PARENTESES comando SENAO comando
          {
              $$ = criar_no_se($3, $5, $7);
          }
          ;
comando_para: PARA ABRE_PARENTESES comando_atribuicao expressao PONTO_VIRGULA expressao FECHA_PARENTESES comando
            {
                $$ = criar_no_para($3, $4, $6, $8);
            }
            ;
comando_enquanto: ENQUANTO ABRE_PARENTESES expressao FECHA_PARENTESES comando
                {
                    $$ = criar_no_enquanto($3, $5);
                }
                ;
comando_escolha: ESCOLHA ABRE_PARENTESES expressao FECHA_PARENTESES ABRE_CHAVES lista_casos FECHA_CHAVES
               {
                   $$ = criar_no_escolha($3, $6);
               }
               ;
```

#### Expressões
```yacc
expressao: expressao_logica
         {
             $$ = $1;
         }
         ;
expressao_logica: expressao_relacional
                {
                    $$ = $1;
                }
                | expressao_logica E_LOGICO expressao_relacional
                {
                    $$ = criar_no_operacao(OP_E_LOGICO, $1, $3);
                }
                | expressao_logica OU_LOGICO expressao_relacional
                {
                    $$ = criar_no_operacao(OP_OU_LOGICO, $1, $3);
                }
                | NAO_LOGICO expressao_relacional
                {
                    $$ = criar_no_operacao_unaria(OP_NAO_LOGICO, $2);
                }
                ;
expressao_relacional: expressao_aritmetica
                    {
                        $$ = $1;
                    }
                    | expressao_aritmetica IGUAL expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_IGUAL, $1, $3);
                    }
                    | expressao_aritmetica DIFERENTE expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_DIFERENTE, $1, $3);
                    }
                    | expressao_aritmetica MENOR expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_MENOR, $1, $3);
                    }
                    | expressao_aritmetica MENOR_IGUAL expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_MENOR_IGUAL, $1, $3);
                    }
                    | expressao_aritmetica MAIOR expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_MAIOR, $1, $3);
                    }
                    | expressao_aritmetica MAIOR_IGUAL expressao_aritmetica
                    {
                        $$ = criar_no_operacao(OP_MAIOR_IGUAL, $1, $3);
                    }
                    ;
expressao_aritmetica: termo
                    {
                        $$ = $1;
                    }
                    | expressao_aritmetica MAIS termo
                    {
                        $$ = criar_no_operacao(OP_SOMA, $1, $3);
                    }
                    | expressao_aritmetica MENOS termo
                    {
                        $$ = criar_no_operacao(OP_SUBTRACAO, $1, $3);
                    }
                    ;
termo: fator
     {
         $$ = $1;
     }
     | termo MULTIPLICACAO fator
     {
         $$ = criar_no_operacao(OP_MULTIPLICACAO, $1, $3);
     }
     | termo DIVISAO fator
     {
         $$ = criar_no_operacao(OP_DIVISAO, $1, $3);
     }
     | termo MODULO fator
     {
         $$ = criar_no_operacao(OP_MODULO, $1, $3);
     }
     ;
fator: NUM_INTEIRO
     {
         $$ = criar_no_literal_int($1);
     }
     | NUM_REAL
     {
         $$ = criar_no_literal_float($1);
     }
     | CARACTER_LITERAL
     {
         $$ = criar_no_literal_char($1);
     }
     | VERDADEIRO
     {
         $$ = criar_no_literal_bool(1);
     }
     | FALSO
     {
         $$ = criar_no_literal_bool(0);
     }
     | IDENTIFICADOR
     {
         $$ = criar_no_identificador($1);
     }
     | IDENTIFICADOR ABRE_COLCHETES expressao FECHA_COLCHETES
     {
         $$ = criar_no_acesso_vetor($1, $3);
     }
     | chamada_funcao
     {
         $$ = $1;
     }
     | ABRE_PARENTESES expressao FECHA_PARENTESES
     {
         $$ = $2;
     }
     | MENOS fator %prec MENOS_UNARIO
     {
         $$ = criar_no_operacao_unaria(OP_MENOS_UNARIO, $2);
     }
     ;
```

### 3. Tratamento de Erros

#### Função de Erro
```c
void yyerror(const char* msg) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", yylineno, msg);
    fprintf(stderr, "Próximo ao token: '%s'\n", yytext);

    // Log adicional para debugging
    #ifdef DEBUG_PARSER
    fprintf(stderr, "Estado do parser: %d\n", yystate);
    imprimir_pilha_parser();
    #endif
}
```
#### Recuperação de Erros
```yacc
// Recuperação em comandos
comando: error PONTO_VIRGULA
       {
           yyerror("Comando inválido, recuperando...");
           $$ = criar_no_erro();
           yyerrok;
       }
       ;
// Recuperação em blocos
bloco: ABRE_CHAVES lista_comandos FECHA_CHAVES
     {
         $$ = criar_no_bloco($2);
     }
     | ABRE_CHAVES error FECHA_CHAVES
     {
         yyerror("Erro no bloco, recuperando...");
         $$ = criar_no_bloco_vazio();
         yyerrok;
     }
     ;
```

## Estrutura da AST

### Definição dos Nós
```c
// Em ast.h
typedef enum {
    NO_PROGRAMA,
    NO_FUNCAO,
    NO_PARAMETRO,
    NO_BLOCO,
    NO_DECLARACAO,
    NO_ATRIBUICAO,
    NO_SE,
    NO_PARA,
    NO_ENQUANTO,
    NO_ESCOLHA,
    NO_CASO,
    NO_RETORNE,
    NO_CHAMADA_FUNCAO,
    NO_OPERACAO_BINARIA,
    NO_OPERACAO_UNARIA,
    NO_LITERAL_INT,
    NO_LITERAL_FLOAT,
    NO_LITERAL_CHAR,
    NO_LITERAL_BOOL,
    NO_IDENTIFICADOR,
    NO_ACESSO_VETOR,
    NO_LISTA
} TipoNo;

typedef struct AST_Node {
    TipoNo tipo;
    int linha;

    union {
        // Nó de programa
        struct {
            struct AST_Node* funcoes;
        } programa;
        
        // Nó de função
        struct {
            int tipo_retorno;
            char* nome;
            struct AST_Node* parametros;
            struct AST_Node* corpo;
        } funcao;
        
        // Nó de operação binária
        struct {
            int operador;
            struct AST_Node* esquerda;
            struct AST_Node* direita;
        } operacao_binaria;
        
        // Nó de literal
        struct {
            int tipo_literal;
            union {
                int intval;
                float realval;
                char charval;
                int boolval;
            } valor;
        } literal;
        
        // Nó de identificador
        struct {
            char* nome;
        } identificador;
        
        // Nó de lista (genérico)
        struct {
            struct AST_Node* item;
            struct AST_Node* proximo;
        } lista;
    } dados;

    struct AST_Node* proximo; // Para listas encadeadas
} AST_Node;
```

### Funções de Criação de Nós
```c
// Em ast.c
AST_Node* criar_no_programa(AST_Node* funcoes) {
    AST_Node* no = malloc(sizeof(AST_Node));
    no->tipo = NO_PROGRAMA;
    no->linha = yylineno;
    no->dados.programa.funcoes = funcoes;
    no->proximo = NULL;
    return no;
}

AST_Node* criar_no_operacao(int operador, AST_Node* esq, AST_Node* dir) {
    AST_Node* no = malloc(sizeof(AST_Node));
    no->tipo = NO_OPERACAO_BINARIA;
    no->linha = yylineno;
    no->dados.operacao_binaria.operador = operador;
    no->dados.operacao_binaria.esquerda = esq;
    no->dados.operacao_binaria.direita = dir;
    no->proximo = NULL;
    return no;
}

AST_Node* criar_no_literal_int(int valor) {
    AST_Node* no = malloc(sizeof(AST_Node));
    no->tipo = NO_LITERAL_INT;
    no->linha = yylineno;
    no->dados.literal.tipo_literal = TIPO_INT;
    no->dados.literal.valor.intval = valor;
    no->proximo = NULL;
    return no;
}
```
## Análise Semântica Integrada
### Verificação de Tipos
```yacc
expressao_aritmetica: expressao_aritmetica MAIS termo
                    {
                        // Verificar compatibilidade de tipos
                        int tipo1 = obter_tipo($1);
                        int tipo3 = obter_tipo($3);
                        
                        if (!tipos_compativeis_operacao(tipo1, tipo3, OP_SOMA)) {
                            yyerror("Tipos incompatíveis na operação de soma");
                        }
                        
                        $$ = criar_no_operacao(OP_SOMA, $1, $3);
                        definir_tipo($$, promover_tipos(tipo1, tipo3));
                    }
                    ;
```

### Verificação de Escopo
```yacc
IDENTIFICADOR: {
                   Simbolo* simbolo = buscar_simbolo($1);
                   if (simbolo == NULL) {
                       char msg[256];
                       sprintf(msg, "Variável '%s' não declarada", $1);
                       yyerror(msg);
                   }
                   $$ = criar_no_identificador($1);
                   if (simbolo) {
                       definir_tipo($$, simbolo->tipo);
                   }
               }
               ;
```

## Geração da AST

### Exemplo de AST Gerada

**Código Portugol:**
```portugol
programa {
    inteiro fatorial(inteiro n) {
        se (n <= 1) {
            retorne 1;
        } senao {
            retorne n * fatorial(n - 1);
        }
    }
    
    funcao inicio() {
        inteiro num = 5;
        escreva("Resultado: ", fatorial(num), "\n");
    }
}
```

**AST Resultante:**
```
NO_PROGRAMA
├── NO_FUNCAO (fatorial)
│   ├── tipo_retorno: TIPO_INT
│   ├── parametros: NO_PARAMETRO (n, TIPO_INT)
│   └── corpo: NO_BLOCO
│       └── NO_SE
│           ├── condicao: NO_OPERACAO_BINARIA (<=)
│           │   ├── esquerda: NO_IDENTIFICADOR (n)
│           │   └── direita: NO_LITERAL_INT (1)
│           ├── entao: NO_RETORNE
│           │   └── valor: NO_LITERAL_INT (1)
│           └── senao: NO_RETORNE
│               └── valor: NO_OPERACAO_BINARIA (*)
│                   ├── esquerda: NO_IDENTIFICADOR (n)
│                   └── direita: NO_CHAMADA_FUNCAO (fatorial)
│                       └── args: NO_OPERACAO_BINARIA (-)
│                           ├── esquerda: NO_IDENTIFICADOR (n)
│                           └── direita: NO_LITERAL_INT (1)
└── NO_FUNCAO (inicio)
    ├── tipo_retorno: TIPO_VOID
    ├── parametros: NULL
    └── corpo: NO_BLOCO
        ├── NO_DECLARACAO
        │   ├── tipo: TIPO_INT
        │   ├── nome: "num"
        │   └── valor: NO_LITERAL_INT (5)
        └── NO_CHAMADA_FUNCAO (escreva)
            └── args: [NO_LITERAL_STRING, NO_CHAMADA_FUNCAO, NO_LITERAL_STRING]
```

## Otimizações do Parser

### Eliminação de Recursão à Esquerda
```yacc
// Problema: recursão à esquerda
expressao: expressao MAIS termo
         | termo
         ;
// Solução: recursão à direita ou iteração
expressao: termo lista_operacoes
         ;
lista_operacoes: /* vazio */
               | MAIS termo lista_operacoes
               ;
```

### Redução de Conflitos
```yacc
// Usar precedência para resolver conflitos shift/reduce
%left MAIS MENOS
%left MULTIPLICACAO DIVISAO
%right MENOS_UNARIO
// Resolver conflito dangling-else
%nonassoc SENAO
%nonassoc SE
```

## Debugging e Testes

### Visualização da AST
```c
void imprimir_ast(AST_Node* no, int nivel) {
    if (!no) return;

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    switch (no->tipo) {
        case NO_PROGRAMA:
            printf("PROGRAMA\n");
            imprimir_ast(no->dados.programa.funcoes, nivel + 1);
            break;

        case NO_OPERACAO_BINARIA:
            printf("OPERACAO %s\n", nome_operador(no->dados.operacao_binaria.operador));
            imprimir_ast(no->dados.operacao_binaria.esquerda, nivel + 1);
            imprimir_ast(no->dados.operacao_binaria.direita, nivel + 1);
            break;

        case NO_LITERAL_INT:
            printf("INT: %d\n", no->dados.literal.valor.intval);
            break;

        // ... outros casos
    }

    imprimir_ast(no->proximo, nivel);
}
```
### Testes do Parser
```c
// Teste individual
void testar_expressao(const char* codigo, const char* esperado) {
    yy_scan_string(codigo);
    AST_Node* ast = NULL;
    
    if (yyparse() == 0) {
        char resultado[1000];
        ast_para_string(ast, resultado);
        
        if (strcmp(resultado, esperado) == 0) {
            printf("✓ '%s'\n", codigo);
        } else {
            printf("✗ '%s'\n  Esperado: %s\n  Obtido: %s\n", 
                   codigo, esperado, resultado);
        }
    } else {
        printf("✗ '%s' - Erro de parsing\n", codigo);
    }
}
int main() {
    testar_expressao("2 + 3 * 4", "SOMA(2, MULT(3, 4))");
    testar_expressao("(2 + 3) * 4", "MULT(SOMA(2, 3), 4)");
    return 0;
}
```

## Performance e Memória

### Gerenciamento de Memória
```c
void liberar_ast(AST_Node* no) {
    if (!no) return;

    switch (no->tipo) {
        case NO_PROGRAMA:
            liberar_ast(no->dados.programa.funcoes);
            break;

        case NO_OPERACAO_BINARIA:
            liberar_ast(no->dados.operacao_binaria.esquerda);
            liberar_ast(no->dados.operacao_binaria.direita);
            break;

        case NO_IDENTIFICADOR:
            free(no->dados.identificador.nome);
            break;

        // ... outros casos
    }

    liberar_ast(no->proximo);
    free(no);
}
```
### Otimização de Pilha
```c
// Configurar tamanho da pilha do parser
#define YYMAXDEPTH 10000
#define YYINITDEPTH 200
```

## Interface com Outras Fases

### Passagem para Análise Semântica
```c
int main() {
    if (yyparse() == 0) {
        printf("Parsing concluído com sucesso\n");

        // Análise semântica
        if (analisar_semantica(raiz_programa) == 0) {
            printf("Análise semântica OK\n");

            // Geração de código
            gerar_codigo(raiz_programa);
        }
    }

    liberar_ast(raiz_programa);
    return 0;
}
```

### Comunicação com Lexer
```c
// Parser solicita tokens do lexer
int token = yylex();
char* texto_token = yytext;
int linha_token = yylineno;
```

O analisador sintático é o coração do compilador, transformando a sequência linear de tokens em uma estrutura hierárquica (AST) que representa a estrutura lógica do programa. Sua implementação robusta garante que apenas programas sintaticamente corretos sejam aceitos e que a AST resultante seja adequada para as fases subsequentes de compilação.
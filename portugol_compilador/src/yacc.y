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
    struct AST* ast; // Campo para AST
    struct AST* bloco; // Adicionado para blocos de múltiplos filhos
}

%token PROGRAMA INICIO FIM LEIA ESCREVA
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTERE TIPO_LOGICO TIPO_VAZIO
%token SE SENAO ENTAO FIMSE
%token ABRECHAVE FECHACHAVE
%token ENQUANTO FACA FIMENQUANTO
%token IGUAL COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token SOMA SUB MUL DIV MODULO
%token ABREPAR FECHAPAR PONTOEVIRGULA VIRGULA
%token PARA
%token DOISPONTOS
%token FIMFUNCAO
%token <str> NUM ID STRING
%token FUNCAO RETORNE
%token <str> COMENTARIO_LINHA COMENTARIO_BLOCO
%token ESCOLHA CASO PARE CASO_CONTRARIO
%token INCREMENTO DECREMENTO
%type <ast> programa corpo_programa lista_funcoes funcao cabecalho_funcao lista_args args bloco bloco_conteudo comando declaracao leitura escrita atribuicao expressao lista_parametros parametros parametro chamada_funcao condicional senao_bloco
%type <inteiro> tipo
%type <ast> comentario
%type <ast> lista_ids
%type <ast> escolha caso lista_casos caso_contrario
%type <ast> incremento_decremento

// token Bitwise
%token OP_BITWISE_AND OP_BITWISE_NOT OP_BITWISE_OR OP_BITWISE_LEFT_SHIFT OP_BITWISE_RIGHT_SHIFT OP_BITWISE_XOR

%left SOMA SUB
%left MUL DIV MODULO


%%

programa: PROGRAMA ABRECHAVE corpo_programa FECHACHAVE { $$ = $3; };

corpo_programa: lista_funcoes INICIO bloco {
    raiz_ast = ast_cria(AST_PROGRAMA, NULL, 2, $1, $3);
    $$ = raiz_ast;
};

funcao:
    cabecalho_funcao bloco FIMFUNCAO {
        $$ = ast_cria(AST_FUNCAO, strdup($1->valor), 2, $1->filhos[0], $2);
    }
;

cabecalho_funcao:
    FUNCAO tipo ID ABREPAR lista_parametros FECHAPAR {
        // Insere a função ANTES do bloco, para permitir recursão
        Simbolo **parametros = NULL;
        if ($5->n_filhos > 0) {
            parametros = malloc(sizeof(Simbolo*) * $5->n_filhos);
            for (int i = 0; i < $5->n_filhos; i++) {
                parametros[i] = buscarSimbolo($5->filhos[i]->valor, escopo_atual + 1);
            }
        }
        inserirFuncao($3, $2, escopo_atual, $5->n_filhos, parametros);
        // Cria um nó AST para o cabeçalho (opcional, mas útil para manter a AST completa)
        $$ = ast_cria(AST_DECLARACAO, strdup($3), 1, $5);
    }
;

lista_args:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | args { $$ = $1; }
;

args:
    expressao { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | args VIRGULA expressao {
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
    | condicional { $$ = $1; }
    | escolha { $$ = $1; }
    | ENQUANTO ABREPAR expressao FECHAPAR ABRECHAVE bloco FECHACHAVE {
        $$ = ast_cria(AST_WHILE, NULL, 2, $3, $6);
    }
    | PARA ABREPAR declaracao PONTOEVIRGULA expressao PONTOEVIRGULA expressao FECHAPAR ABRECHAVE bloco FECHACHAVE {
        $$ = ast_cria(AST_FOR, NULL, 4, $3, $5, $7, $10);
    }
    | RETORNE expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("return"), 1, $2);
    }
    | chamada_funcao { $$ = $1; }
    | incremento_decremento { $$ = $1; }
;

condicional:
    SE ABREPAR expressao FECHAPAR ABRECHAVE bloco FECHACHAVE senao_bloco {
        // se (condicao) { bloco } else { ... } ou se (condicao) { bloco }
        if ($8 != NULL) { // se houver senao_bloco (pode ser senao ou senao se)
            $$ = ast_cria(AST_IF, NULL, 3, $3, $6, $8);
        } else { // apenas se
            $$ = ast_cria(AST_IF, NULL, 2, $3, $6);
        }
    }
;

senao_bloco:
    SENAO ABRECHAVE bloco FECHACHAVE { $$ = $3; } // senao { bloco }
    | SENAO SE ABREPAR expressao FECHAPAR ABRECHAVE bloco FECHACHAVE senao_bloco {
        // senao se (condicao) { bloco } ...
        // Criamos um novo AST_IF para o "senao se", e ele pode ter um "senao_bloco" como seu próprio else
        if ($9 != NULL) {
            $$ = ast_cria(AST_IF, NULL, 3, $4, $7, $9);
        } else {
            $$ = ast_cria(AST_IF, NULL, 2, $4, $7);
        }
    }
    | /* vazio */ { $$ = NULL; } // Para o caso de não ter senao
;

chamada_funcao:
    ID ABREPAR lista_args FECHAPAR { $$ = ast_cria(AST_CHAMADA_FUNCAO, strdup($1), 1, $3); }
;

declaracao:
    tipo lista_ids {
        for (int i = 0; i < $2->n_filhos; i++) {
            inserirSimbolo($2->filhos[i]->valor, $1, escopo_atual);
        }
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, ast_cria(AST_TIPO, strdup($1 == TIPO_INT ? "int" : $1 == TIPO_FLOAT ? "float" : $1 == TIPO_CHAR ? "char" : "bool"), 0), $2);
    }
    | tipo lista_ids IGUAL expressao {
        for (int i = 0; i < $2->n_filhos; i++) {
            inserirSimbolo($2->filhos[i]->valor, $1, escopo_atual);
            marcarVariavelInicializada($2->filhos[i]->valor, escopo_atual);
        }
        AST* atribuicao = ast_cria(AST_ATRIBUICAO, NULL, 2, $2->filhos[0], $4);
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, ast_cria(AST_TIPO, strdup($1 == TIPO_INT ? "int" : $1 == TIPO_FLOAT ? "float" : $1 == TIPO_CHAR ? "char" : "bool"), 0), atribuicao);
    }
;

lista_ids:
    ID { $$ = ast_cria(AST_BLOCO, NULL, 1, ast_cria(AST_ID, strdup($1), 0)); }
    | lista_ids VIRGULA ID {
        int n = $1->n_filhos + 1;
        AST** filhos = malloc(sizeof(AST*) * n);
        for (int i = 0; i < $1->n_filhos; i++) filhos[i] = $1->filhos[i];
        filhos[n-1] = ast_cria(AST_ID, strdup($3), 0);
        AST* novo = ast_cria(AST_BLOCO, NULL, 0);
        novo->n_filhos = n;
        novo->filhos = filhos;
        $$ = novo;
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
    LEIA ABREPAR ID FECHAPAR {
        checar_declaracao($3);
        marcarVariavelInicializada($3, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        $$ = ast_cria(AST_LEITURA, NULL, 1, id);
    }
;

escrita:
    ESCREVA ABREPAR ID FECHAPAR {
        checar_declaracao($3);
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        id->tipo_expr = buscar_tipo_variavel($3); // Propaga o tipo!
        $$ = ast_cria(AST_ESCRITA, NULL, 1, id);
    }
    | ESCREVA ABREPAR STRING FECHAPAR {
        AST* str = ast_cria(AST_STRING, strdup($3), 0);
        $$ = ast_cria(AST_ESCRITA, NULL, 1, str);
    }
    | ESCREVA ABREPAR expressao FECHAPAR {
        $$ = ast_cria(AST_ESCRITA, NULL, 1, $3);
    }
    | ESCREVA ABREPAR NUM FECHAPAR {
        AST* num = ast_cria(AST_NUM, strdup($3), 0);
        $$ = ast_cria(AST_ESCRITA, NULL, 1, num);
    }
;

atribuicao:
    ID IGUAL expressao {
        checar_declaracao($1);
        marcarVariavelInicializada($1, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_ATRIBUICAO, NULL, 2, id, $3);
    }
;

expressao:
    NUM {
        AST* num = ast_cria(AST_NUM, strdup($1), 0);
        num->tipo_expr = TIPO_INT; // ou TIPO_FLOAT se detectar ponto
        $$ = num;
    }
    | SUB NUM {
        char* neg = (char*)malloc(strlen($2) + 2);
        sprintf(neg, "-%s", $2);
        AST* num = ast_cria(AST_NUM, neg, 0);
        num->tipo_expr = TIPO_INT;
        $$ = num;
        free(neg);
    }
    | ID {
        checar_declaracao($1);
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        id->tipo_expr = buscar_tipo_variavel($1);
        $$ = id;
    }
    | expressao SOMA expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("+"), 2, $1, $3);
        novo->tipo_expr = ($1->tipo_expr == TIPO_FLOAT || $3->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        $$ = novo;
    }
    | expressao SUB expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("-"), 2, $1, $3);
        novo->tipo_expr = ($1->tipo_expr == TIPO_FLOAT || $3->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        $$ = novo;
    }
    | expressao COMPARA expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("=="), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao MENOR expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("<"), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao MAIOR expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup(">"), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao MENOR_IGUAL expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("<="), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao MAIOR_IGUAL expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup(">="), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao DIFERENTE expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("!="), 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | ID ABREPAR lista_args FECHAPAR {
        Simbolo *func = buscarSimbolo($1, 0);
        if (!func) {
            fprintf(stderr, "[ERRO SEMÂNTICO] Função '%s' não declarada!\n", $1);
            exit(1);
        }
        if (func->n_parametros != $3->n_filhos) {
            fprintf(stderr, "[ERRO SEMÂNTICO] Função '%s' espera %d parâmetros, mas recebeu %d.\n", $1, func->n_parametros, $3->n_filhos);
            exit(1);
        }
        for (int i = 0; i < func->n_parametros; i++) {
            int tipo_esperado = func->parametros[i]->tipo;
            int tipo_recebido = $3->filhos[i]->tipo_expr;
            if (tipo_esperado != tipo_recebido) {
                fprintf(stderr, "[ERRO SEMÂNTICO] Parâmetro %d da função '%s' espera tipo %d, mas recebeu tipo %d.\n", i+1, $1, tipo_esperado, tipo_recebido);
                exit(1);
            }
        }
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        AST* call = ast_cria(AST_EXPRESSAO, NULL, 2, id, $3);
        call->tipo_expr = func->tipo_retorno;
        $$ = call;
    }
    | expressao MUL expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("*"), 2, $1, $3);
        novo->tipo_expr = ($1->tipo_expr == TIPO_FLOAT || $3->tipo_expr == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INT;
        $$ = novo;
    }
    | expressao DIV expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("/"), 2, $1, $3);
        novo->tipo_expr = TIPO_FLOAT; // divisão sempre resulta em float
        $$ = novo;
    }
    | expressao MODULO expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("%"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | ID INCREMENTO {
        checar_declaracao($1);
        AST* id_node = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_INCREMENTO, NULL, 1, id_node); // Reusing AST_INCREMENTO type
        $$->tipo_expr = buscar_tipo_variavel($1); // Propagate type
    }
    | ID DECREMENTO {
        checar_declaracao($1);
        AST* id_node = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_DECREMENTO, NULL, 1, id_node); // Reusing AST_DECREMENTO type
        $$->tipo_expr = buscar_tipo_variavel($1); // Propagate type
    }
;

lista_parametros:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | parametros { $$ = $1; }
;

parametros:
    parametro { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | parametros VIRGULA parametro {
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

escolha:
    ESCOLHA ABREPAR expressao FECHAPAR ABRECHAVE lista_casos caso_contrario FECHACHAVE {
        $$ = ast_cria(AST_ESCOLHA, NULL, 2, $3, ast_cria(AST_BLOCO, NULL, 2, $6, $7));
    }
;

lista_casos:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | lista_casos caso { 
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

caso:
    CASO expressao DOISPONTOS bloco_conteudo PARE {
        $$ = ast_cria(AST_CASO, NULL, 2, $2, $4);
    }
;

caso_contrario:
    /* vazio */ { $$ = ast_cria(AST_BLOCO, NULL, 0); }
    | CASO_CONTRARIO DOISPONTOS bloco_conteudo {
        $$ = ast_cria(AST_CASO_CONTRARIO, NULL, 1, $3);
    }
;

incremento_decremento:
    ID INCREMENTO {
        checar_declaracao($1);
        AST* id_node = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_INCREMENTO, NULL, 1, id_node);
    }
    | ID DECREMENTO {
        checar_declaracao($1);
        AST* id_node = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_DECREMENTO, NULL, 1, id_node);
    }
;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}
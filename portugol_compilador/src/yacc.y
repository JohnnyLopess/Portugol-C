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
#define TIPO_CAD 5

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
%token TIPO_INTEIRO TIPO_REAL TIPO_CARACTER TIPO_LOGICO TIPO_VAZIO TIPO_CADEIA
%token SE SENAO ENTAO FIMSE
%token ABRECHAVE FECHACHAVE
%token ABRECOLCHETE FECHACOLCHETE
%token ENQUANTO FACA FIMENQUANTO
%token IGUAL COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token SOMA SUB MUL DIV MODULO
%token ABREPAR FECHAPAR PONTOEVIRGULA VIRGULA
%token PARA
%token DOISPONTOS
%token <str> NUM ID STRING
%token FUNCAO RETORNE
%token <str> COMENTARIO_LINHA COMENTARIO_BLOCO
%token ESCOLHA CASO PARE CASO_CONTRARIO
%token INCREMENTO DECREMENTO
%token E_LOGICO
%token OU_LOGICO 
%token NAO_LOGICO 
%type <ast> programa corpo_programa lista_funcoes funcao cabecalho_funcao lista_args args bloco bloco_conteudo comando declaracao leitura escrita atribuicao expressao lista_parametros parametros parametro chamada_funcao condicional senao_bloco
%type <inteiro> tipo
%type <ast> comentario
%type <ast> lista_ids
%type <ast> escolha caso lista_casos caso_contrario
%type <ast> incremento_decremento
%type <ast> lista_escrita_args escrita_arg
%type <ast> iteracao_for
%type <ast> declaracao_multipla_inicializacao // NOVO: para declarações com múltiplas inicializações

// token Bitwise
%token OP_BITWISE_AND OP_BITWISE_NOT OP_BITWISE_OR OP_BITWISE_LEFT_SHIFT OP_BITWISE_RIGHT_SHIFT OP_BITWISE_XOR

%left OU_LOGICO
%left E_LOGICO
%left COMPARA DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%right NAO_LOGICO
%left SOMA SUB
%left MUL DIV MODULO



%%

programa: PROGRAMA ABRECHAVE corpo_programa FECHACHAVE { $$ = $3; };

corpo_programa: lista_funcoes FUNCAO INICIO ABREPAR FECHAPAR ABRECHAVE bloco FECHACHAVE {
    raiz_ast = ast_cria(AST_PROGRAMA, NULL, 2, $1, $7);
    $$ = raiz_ast;
};

funcao:
    cabecalho_funcao ABRECHAVE bloco FECHACHAVE {
        $$ = ast_cria(AST_FUNCAO, strdup($1->valor), 2, $1->filhos[0], $3);
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
    | FUNCAO ID ABREPAR lista_parametros FECHAPAR {
        // Para funcoes com o tipo omitido, sendo o retorno do tipo void
        Simbolo **parametros = NULL;
        int tipo = TIPO_VOID;

        if ($4->n_filhos > 0) {
            parametros = malloc(sizeof(Simbolo*) * $4->n_filhos);
            for (int i = 0; i < $4->n_filhos; i++) {
                parametros[i] = buscarSimbolo($4->filhos[i]->valor, escopo_atual + 1);
            }
        }
        inserirFuncao($2, tipo, escopo_atual, $4->n_filhos, parametros);
        // Cria um nó AST para o cabeçalho (opcional, mas útil para manter a AST completa)
        $$ = ast_cria(AST_DECLARACAO, strdup($2), 1, $4);
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
    | PARA ABREPAR declaracao PONTOEVIRGULA expressao PONTOEVIRGULA iteracao_for FECHAPAR ABRECHAVE bloco FECHACHAVE {
        $$ = ast_cria(AST_FOR, NULL, 4, $3, $5, $7, $10);
    }
    | RETORNE expressao {
        $$ = ast_cria(AST_EXPRESSAO, strdup("return"), 1, $2);
    }
    | chamada_funcao { $$ = $1; }
    | incremento_decremento { $$ = $1; }
;

iteracao_for:
    expressao { $$ = $1; }
    | atribuicao { $$ = $1; }
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
            const char* tipo_str;
            switch($1) {
                case TIPO_INT: tipo_str = "int"; break;
                case TIPO_FLOAT: tipo_str = "float"; break;
                case TIPO_CHAR: tipo_str = "char"; break;
                case TIPO_BOOL: tipo_str = "bool"; break;
                case TIPO_CAD: tipo_str = "cadeia"; break;
                default: tipo_str = "void";
            }
            $$ = ast_cria(AST_DECLARACAO, NULL, 2, ast_cria(AST_TIPO, strdup(tipo_str), 0), $2);
    }
    | tipo ID IGUAL expressao {
        inserirSimbolo($2, $1, escopo_atual);
        marcarVariavelInicializada($2, escopo_atual);
        AST* atribuicao = ast_cria(AST_ATRIBUICAO, NULL, 2, ast_cria(AST_ID, strdup($2), 0), $4);
        const char* tipo_str;
        switch($1) {
            case TIPO_INT: tipo_str = "int"; break;
            case TIPO_FLOAT: tipo_str = "float"; break;
            case TIPO_CHAR: tipo_str = "char"; break;
            case TIPO_BOOL: tipo_str = "bool"; break;
            case TIPO_CAD: tipo_str = "cadeia"; break;
            default: tipo_str = "void";
        }
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, ast_cria(AST_TIPO, strdup(tipo_str), 0), atribuicao);
    }
    | tipo ID ABRECOLCHETE NUM FECHACOLCHETE {
        inserirSimbolo($2, $1, escopo_atual);
        AST* tamanho = ast_cria(AST_NUM, strdup($4), 0);
        AST* id = ast_cria(AST_ID, strdup($2), 0);
        $$ = ast_cria(AST_VETOR_DECLARACAO, NULL, 3, 
                            ast_cria(AST_TIPO, strdup($1 == TIPO_INT ? "int" : $1 == TIPO_FLOAT ? "float" : $1 == TIPO_CHAR ? "char" : "bool"), 0), 
                            id, tamanho);
    }
    // NOVO: Regra para declaração com múltiplas inicializações (e.g., inteiro x = 10, y = 20)
    | tipo declaracao_multipla_inicializacao {
        AST* type_node = ast_cria(AST_TIPO, strdup($1 == TIPO_INT ? "int" : $1 == TIPO_FLOAT ? "float" : $1 == TIPO_CHAR ? "char" : "bool"), 0);
        // $2 é um AST_BLOCO contendo nós AST_ATRIBUICAO
        AST* assignments_block = $2; 

        // Cria um novo AST_BLOCO para conter as declarações + atribuições
        AST* combined_declarations = ast_cria(AST_BLOCO, NULL, 0);
        combined_declarations->n_filhos = assignments_block->n_filhos;
        combined_declarations->filhos = assignments_block->filhos; // Transfere a propriedade dos filhos

        for (int i = 0; i < combined_declarations->n_filhos; i++) {
            AST* assign_node = combined_declarations->filhos[i]; // Este é um AST_ATRIBUICAO
            if (assign_node && assign_node->tipo == AST_ATRIBUICAO && assign_node->filhos[0] && assign_node->filhos[0]->tipo == AST_ID) {
                inserirSimbolo(assign_node->filhos[0]->valor, $1, escopo_atual);
                marcarVariavelInicializada(assign_node->filhos[0]->valor, escopo_atual);
            } else {
                fprintf(stderr, "[ERRO SEMÂNTICO] Estrutura de atribuição inesperada em declaração múltipla.\n");
                exit(1);
            }
        }
        $$ = ast_cria(AST_DECLARACAO, NULL, 2, type_node, combined_declarations);
    }
;

// NOVO: Define a regra para múltiplas inicializações na mesma linha
declaracao_multipla_inicializacao:
    ID IGUAL expressao {
        AST* id_node = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_BLOCO, NULL, 1, ast_cria(AST_ATRIBUICAO, NULL, 2, id_node, $3));
    }
    | declaracao_multipla_inicializacao VIRGULA ID IGUAL expressao {
        int n = $1->n_filhos + 1;
        // Realloc precisa ser feito no pai, então precisamos criar um novo bloco aqui
        // ou $1 já deve ser um bloco que podemos reallocar.
        // A lógica do realloc está implícita no ast_cria do bloco pai.
        // Aqui, $1 é o AST_BLOCO que já contém as atribuições anteriores.
        AST** filhos = realloc($1->filhos, sizeof(AST*) * n);
        AST* id_node = ast_cria(AST_ID, strdup($3), 0);
        filhos[n-1] = ast_cria(AST_ATRIBUICAO, NULL, 2, id_node, $5);
        $1->n_filhos = n;
        $1->filhos = filhos;
        $$ = $1;
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
    | TIPO_CARACTER { $$ = TIPO_CHAR; }
    | TIPO_LOGICO    { $$ = TIPO_BOOL; }
    | TIPO_VAZIO     { $$ = TIPO_VOID; }
    | TIPO_CADEIA   { $$ = TIPO_CAD; }
;

leitura:
    LEIA ABREPAR ID FECHAPAR {
        checar_declaracao($3);
        marcarVariavelInicializada($3, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        $$ = ast_cria(AST_LEITURA, NULL, 1, id);
    }
    | LEIA ABREPAR ID ABRECOLCHETE expressao FECHACOLCHETE FECHAPAR {
        checar_declaracao($3);
        marcarVariavelInicializada($3, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($3), 0);
        AST* acesso = ast_cria(AST_VETOR_ACESSO, NULL, 2, id, $5);
        $$ = ast_cria(AST_LEITURA, NULL, 1, acesso);
    }
;

escrita:

    ESCREVA ABREPAR lista_escrita_args FECHAPAR {
            $$ = ast_cria(AST_ESCRITA, NULL, 1, $3);
    }
;

lista_escrita_args:
    escrita_arg { $$ = ast_cria(AST_BLOCO, NULL, 1, $1); }
    | lista_escrita_args VIRGULA escrita_arg {
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

escrita_arg:
    expressao { $$ = $1; }
    | STRING { $$ = ast_cria(AST_STRING, strdup($1), 0); }
;

atribuicao:
    ID IGUAL expressao {
        checar_declaracao($1);
        marcarVariavelInicializada($1, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        $$ = ast_cria(AST_ATRIBUICAO, NULL, 2, id, $3);
    }
    | ID ABRECOLCHETE expressao FECHACOLCHETE IGUAL expressao {
        checar_declaracao($1);
        marcarVariavelInicializada($1, escopo_atual);
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        AST* acesso = ast_cria(AST_VETOR_ACESSO, NULL, 2, id, $3);
        $$ = ast_cria(AST_ATRIBUICAO, NULL, 2, acesso, $6);
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
    | ID ABRECOLCHETE expressao FECHACOLCHETE {
        checar_declaracao($1);
        AST* id = ast_cria(AST_ID, strdup($1), 0);
        AST* acesso = ast_cria(AST_VETOR_ACESSO, NULL, 2, id, $3);
        acesso->tipo_expr = buscar_tipo_variavel($1);
        $$ = acesso;
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
    | expressao OP_BITWISE_AND expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("&"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | OP_BITWISE_NOT expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("~"), 1, $2);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | expressao OP_BITWISE_OR expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("|"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | expressao OP_BITWISE_LEFT_SHIFT expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup("<<"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | expressao OP_BITWISE_RIGHT_SHIFT expressao {
        AST* novo = ast_cria(AST_EXPRESSAO, strdup(">>"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;
    }
    | expressao OP_BITWISE_XOR expressao {
        AST*novo = ast_cria(AST_EXPRESSAO, strdup("^"), 2, $1, $3);
        novo->tipo_expr = TIPO_INT;
        $$ = novo;

    }
    | STRING {
            AST* str_node = ast_cria(AST_STRING, strdup($1), 0);
            str_node->tipo_expr = TIPO_CAD;
            $$ = str_node;
    }
    | ABREPAR expressao FECHAPAR {
        $$ = $2; // Parenthesized expressions
    }
    | expressao E_LOGICO expressao {
        // "e" lógico (AND)
        AST* novo = ast_cria(AST_AND, NULL, 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | expressao OU_LOGICO expressao {
        // "ou" lógico (OR)
        AST* novo = ast_cria(AST_OR, NULL, 2, $1, $3);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
    }
    | NAO_LOGICO expressao {
        // "nao" lógico (NOT)
        AST* novo = ast_cria(AST_NOT, NULL, 1, $2);
        novo->tipo_expr = TIPO_BOOL;
        $$ = novo;
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

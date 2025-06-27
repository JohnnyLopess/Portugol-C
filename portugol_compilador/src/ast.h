#ifndef AST_H
#define AST_H
#include <stdio.h>

typedef enum {
    AST_PROGRAMA,
    AST_BLOCO,
    AST_DECLARACAO,
    AST_TIPO,
    AST_LEITURA,
    AST_ESCRITA,
    AST_ATRIBUICAO,
    AST_IF,
    AST_WHILE,
    AST_FOR,
    AST_EXPRESSAO,
    AST_NUM,
    AST_ID,
    AST_FUNCAO,
    AST_STRING,
    AST_CHAMADA_FUNCAO,
    AST_COMENTARIO,
    AST_ESCOLHA,
    AST_CASO,
    AST_CASO_CONTRARIO,
    AST_INCREMENTO,
    AST_DECREMENTO,
    AST_VETOR_DECLARACAO,
    AST_VETOR_ACESSO,
    AST_AND,
    AST_OR, 
    AST_NOT  
} ASTTipo;

typedef struct AST {
    ASTTipo tipo;
    char* valor; // Para números, ids, strings, operadores
    struct AST** filhos;
    int n_filhos;
    int tipo_expr;
} AST;

AST* ast_cria(ASTTipo tipo, char* valor, int n_filhos, ...);
void ast_libera(AST* no);
void ast_gera_c(AST* no, FILE* saida, int nivel_indent);
AST* otimiza_ast_propagacao_constantes(AST* no);
AST* otimiza_ast_dead_code(AST* no);

#endif
#include <stdio.h>
#include "ast.h"
#include "simbolos.h"

int yyparse();
extern AST *raiz_ast; // Defina raiz_ast como global no yacc.y

int main()
{
    printf("Iniciando o tradutor Portugol → C...\n");
    yyparse();
    FILE *saida = fopen("saida.c", "w");
    raiz_ast = otimiza_ast_propagacao_constantes(raiz_ast);
    raiz_ast = otimiza_ast_dead_code(raiz_ast);
    ast_gera_c(raiz_ast, saida, 0);
    fclose(saida);
    verificar_variaveis();
    ast_libera(raiz_ast);
    return 0;
}

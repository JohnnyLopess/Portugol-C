#include <stdio.h>
#include "ast.h" 

// Função gerada automaticamente pelo Bison
int yyparse();  
extern AST* raiz_ast; // Defina raiz_ast como global no yacc.y

int main() {
    printf("Iniciando o tradutor Portugol → C...\n");
    yyparse();
    FILE* saida = fopen("saida.c", "w");
    ast_gera_c(raiz_ast, saida, 0);
    fclose(saida);
    ast_libera(raiz_ast);
    return 0;
}

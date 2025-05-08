#include <stdio.h>

// Função gerada automaticamente pelo Bison
int yyparse();  

int main() {
    printf("Iniciando o tradutor Portugol → C...\n");
    yyparse();  // Inicia a análise sintática
    return 0;
}

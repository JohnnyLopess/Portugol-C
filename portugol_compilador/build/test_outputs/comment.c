#include <stdio.h>

int main() {
    float numero;
    //este é um número real
    char letra;
    int idade;
    /*este bloco tem operações de leia
 e escreva*/
    printf("Digite um número real: ");
    scanf("%f", &numero);
    printf("Digite uma letra: ");
    scanf(" %c", &letra);
    //teste
    printf("Digite sua idade: ");
    scanf("%d", &idade);
    //resultado
    printf("%f\n", numero);
    printf("%c\n", letra);
    printf("%d\n", idade);
    return 0;
}

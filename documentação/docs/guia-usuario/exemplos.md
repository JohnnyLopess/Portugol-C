# Exemplos de Código

Esta seção apresenta diversos exemplos práticos de programas em Portugol e sua tradução para C.

## Programas Básicos

### Hello World

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            escreva("Hello, World!")
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        printf("Hello, World!");
        return 0;
    }
    ```

### Variáveis e Tipos

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro idade
            caracter inicial
            logico ativo

            idade = 25
            inicial = 65  // 'A'
            ativo = 1     // verdadeiro

            escreva("Idade: ", idade)
            escreva("Inicial: ", inicial)
            escreva("Ativo: ", ativo)
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int idade;
        char inicial;
        bool ativo;
        idade = 25;
        inicial = 65;
        ativo = 1;
        printf("Idade: %d\n", idade);
        printf("Inicial: %c\n", inicial);
        printf("Ativo: %d\n", ativo);
        return 0;
    }
    ```

## Estruturas de Controle

### Condicionais

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro numero
            leia(numero)

            se (numero > 0) {
                escreva("Número positivo")
            } senao se (numero < 0) {
                escreva("Número negativo")
            } senao {
                escreva("Número é zero")
            }
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int numero;
        scanf("%d", &numero);
        if (numero > 0) {
            printf("Número positivo");
        } else if (numero < 0) {
            printf("Número negativo");
        } else {
            printf("Número é zero");
        }
        return 0;
    }
    ```

### Laço While

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro contador
            contador = 1

            enquanto (contador <= 5) {
                escreva("Contador: ", contador)
                contador = contador + 1
            }
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int contador;
        contador = 1;
        while (contador <= 5) {
            printf("Contador: %d\n", contador);
            contador = contador + 1;
        }
        return 0;
    }
    ```

### Laço For

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro i

            para (inteiro i = 1; i <= 10; i++) {
                escreva("Número: ", i)
            }
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        for (int i = 1; i <= 10; i++) {
            printf("Número: %d\n", i);
        }
        return 0;
    }
    ```

## Vetores (Arrays)

### Vetor de Inteiros

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro numeros[5]
            inteiro i

            // Preenchendo o vetor
            para (inteiro i = 0; i < 5; i++) {
                numeros[i] = i * 10
            }

            // Exibindo o vetor
            para (inteiro i = 0; i < 5; i++) {
                escreva("numeros[", i, "] = ", numeros[i])
            }
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int numeros[5];
        int i;
        for (int i = 0; i < 5; i++) {
            numeros[i] = i * 10;
        }
        for (int i = 0; i < 5; i++) {
            printf("numeros[%d] = %d\n", i, numeros[i]);
        }
        return 0;
    }
    ```

### Vetor de Reais

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            real notas[3]
            real media

            notas[0] = 8.5
            notas[1] = 9.0
            notas[2] = 7.5

            media = (notas[0] + notas[1] + notas[2]) / 3
            escreva("Média: ", media)
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        float notas[3];
        float media;
        notas[0] = 8.5;
        notas[1] = 9.0;
        notas[2] = 7.5;
        media = (notas[0] + notas[1] + notas[2]) / 3;
        printf("Média: %f\n", media);
        return 0;
    }
    ```

## Operações Avançadas

### Operadores Bitwise

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro a, b, resultado
            a = 12  // 1100 em binário
            b = 7   // 0111 em binário

            resultado = a & b  // AND
            escreva("AND: ", resultado)

            resultado = a | b  // OR
            escreva("OR: ", resultado)

            resultado = a ^ b  // XOR
            escreva("XOR: ", resultado)
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int a, b, resultado;
        a = 12;
        b = 7;
        resultado = a & b;
        printf("AND: %d\n", resultado);
        resultado = a | b;
        printf("OR: %d\n", resultado);
        resultado = a ^ b;
        printf("XOR: %d\n", resultado);
        return 0;
    }
    ```

### Incremento e Decremento

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            inteiro contador
            contador = 5

            escreva("Valor inicial: ", contador)
            contador++
            escreva("Após incremento: ", contador)
            contador--
            escreva("Após decremento: ", contador)
        }
    }
    ```

=== "C Gerado"
    ```c
    #include <stdio.h>

    int main() {
        int contador;
        contador = 5;
        printf("Valor inicial: %d\n", contador);
        contador++;
        printf("Após incremento: %d\n", contador);
        contador--;
        printf("Após decremento: %d\n", contador);
        return 0;
    }
    ```

## Programas Completos

### Calculadora Simples

=== "Portugol"
    ```portugol
    programa {
        funcao inicio() {
            real num1, num2, resultado
            caracter operacao

            escreva("Digite o primeiro número: ")
            leia(num1)
            escreva("Digite a operação (+, -, *, /): ")
            leia(operacao)
            escreva("Digite o segundo número: ")
            leia(num2)

            escolha(operacao) {
                caso '+':
                    resultado = num1 + num2
                pare
                caso '-':
                    resultado = num1 - num2
                pare
                caso '*':
                    resultado = num1 * num2
                pare
                caso '/':
                    se (num2 != 0) {
                        resultado = num1 / num2
                    } senao {
                        escreva("Erro: Divisão por zero!")
                        retorne 1
                    }
                pare
                caso contrario:
                    escreva("Operação inválida!")
                    retorne 1
            }

            escreva("Resultado: ", resultado)
        }
    }
    ```

!!! note "Nota sobre os Exemplos"
    Todos estes exemplos foram testados e validados pelo nosso sistema automatizado de testes. Você pode encontrar mais exemplos na pasta `exemplos/` do repositório.
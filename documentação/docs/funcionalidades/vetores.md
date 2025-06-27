# Vetores

O Portugol-C oferece suporte completo a vetores (arrays) para todos os tipos de dados suportados. Vetores permitem armazenar múltiplos valores do mesmo tipo em uma única estrutura de dados.

## Declaração de Vetores

### Sintaxe Básica
```portugol
tipo nome_vetor[tamanho];
tipo nome_vetor[tamanho] = {valores_iniciais};
```

### Exemplos de Declaração

```portugol
// Declaração simples
inteiro numeros[10];
real notas[5];
caracter nome[50];
logico flags[8];
// Declaração com inicialização
inteiro pares[5] = {2, 4, 6, 8, 10};
real temperaturas[3] = {25.5, 30.0, 28.2};
caracter vogais[5] = {'a', 'e', 'i', 'o', 'u'};
logico estados[4] = {verdadeiro, falso, verdadeiro, falso};
```

## Tipos de Vetores Suportados

### Vetores de Inteiros

```portugol
programa {
    funcao inicio() {
        inteiro numeros[5];
        
        // Preenchimento manual
        numeros[0] = 10;
        numeros[1] = 20;
        numeros[2] = 30;
        numeros[3] = 40;
        numeros[4] = 50;
        
        // Exibição
        para (inteiro i = 0; i < 5; i++) {
            escreva("numeros[", i, "] = ", numeros[i], "\n");
        }
    }
}
```

### Vetores de Reais

```portugol
programa {
    funcao inicio() {
        real precos[4] = {15.99, 25.50, 8.75, 42.30};
        real soma = 0.0;
        
        // Calcular soma
        para (inteiro i = 0; i < 4; i++) {
            soma = soma + precos[i];
        }
        
        real media = soma / 4.0;
        escreva("Média dos preços: ", media, "\n");
    }
}
```

### Vetores de Caracteres

```portugol
programa {
    funcao inicio() {
        caracter palavra[10] = {'P', 'o', 'r', 't', 'u', 'g', 'o', 'l', '\0'};
        
        // Exibir como string
        escreva("Palavra: ");
        inteiro i = 0;
        enquanto (palavra[i] != '\0') {
            escreva(palavra[i]);
            i++;
        }
        escreva("\n");
        
        // Contar caracteres
        inteiro tamanho = 0;
        enquanto (palavra[tamanho] != '\0') {
            tamanho++;
        }
        escreva("Tamanho: ", tamanho, "\n");
    }
}
```

### Vetores Lógicos

```portugol
programa {
    funcao inicio() {
        logico respostas[5];
        inteiro corretas = 0;
        
        // Simular respostas de um quiz
        respostas[0] = verdadeiro;
        respostas[1] = falso;
        respostas[2] = verdadeiro;
        respostas[3] = verdadeiro;
        respostas[4] = falso;
        
        // Contar respostas corretas
        para (inteiro i = 0; i < 5; i++) {
            se (respostas[i] == verdadeiro) {
                corretas++;
            }
        }
        
        escreva("Respostas corretas: ", corretas, " de 5\n");
    }
}
```

## Operações com Vetores

### Leitura de Dados

```portugol
programa {
    funcao inicio() {
        inteiro tamanho = 5;
        real valores[5];
        
        // Ler valores do usuário
        escreva("Digite ", tamanho, " valores:\n");
        para (inteiro i = 0; i < tamanho; i++) {
            escreva("Valor ", (i + 1), ": ");
            leia(valores[i]);
        }
        
        // Exibir valores lidos
        escreva("\nValores digitados:\n");
        para (inteiro i = 0; i < tamanho; i++) {
            escreva(valores[i], " ");
        }
        escreva("\n");
    }
}
```

### Busca em Vetores

```portugol
programa {
    inteiro buscar(inteiro vetor[], inteiro tamanho, inteiro valor) {
        para (inteiro i = 0; i < tamanho; i++) {
            se (vetor[i] == valor) {
                retorne i; // Retorna o índice
            }
        }
        retorne -1; // Não encontrado
    }
    
    funcao inicio() {
        inteiro numeros[8] = {10, 25, 33, 47, 52, 68, 74, 89};
        inteiro procurado = 47;
        
        inteiro posicao = buscar(numeros, 8, procurado);
        
        se (posicao != -1) {
            escreva("Valor ", procurado, " encontrado na posição ", posicao, "\n");
        } senao {
            escreva("Valor ", procurado, " não encontrado\n");
        }
    }
}
```

### Ordenação de Vetores

```portugol
programa {
    funcao ordenar_bubble_sort(inteiro vetor[], inteiro tamanho) {
        para (inteiro i = 0; i < tamanho - 1; i++) {
            para (inteiro j = 0; j < tamanho - i - 1; j++) {
                se (vetor[j] > vetor[j + 1]) {
                    // Trocar elementos
                    inteiro temp = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = temp;
                }
            }
        }
    }
    
    funcao exibir_vetor(inteiro vetor[], inteiro tamanho) {
        para (inteiro i = 0; i < tamanho; i++) {
            escreva(vetor[i], " ");
        }
        escreva("\n");
    }
    
    funcao inicio() {
        inteiro numeros[6] = {64, 34, 25, 12, 22, 11};
        
        escreva("Vetor original: ");
        exibir_vetor(numeros, 6);
        
        ordenar_bubble_sort(numeros, 6);
        
        escreva("Vetor ordenado: ");
        exibir_vetor(numeros, 6);
    }
}
```

## Funções com Vetores

### Passagem de Vetores para Funções

```portugol
programa {
    real calcular_media(real notas[], inteiro quantidade) {
        real soma = 0.0;
        
        para (inteiro i = 0; i < quantidade; i++) {
            soma = soma + notas[i];
        }
        
        retorne soma / quantidade;
    }
    
    inteiro encontrar_maior(inteiro valores[], inteiro tamanho) {
        inteiro maior = valores[0];
        
        para (inteiro i = 1; i < tamanho; i++) {
            se (valores[i] > maior) {
                maior = valores[i];
            }
        }
        
        retorne maior;
    }
    
    funcao preencher_sequencial(inteiro vetor[], inteiro tamanho) {
        para (inteiro i = 0; i < tamanho; i++) {
            vetor[i] = (i + 1) * 10;
        }
    }
    
    funcao inicio() {
        real notas[4] = {8.5, 7.2, 9.1, 6.8};
        inteiro valores[5];
        
        // Calcular média
        real media = calcular_media(notas, 4);
        escreva("Média das notas: ", media, "\n");
        
        // Preencher e encontrar maior
        preencher_sequencial(valores, 5);
        inteiro maior = encontrar_maior(valores, 5);
        escreva("Maior valor: ", maior, "\n");
    }
}
```

## Algoritmos Comuns

### Inversão de Vetor

```portugol
programa {
    funcao inverter_vetor(inteiro vetor[], inteiro tamanho) {
        inteiro inicio = 0;
        inteiro fim = tamanho - 1;
        
        enquanto (inicio < fim) {
            // Trocar elementos
            inteiro temp = vetor[inicio];
            vetor[inicio] = vetor[fim];
            vetor[fim] = temp;
            
            inicio++;
            fim--;
        }
    }
    
    funcao inicio() {
        inteiro numeros[5] = {1, 2, 3, 4, 5};
        
        escreva("Vetor original: ");
        para (inteiro i = 0; i < 5; i++) {
            escreva(numeros[i], " ");
        }
        escreva("\n");
        
        inverter_vetor(numeros, 5);
        
        escreva("Vetor invertido: ");
        para (inteiro i = 0; i < 5; i++) {
            escreva(numeros[i], " ");
        }
        escreva("\n");
    }
}
```

### Remoção de Duplicatas

```portugol
programa {
    inteiro remover_duplicatas(inteiro vetor[], inteiro tamanho) {
        inteiro novo_tamanho = 0;
        
        para (inteiro i = 0; i < tamanho; i++) {
            logico eh_duplicata = falso;
            
            // Verificar se o elemento já existe
            para (inteiro j = 0; j < novo_tamanho; j++) {
                se (vetor[i] == vetor[j]) {
                    eh_duplicata = verdadeiro;
                    pare;
                }
            }
            
            // Se não é duplicata, manter no vetor
            se (!eh_duplicata) {
                vetor[novo_tamanho] = vetor[i];
                novo_tamanho++;
            }
        }
        
        retorne novo_tamanho;
    }
    
    funcao inicio() {
        inteiro numeros[8] = {1, 2, 2, 3, 4, 3, 5, 1};
        
        escreva("Vetor original: ");
        para (inteiro i = 0; i < 8; i++) {
            escreva(numeros[i], " ");
        }
        escreva("\n");
        
        inteiro novo_tamanho = remover_duplicatas(numeros, 8);
        
        escreva("Vetor sem duplicatas: ");
        para (inteiro i = 0; i < novo_tamanho; i++) {
            escreva(numeros[i], " ");
        }
        escreva("\n");
    }
}
```

## Strings como Vetores de Caracteres

### Manipulação de Strings

```portugol
programa {
    inteiro tamanho_string(caracter str[]) {
        inteiro tamanho = 0;
        enquanto (str[tamanho] != '\0') {
            tamanho++;
        }
        retorne tamanho;
    }
    
    funcao copiar_string(caracter origem[], caracter destino[]) {
        inteiro i = 0;
        enquanto (origem[i] != '\0') {
            destino[i] = origem[i];
            i++;
        }
        destino[i] = '\0'; // Terminar string
    }
    
    logico comparar_strings(caracter str1[], caracter str2[]) {
        inteiro i = 0;
        enquanto (str1[i] != '\0' && str2[i] != '\0') {
            se (str1[i] != str2[i]) {
                retorne falso;
            }
            i++;
        }
        retorne (str1[i] == str2[i]); // Ambas devem ter terminado
    }
    
    funcao inicio() {
        caracter nome1[20] = {'J', 'o', 'a', 'o', '\0'};
        caracter nome2[20];
        caracter nome3[20] = {'J', 'o', 'a', 'o', '\0'};
        
        escreva("Tamanho de nome1: ", tamanho_string(nome1), "\n");
        
        copiar_string(nome1, nome2);
        escreva("Nome copiado: ");
        inteiro i = 0;
        enquanto (nome2[i] != '\0') {
            escreva(nome2[i]);
            i++;
        }
        escreva("\n");
        
        se (comparar_strings(nome1, nome3)) {
            escreva("Os nomes são iguais\n");
        } senao {
            escreva("Os nomes são diferentes\n");
        }
    }
}
```

## Limitações e Considerações

### Limitações
- Tamanho fixo definido em tempo de compilação
- Não há verificação automática de limites (bounds checking)
- Não há redimensionamento dinâmico
- Índices começam em 0 (zero-indexed)

### Boas Práticas

```portugol
// 1. Sempre verificar limites
funcao acesso_seguro(inteiro vetor[], inteiro tamanho, inteiro indice) {
    se (indice >= 0 && indice < tamanho) {
        retorne vetor[indice];
    } senao {
        escreva("Erro: Índice fora dos limites!\n");
        retorne -1; // Valor de erro
    }
}
// 2. Inicializar vetores
inteiro numeros[10] = {0}; // Inicializar todos com 0
// 3. Usar constantes para tamanhos
programa {
    funcao inicio() {
        inteiro TAMANHO = 5;
        inteiro valores[5]; // Use TAMANHO se a linguagem permitir
        
        para (inteiro i = 0; i < TAMANHO; i++) {
            valores[i] = 0;
        }
    }
}
// 4. Documentar o propósito dos vetores
inteiro idades_alunos[30];     // Armazena idades de até 30 alunos
real notas_provas[4];          // Armazena notas das 4 provas
caracter buffer_entrada[256];  // Buffer para entrada do usuário
```

### Exemplo Completo: Sistema de Notas

```portugol
programa {
    funcao entrada_notas(real notas[], inteiro quantidade) {
        para (inteiro i = 0; i < quantidade; i++) {
            escreva("Digite a nota ", (i + 1), ": ");
            leia(notas[i]);
            
            // Validação
            enquanto (notas[i] < 0.0 || notas[i] > 10.0) {
                escreva("Nota inválida. Digite entre 0 e 10: ");
                leia(notas[i]);
            }
        }
    }
    
    real calcular_media(real notas[], inteiro quantidade) {
        real soma = 0.0;
        para (inteiro i = 0; i < quantidade; i++) {
            soma = soma + notas[i];
        }
        retorne soma / quantidade;
    }
    
    inteiro contar_aprovados(real notas[], inteiro quantidade, real media_minima) {
        inteiro aprovados = 0;
        para (inteiro i = 0; i < quantidade; i++) {
            se (notas[i] >= media_minima) {
                aprovados++;
            }
        }
        retorne aprovados;
    }
    
    funcao relatorio(real notas[], inteiro quantidade) {
        real media = calcular_media(notas, quantidade);
        inteiro aprovados = contar_aprovados(notas, quantidade, 6.0);
        
        escreva("\n=== RELATÓRIO ===\n");
        escreva("Média da turma: ", media, "\n");
        escreva("Aprovados (nota >= 6.0): ", aprovados, "\n");
        escreva("Reprovados: ", (quantidade - aprovados), "\n");
        
        escreva("\nNotas individuais:\n");
        para (inteiro i = 0; i < quantidade; i++) {
            escreva("Aluno ", (i + 1), ": ", notas[i]);
            se (notas[i] >= 6.0) {
                escreva(" (Aprovado)\n");
            } senao {
                escreva(" (Reprovado)\n");
            }
        }
    }
    
    funcao inicio() {
        inteiro quantidade = 5;
        real notas[5];
        
        escreva("Sistema de Notas - Digite as notas dos alunos\n\n");
        
        entrada_notas(notas, quantidade);
        relatorio(notas, quantidade);
    }
}
```

## Performance e Otimização

### Acesso Sequencial vs Aleatório
- Acesso sequencial é mais eficiente devido à localidade de memória
- Evite acessos aleatórios desnecessários em loops

### Algoritmos Eficientes
- Use algoritmos de ordenação eficientes para vetores grandes
- Considere busca binária em vetores ordenados
- Minimize cópias desnecessárias de vetores
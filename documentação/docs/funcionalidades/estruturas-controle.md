# Estruturas de Controle

O Portugol-C oferece estruturas de controle para gerenciar o fluxo de execução dos programas, incluindo condicionais, loops e estruturas de seleção.

## Estruturas Condicionais

### Se (if)

A estrutura `se` permite executar código condicionalmente baseado em uma expressão lógica.

#### Sintaxe
```portugol
se (condicao) {
    // código a ser executado se a condição for verdadeira
}
```

#### Se-Senão (if-else)
```portugol
se (condicao) {
    // código se verdadeiro
} senao {
    // código se falso
}
```

#### Se-Senão Se (if-else if)
```portugol
se (condicao1) {
    // código para condição 1
} senao se (condicao2) {
    // código para condição 2
} senao {
    // código padrão
}
```

#### Exemplos
```portugol
programa {
    funcao inicio() {
        inteiro idade = 18;
        
        se (idade >= 18) {
            escreva("Maior de idade\n");
        } senao {
            escreva("Menor de idade\n");
        }
        
        // Múltiplas condições
        inteiro nota = 85;
        se (nota >= 90) {
            escreva("Excelente\n");
        } senao se (nota >= 80) {
            escreva("Bom\n");
        } senao se (nota >= 70) {
            escreva("Regular\n");
        } senao {
            escreva("Insuficiente\n");
        }
    }
}
```

## Estruturas de Repetição

### Para (for)

O loop `para` é usado quando o número de iterações é conhecido.

#### Sintaxe
```portugol
para (inicializacao; condicao; incremento) {
    // código a ser repetido
}
```

#### Exemplos
```portugol
programa {
    funcao inicio() {
        // Loop básico
        para (inteiro i = 0; i < 10; i++) {
            escreva("Valor: ", i, "\n");
        }
        
        // Loop com decremento
        para (inteiro j = 10; j > 0; j--) {
            escreva("Contagem regressiva: ", j, "\n");
        }
        
        // Loop com incremento personalizado
        para (inteiro k = 0; k <= 100; k = k + 10) {
            escreva("Múltiplo de 10: ", k, "\n");
        }
    }
}
```

### Enquanto (while)

O loop `enquanto` executa enquanto uma condição for verdadeira.

#### Sintaxe
```portugol
enquanto (condicao) {
    // código a ser repetido
}
```

#### Exemplos
```portugol
programa {
    funcao inicio() {
        inteiro contador = 0;
        
        enquanto (contador < 5) {
            escreva("Contador: ", contador, "\n");
            contador++;
        }
        
        // Exemplo com entrada do usuário
        inteiro numero;
        escreva("Digite um número (0 para sair): ");
        leia(numero);
        
        enquanto (numero != 0) {
            escreva("Você digitou: ", numero, "\n");
            escreva("Digite outro número (0 para sair): ");
            leia(numero);
        }
    }
}
```

## Estrutura de Seleção Múltipla

### Escolha-Caso (switch-case)

A estrutura `escolha` permite selecionar entre múltiplas opções baseadas no valor de uma variável.

#### Sintaxe
```portugol
escolha (variavel) {
    caso valor1:
        // código para valor1
        pare;
    caso valor2:
        // código para valor2
        pare;
    caso contrario:
        // código padrão
        pare;
}
```

#### Exemplos
```portugol
programa {
    funcao inicio() {
        inteiro opcao = 2;
        
        escolha (opcao) {
            caso 1:
                escreva("Opção 1 selecionada\n");
                pare;
            caso 2:
                escreva("Opção 2 selecionada\n");
                pare;
            caso 3:
                escreva("Opção 3 selecionada\n");
                pare;
            caso contrario:
                escreva("Opção inválida\n");
                pare;
        }
        
        // Exemplo com caracteres
        caracter grade = 'B';
        
        escolha (grade) {
            caso 'A':
                escreva("Excelente!\n");
                pare;
            caso 'B':
                escreva("Bom trabalho!\n");
                pare;
            caso 'C':
                escreva("Satisfatório\n");
                pare;
            caso contrario:
                escreva("Nota inválida\n");
                pare;
        }
    }
}
```

## Estruturas Aninhadas

As estruturas de controle podem ser aninhadas para criar lógicas mais complexas.

### Exemplo Complexo
```portugol
programa {
    funcao inicio() {
        inteiro idade, renda;
        
        escreva("Digite sua idade: ");
        leia(idade);
        escreva("Digite sua renda: ");
        leia(renda);
        
        se (idade >= 18) {
            se (renda >= 2000) {
                escreva("Elegível para crédito premium\n");
            } senao se (renda >= 1000) {
                escreva("Elegível para crédito básico\n");
            } senao {
                escreva("Renda insuficiente\n");
            }
        } senao {
            escreva("Menor de idade - não elegível\n");
        }
        
        // Loop aninhado
        para (inteiro i = 1; i <= 3; i++) {
            escreva("Tabela do ", i, ":\n");
            para (inteiro j = 1; j <= 10; j++) {
                escreva(i, " x ", j, " = ", i * j, "\n");
            }
            escreva("\n");
        }
    }
}
```

## Controle de Fluxo

### Pare (break)
Interrompe a execução de loops ou estruturas switch.

```portugol
para (inteiro i = 0; i < 10; i++) {
    se (i == 5) {
        pare; // Sai do loop quando i for 5
    }
    escreva(i, "\n");
}
```

### Continue
O Portugol-C não possui uma palavra-chave específica para `continue`, mas o comportamento pode ser simulado com estruturas condicionais.

```portugol
para (inteiro i = 0; i < 10; i++) {
    se (i % 2 == 0) {
        // Pula números pares - simula continue
    } senao {
        escreva("Número ímpar: ", i, "\n");
    }
}
```

## Boas Práticas

1. **Indentação:** Use indentação consistente para melhorar a legibilidade
2. **Chaves:** Sempre use chaves, mesmo para blocos de uma linha
3. **Condições claras:** Escreva condições claras e legíveis
4. **Evite aninhamento excessivo:** Limite o número de níveis de aninhamento
5. **Comentários:** Documente lógicas complexas

```portugol
// Boa prática
se (idade >= 18 && renda > 1000) {
    processar_credito();
}

// Em vez de
se (idade >= 18) {
    se (renda > 1000) {
        processar_credito();
    }
}
```

## Operadores em Condições

### Operadores Relacionais
- `==` (igual)
- `!=` (diferente)
- `<` (menor que)
- `>` (maior que)
- `<=` (menor ou igual)
- `>=` (maior ou igual)

### Operadores Lógicos
- `&&` (E lógico)
- `||` (OU lógico)
- `!` (NÃO lógico)

### Exemplos
```portugol
se (idade >= 18 && idade <= 65) {
    escreva("Idade para trabalhar\n");
}

se (nota < 60 || faltas > 10) {
    escreva("Reprovado\n");
}

se (!(aprovado)) {
    escreva("Não aprovado\n");
}
```

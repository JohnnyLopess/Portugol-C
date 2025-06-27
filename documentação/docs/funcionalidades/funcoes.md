# Funções

O Portugol-C suporta a definição e uso de funções para modularizar código e promover reutilização. As funções podem ter parâmetros, valores de retorno e diferentes escopos.

## Estrutura Básica

### Sintaxe Geral
```portugol
tipo_retorno nome_funcao(parametros) {
    // corpo da função
    retorne valor; // opcional
}
```

### Função Principal
Todo programa Portugol-C deve ter uma função `inicio()` que serve como ponto de entrada:

```portugol
programa {
    funcao inicio() {
        // código principal do programa
    }
}
```

## Tipos de Funções

### Funções Sem Retorno (void)

Funções que não retornam valores usam a palavra-chave `vazio` ou omitem o tipo de retorno.

```portugol
funcao saudar() {
    escreva("Olá, mundo!\n");
}
funcao exibir_menu() {
    escreva("=== MENU ===\n");
    escreva("1. Opção 1\n");
    escreva("2. Opção 2\n");
    escreva("3. Sair\n");
}
```

### Funções Com Retorno

Funções que retornam valores devem especificar o tipo de retorno e usar a palavra-chave `retorne`.

```portugol
inteiro somar(inteiro a, inteiro b) {
    retorne a + b;
}
real calcular_media(real nota1, real nota2, real nota3) {
    retorne (nota1 + nota2 + nota3) / 3.0;
}
logico eh_par(inteiro numero) {
    retorne (numero % 2 == 0);
}
caracter obter_conceito(real media) {
    se (media >= 9.0) {
        retorne 'A';
    } senao se (media >= 7.0) {
        retorne 'B';
    } senao se (media >= 5.0) {
        retorne 'C';
    } senao {
        retorne 'D';
    }
}
```

## Parâmetros

### Parâmetros Simples

```portugol
funcao cumprimentar(caracter nome[]) {
    escreva("Olá, ", nome, "!\n");
}
funcao calcular_area_retangulo(real largura, real altura) {
    real area = largura * altura;
    escreva("Área: ", area, "\n");
}
```

### Múltiplos Parâmetros

```portugol
inteiro encontrar_maior(inteiro a, inteiro b, inteiro c) {
    inteiro maior = a;
    
    se (b > maior) {
        maior = b;
    }
    
    se (c > maior) {
        maior = c;
    }
    
    retorne maior;
}
```

### Parâmetros de Diferentes Tipos

```portugol
funcao exibir_dados_pessoa(caracter nome[], inteiro idade, real salario, logico ativo) {
    escreva("Nome: ", nome, "\n");
    escreva("Idade: ", idade, "\n");
    escreva("Salário: ", salario, "\n");
    escreva("Ativo: ", ativo, "\n");
}
```

## Exemplos Práticos

### Calculadora Simples

```portugol
programa {
    real somar(real a, real b) {
        retorne a + b;
    }
    
    real subtrair(real a, real b) {
        retorne a - b;
    }
    
    real multiplicar(real a, real b) {
        retorne a * b;
    }
    
    real dividir(real a, real b) {
        se (b != 0) {
            retorne a / b;
        } senao {
            escreva("Erro: Divisão por zero!\n");
            retorne 0.0;
        }
    }
    
    funcao inicio() {
        real num1, num2, resultado;
        caracter operacao;
        
        escreva("Digite o primeiro número: ");
        leia(num1);
        
        escreva("Digite o segundo número: ");
        leia(num2);
        
        escreva("Digite a operação (+, -, *, /): ");
        leia(operacao);
        
        escolha (operacao) {
            caso '+':
                resultado = somar(num1, num2);
                pare;
            caso '-':
                resultado = subtrair(num1, num2);
                pare;
            caso '*':
                resultado = multiplicar(num1, num2);
                pare;
            caso '/':
                resultado = dividir(num1, num2);
                pare;
            padrao:
                escreva("Operação inválida!\n");
                retorne;
        }
        
        escreva("Resultado: ", resultado, "\n");
    }
}
```

### Sistema de Validação

```portugol
programa {
    logico validar_idade(inteiro idade) {
        retorne (idade >= 0 && idade <= 150);
    }
    
    logico validar_email(caracter email[]) {
        // Validação simples - verificar se contém @
        inteiro i = 0;
        enquanto (email[i] != '\0') {
            se (email[i] == '@') {
                retorne verdadeiro;
            }
            i++;
        }
        retorne falso;
    }
    
    caracter classificar_idade(inteiro idade) {
        se (idade < 13) {
            retorne 'C'; // Criança
        } senao se (idade < 18) {
            retorne 'A'; // Adolescente
        } senao se (idade < 60) {
            retorne 'J'; // Jovem/Adulto
        } senao {
            retorne 'I'; // Idoso
        }
    }
    
    funcao inicio() {
        inteiro idade;
        caracter email[100];
        
        escreva("Digite sua idade: ");
        leia(idade);
        
        se (validar_idade(idade)) {
            caracter categoria = classificar_idade(idade);
            escreva("Categoria: ", categoria, "\n");
        } senao {
            escreva("Idade inválida!\n");
        }
        
        escreva("Digite seu email: ");
        leia(email);
        
        se (validar_email(email)) {
            escreva("Email válido!\n");
        } senao {
            escreva("Email inválido!\n");
        }
    }
}
```

## Escopo de Variáveis

### Variáveis Locais

Variáveis declaradas dentro de funções são locais e só existem no escopo da função.

```portugol
funcao exemplo_escopo() {
    inteiro local = 10; // Variável local
    escreva("Valor local: ", local, "\n");
}
funcao inicio() {
    exemplo_escopo();
    // local não existe aqui - erro de compilação
}
```

### Variáveis Globais

Variáveis declaradas fora de funções são globais e podem ser acessadas por todas as funções.

```portugol
programa {
    inteiro contador_global = 0; // Variável global
    
    funcao incrementar() {
        contador_global++;
    }
    
    funcao obter_contador() {
        retorne contador_global;
    }
    
    funcao inicio() {
        escreva("Contador inicial: ", contador_global, "\n");
        incrementar();
        escreva("Contador após incremento: ", obter_contador(), "\n");
    }
}
```

## Recursão

O Portugol-C suporta funções recursivas:

```portugol
programa {
    inteiro fatorial(inteiro n) {
        se (n <= 1) {
            retorne 1;
        } senao {
            retorne n * fatorial(n - 1);
        }
    }
    
    inteiro fibonacci(inteiro n) {
        se (n <= 1) {
            retorne n;
        } senao {
            retorne fibonacci(n - 1) + fibonacci(n - 2);
        }
    }
    
    funcao inicio() {
        inteiro num = 5;
        
        escreva("Fatorial de ", num, ": ", fatorial(num), "\n");
        
        escreva("Sequência de Fibonacci até ", num, ":\n");
        para (inteiro i = 0; i <= num; i++) {
            escreva(fibonacci(i), " ");
        }
        escreva("\n");
    }
}
```

## Passagem de Parâmetros

### Por Valor

Por padrão, os parâmetros são passados por valor (cópia).

```portugol
funcao modificar_valor(inteiro x) {
    x = 100; // Modifica apenas a cópia local
}
funcao inicio() {
    inteiro numero = 10;
    modificar_valor(numero);
    escreva("Número: ", numero, "\n"); // Ainda será 10
}
```

### Arrays (Passagem por Referência)

Arrays são passados por referência, permitindo modificações.

```portugol
funcao preencher_array(inteiro vetor[], inteiro tamanho) {
    para (inteiro i = 0; i < tamanho; i++) {
        vetor[i] = i * 2;
    }
}
funcao exibir_array(inteiro vetor[], inteiro tamanho) {
    para (inteiro i = 0; i < tamanho; i++) {
        escreva(vetor[i], " ");
    }
    escreva("\n");
}
funcao inicio() {
    inteiro numeros[5];
    
    preencher_array(numeros, 5);
    exibir_array(numeros, 5);
}
```

## Boas Práticas

### Nomenclatura

```portugol
// Boas práticas
funcao calcular_media_aluno(real nota1, real nota2, real nota3) { }
funcao validar_cpf(caracter cpf[]) { }
funcao obter_idade_usuario() { }
// Evitar
funcao calc(real a, real b, real c) { }
funcao val(caracter x[]) { }
funcao get() { }
```

### Documentação

```portugol
/*
 * Calcula a área de um círculo dado o raio
 * Parâmetro: raio - o raio do círculo
 * Retorna: a área calculada
 */
real calcular_area_circulo(real raio) {
    real pi = 3.14159;
    retorne pi * raio * raio;
}
```

### Modularização

```portugol
programa {
    // Funções de entrada e saída
    funcao ler_dados() { }
    funcao exibir_resultados() { }
    
    // Funções de processamento
    funcao processar_dados() { }
    funcao validar_entrada() { }
    
    // Funções utilitárias
    funcao limpar_tela() { }
    funcao pausar() { }
    
    funcao inicio() {
        // Programa principal organizado
    }
}
```

## Limitações

- Não há sobrecarga de funções (overloading)
- Não há parâmetros opcionais
- Não há parâmetros nomeados
- Funções devem ser declaradas antes de serem usadas
- Não há ponteiros para funções
- Recursão limitada pelo tamanho da pilha
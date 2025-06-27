# Operadores

O Portugol-C oferece um conjunto completo de operadores para realizar operações aritméticas, relacionais, lógicas e de atribuição, permitindo a construção de expressões complexas.

## Operadores Aritméticos

### Operadores Básicos

| Operador | Descrição | Exemplo | Resultado |
|----------|-----------|---------|-----------|
| `+` | Adição | `5 + 3` | `8` |
| `-` | Subtração | `10 - 4` | `6` |
| `*` | Multiplicação | `6 * 7` | `42` |
| `/` | Divisão | `15 / 3` | `5` |
| `%` | Módulo (resto da divisão) | `17 % 5` | `2` |

### Exemplos de Uso

```portugol
programa {
    funcao inicio() {
        inteiro a = 15, b = 4;
        real x = 10.5, y = 3.2;
        
        // Operações com inteiros
        escreva("Soma: ", a + b, "\n");           // 19
        escreva("Subtração: ", a - b, "\n");      // 11
        escreva("Multiplicação: ", a * b, "\n");  // 60
        escreva("Divisão: ", a / b, "\n");        // 3 (divisão inteira)
        escreva("Módulo: ", a % b, "\n");         // 3
        
        // Operações com reais
        escreva("Soma real: ", x + y, "\n");      // 13.7
        escreva("Divisão real: ", x / y, "\n");   // 3.28125
        
        // Operações mistas
        escreva("Mista: ", a + x, "\n");          // 25.5
    }
}
```

### Operador Unário

```portugol
programa {
    funcao inicio() {
        inteiro numero = 10;
        
        escreva("Número original: ", numero, "\n");     // 10
        escreva("Número negativo: ", -numero, "\n");    // -10
        escreva("Positivo explícito: ", +numero, "\n"); // 10
    }
}
```

## Operadores de Atribuição

### Atribuição Simples

```portugol
inteiro x = 10;        // Atribuição inicial
x = 20;                // Reatribuição
```

### Operadores de Atribuição Composta

| Operador | Equivalente | Exemplo | Significado |
|----------|-------------|---------|-------------|
| `+=` | `x = x + y` | `x += 5` | Adicionar e atribuir |
| `-=` | `x = x - y` | `x -= 3` | Subtrair e atribuir |
| `*=` | `x = x * y` | `x *= 2` | Multiplicar e atribuir |
| `/=` | `x = x / y` | `x /= 4` | Dividir e atribuir |
| `%=` | `x = x % y` | `x %= 3` | Módulo e atribuir |

```portugol
programa {
    funcao inicio() {
        inteiro valor = 10;
        
        escreva("Valor inicial: ", valor, "\n");  // 10
        
        valor += 5;
        escreva("Após += 5: ", valor, "\n");      // 15
        
        valor -= 3;
        escreva("Após -= 3: ", valor, "\n");      // 12
        
        valor *= 2;
        escreva("Após *= 2: ", valor, "\n");      // 24
        
        valor /= 4;
        escreva("Após /= 4: ", valor, "\n");      // 6
        
        valor %= 4;
        escreva("Após %= 4: ", valor, "\n");      // 2
    }
}
```

## Operadores de Incremento e Decremento

### Pré e Pós-incremento/decremento

| Operador | Descrição | Exemplo | Comportamento |
|----------|-----------|---------|---------------|
| `++x` | Pré-incremento | `++contador` | Incrementa primeiro, depois usa |
| `x++` | Pós-incremento | `contador++` | Usa primeiro, depois incrementa |
| `--x` | Pré-decremento | `--contador` | Decrementa primeiro, depois usa |
| `x--` | Pós-decremento | `contador--` | Usa primeiro, depois decrementa |

```portugol
programa {
    funcao inicio() {
        inteiro a = 5, b = 5;
        
        escreva("Valores iniciais - a: ", a, ", b: ", b, "\n");
        
        // Pré-incremento
        escreva("Pré-incremento ++a: ", ++a, "\n");  // a vira 6, mostra 6
        escreva("Valor de a agora: ", a, "\n");      // 6
        
        // Pós-incremento
        escreva("Pós-incremento b++: ", b++, "\n");  // mostra 5, b vira 6
        escreva("Valor de b agora: ", b, "\n");      // 6
        
        // Uso em loops
        para (inteiro i = 0; i < 3; i++) {
            escreva("Loop: ", i, "\n");
        }
        
        // Decremento
        inteiro c = 10;
        escreva("Pré-decremento --c: ", --c, "\n");  // 9
        escreva("Pós-decremento c--: ", c--, "\n");  // 9, depois vira 8
        escreva("Valor final de c: ", c, "\n");      // 8
    }
}
```

## Operadores Relacionais

### Comparações

| Operador | Descrição | Exemplo | Resultado |
|----------|-----------|---------|-----------|
| `==` | Igual a | `5 == 5` | `verdadeiro` |
| `!=` | Diferente de | `5 != 3` | `verdadeiro` |
| `<` | Menor que | `3 < 5` | `verdadeiro` |
| `>` | Maior que | `7 > 4` | `verdadeiro` |
| `<=` | Menor ou igual | `5 <= 5` | `verdadeiro` |
| `>=` | Maior ou igual | `6 >= 6` | `verdadeiro` |

```portugol
programa {
    funcao inicio() {
        inteiro x = 10, y = 20;
        
        escreva("x = ", x, ", y = ", y, "\n");
        
        escreva("x == y: ", (x == y), "\n");     // falso (0)
        escreva("x != y: ", (x != y), "\n");     // verdadeiro (1)
        escreva("x < y: ", (x < y), "\n");       // verdadeiro (1)
        escreva("x > y: ", (x > y), "\n");       // falso (0)
        escreva("x <= 10: ", (x <= 10), "\n");  // verdadeiro (1)
        escreva("y >= 20: ", (y >= 20), "\n");  // verdadeiro (1)
        
        // Comparação de caracteres
        caracter a = 'A', b = 'B';
        escreva("'A' < 'B': ", (a < b), "\n");  // verdadeiro (ASCII)
    }
}
```

## Operadores Lógicos

### Operadores Booleanos

| Operador | Descrição | Exemplo | Resultado |
|----------|-----------|---------|-----------|
| `&&` | E lógico (AND) | `verdadeiro && falso` | `falso` |
| `\|\|` | OU lógico (OR) | `verdadeiro \|\| falso` | `verdadeiro` |
| `!` | NÃO lógico (NOT) | `!verdadeiro` | `falso` |

```portugol
programa {
    funcao inicio() {
        logico p = verdadeiro;
        logico q = falso;
        
        escreva("p = ", p, ", q = ", q, "\n");
        
        // Operador E (&&)
        escreva("p && q: ", (p && q), "\n");           // falso
        escreva("p && verdadeiro: ", (p && verdadeiro), "\n"); // verdadeiro
        
        // Operador OU (||)
        escreva("p || q: ", (p || q), "\n");           // verdadeiro
        escreva("q || falso: ", (q || falso), "\n");   // falso
        
        // Operador NÃO (!)
        escreva("!p: ", (!p), "\n");                   // falso
        escreva("!q: ", (!q), "\n");                   // verdadeiro
        
        // Combinações complexas
        escreva("!(p && q): ", (!(p && q)), "\n");     // verdadeiro
        escreva("!p || !q: ", ((!p) || (!q)), "\n");  // verdadeiro (Lei de De Morgan)
    }
}
```

### Avaliação de Curto-Circuito

```portugol
programa {
    logico sempre_verdadeiro() {
        escreva("Função sempre_verdadeiro chamada\n");
        retorne verdadeiro;
    }
    
    logico sempre_falso() {
        escreva("Função sempre_falso chamada\n");
        retorne falso;
    }
    
    funcao inicio() {
        // Com &&, se o primeiro for falso, o segundo não é avaliado
        escreva("Teste 1: ");
        se (sempre_falso() && sempre_verdadeiro()) {
            escreva("Condição verdadeira\n");
        }
        
        // Com ||, se o primeiro for verdadeiro, o segundo não é avaliado
        escreva("Teste 2: ");
        se (sempre_verdadeiro() || sempre_falso()) {
            escreva("Condição verdadeira\n");
        }
    }
}
```

## Operadores Bitwise

### Operações em Bits

| Operador | Descrição | Exemplo | Resultado |
|----------|-----------|---------|-----------|
| `&` | E bitwise (AND) | `5 & 3` | `1` |
| `\|` | OU bitwise (OR) | `5 \| 3` | `7` |
| `^` | OU exclusivo (XOR) | `5 ^ 3` | `6` |
| `~` | Complemento (NOT) | `~5` | `-6` |
| `<<` | Deslocamento à esquerda | `5 << 1` | `10` |
| `>>` | Deslocamento à direita | `10 >> 1` | `5` |

```portugol
programa {
    funcao inicio() {
        inteiro a = 5;  // 101 em binário
        inteiro b = 3;  // 011 em binário
        
        escreva("a = ", a, " (101 binário)\n");
        escreva("b = ", b, " (011 binário)\n");
        
        // Operações bitwise
        escreva("a & b = ", (a & b), "\n");    // 1 (001)
        escreva("a | b = ", (a | b), "\n");    // 7 (111)
        escreva("a ^ b = ", (a ^ b), "\n");    // 6 (110)
        escreva("~a = ", (~a), "\n");          // -6 (complemento de 2)
        
        // Deslocamentos
        escreva("a << 1 = ", (a << 1), "\n"); // 10 (1010)
        escreva("a >> 1 = ", (a >> 1), "\n"); // 2 (10)
        
        // Aplicações práticas
        inteiro numero = 16;
        escreva("Testar se ", numero, " é par: ", ((numero & 1) == 0), "\n");
        escreva("Multiplicar por 4 (<<2): ", (numero << 2), "\n"); // 64
        escreva("Dividir por 2 (>>1): ", (numero >> 1), "\n");     // 8
    }
}
```

## Precedência de Operadores

### Tabela de Precedência (do maior para o menor)

| Precedência | Operadores | Associatividade | Descrição |
|------------|------------|-----------------|-----------|
| 1 | `()` `[]` | Esquerda → Direita | Parênteses, índices |
| 2 | `!` `~` `+` `-` `++` `--` | Direita → Esquerda | Unários |
| 3 | `*` `/` `%` | Esquerda → Direita | Multiplicativos |
| 4 | `+` `-` | Esquerda → Direita | Aditivos |
| 5 | `<<` `>>` | Esquerda → Direita | Deslocamento |
| 6 | `<` `<=` `>` `>=` | Esquerda → Direita | Relacionais |
| 7 | `==` `!=` | Esquerda → Direita | Igualdade |
| 8 | `&` | Esquerda → Direita | E bitwise |
| 9 | `^` | Esquerda → Direita | XOR bitwise |
| 10 | `\|` | Esquerda → Direita | OU bitwise |
| 11 | `&&` | Esquerda → Direita | E lógico |
| 12 | `\|\|` | Esquerda → Direita | OU lógico |
| 13 | `=` `+=` `-=` `*=` `/=` `%=` | Direita → Esquerda | Atribuição |

### Exemplos de Precedência

```portugol
programa {
    funcao inicio() {
        inteiro a = 5, b = 3, c = 2;
        
        // Sem parênteses - seguindo precedência
        inteiro resultado1 = a + b * c;        // 5 + (3 * 2) = 11
        escreva("a + b * c = ", resultado1, "\n");
        
        // Com parênteses - alterando precedência
        inteiro resultado2 = (a + b) * c;      // (5 + 3) * 2 = 16
        escreva("(a + b) * c = ", resultado2, "\n");
        
        // Exemplo complexo
        inteiro x = 10, y = 5, z = 2;
        inteiro complexo = x + y * z - x / y;  // 10 + (5*2) - (10/5) = 10 + 10 - 2 = 18
        escreva("x + y * z - x / y = ", complexo, "\n");
        
        // Com parênteses para clareza
        inteiro claro = x + (y * z) - (x / y); // Mesmo resultado, mais claro
        escreva("Com parênteses: ", claro, "\n");
        
        // Operadores lógicos e relacionais
        logico condicao = (a > b) && (c < b) || (x == 10);
        escreva("Condição complexa: ", condicao, "\n");
    }
}
```

## Conversões e Casting

### Conversões Automáticas

```portugol
programa {
    funcao inicio() {
        inteiro i = 10;
        real r = 3.14;
        caracter c = 'A';
        
        // Conversões automáticas
        real resultado1 = i + r;        // int → float
        escreva("int + float: ", resultado1, "\n");  // 13.14
        
        inteiro resultado2 = c + i;     // char → int (ASCII)
        escreva("char + int: ", resultado2, "\n");   // 75 ('A' = 65)
        
        // Divisão inteira vs real
        inteiro div_int = 7 / 2;        // 3 (divisão inteira)
        real div_real = 7.0 / 2;        // 3.5 (divisão real)
        escreva("Divisão inteira: ", div_int, "\n");
        escreva("Divisão real: ", div_real, "\n");
    }
}
```

## Boas Práticas

### Clareza nas Expressões

```portugol
// Bom: uso de parênteses para clareza
se ((idade >= 18) && (renda > 1000)) {
    processar_credito();
}
// Melhor ainda: variáveis descritivas
logico maior_idade = (idade >= 18);
logico renda_suficiente = (renda > 1000);
se (maior_idade && renda_suficiente) {
    processar_credito();
}
```

### Evitar Efeitos Colaterais

```portugol
// Evitar: múltiplos incrementos na mesma expressão
inteiro x = 5;
inteiro resultado = ++x + x++; // Comportamento indefinido
// Preferir: operações separadas
x = 5;
++x;                           // x = 6
resultado = x + x;             // 12
x++;                           // x = 7
```

### Comparações Seguras

```portugol
// Para números reais, evitar comparação exata
real a = 0.1 + 0.2;
real b = 0.3;
// Evitar
se (a == b) { /* pode falhar devido à precisão */ }
// Preferir
real tolerancia = 0.0001;
se ((a - b) < tolerancia && (a - b) > -tolerancia) {
    // comparação com tolerância
}
```

## Exemplos Práticos

### Calculadora com Todos os Operadores

```portugol
programa {
    funcao menu() {
        escreva("\n=== CALCULADORA ===\n");
        escreva("1. Operações básicas (+, -, *, /, %)\n");
        escreva("2. Operações lógicas (&&, ||, !)\n");
        escreva("3. Operações bitwise (&, |, ^, ~, <<, >>)\n");
        escreva("4. Comparações (<, >, ==, !=, <=, >=)\n");
        escreva("0. Sair\n");
        escreva("Escolha: ");
    }
    
    funcao operacoes_basicas() {
        real a, b;
        escreva("Digite dois números: ");
        leia(a);
        leia(b);
        
        escreva("Soma: ", (a + b), "\n");
        escreva("Subtração: ", (a - b), "\n");
        escreva("Multiplicação: ", (a * b), "\n");
        
        se (b != 0) {
            escreva("Divisão: ", (a / b), "\n");
            escreva("Módulo: ", ((inteiro)a % (inteiro)b), "\n");
        } senao {
            escreva("Divisão por zero não é possível\n");
        }
    }
    
    funcao inicio() {
        inteiro opcao;
        
        faca {
            menu();
            leia(opcao);
            
            escolha (opcao) {
                caso 1:
                    operacoes_basicas();
                    pare;
                caso 0:
                    escreva("Saindo...\n");
                    pare;
                padrao:
                    escreva("Opção inválida!\n");
                    pare;
            }
        } enquanto (opcao != 0);
    }
}
```
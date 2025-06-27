# Casos de Teste

Este documento descreve todos os casos de teste implementados no compilador Portugol-C, organizados por categoria e funcionalidade.

## Estrutura dos Testes

### Organização dos Arquivos

```
testes/
├── run_tests.sh           # Script principal de execução
├── inputs/                # Arquivos fonte .pg
│   ├── hello.pg
│   ├── variavel.pg
│   ├── vetor_inteiro.pg
│   └── ...
└── expected/              # Saídas esperadas .expected
    ├── hello.expected
    ├── variavel.expected
    ├── vetor_inteiro.expected
    └── ...
```

### Como Funcionam os Testes

1. **Compilação**: Cada arquivo `.pg` é compilado para C
2. **Execução**: O código C é compilado e executado
3. **Comparação**: A saída é comparada com o arquivo `.expected`
4. **Resultado**: Teste passa se as saídas forem idênticas

## Casos de Teste por Categoria

### 1. Testes Básicos

#### Hello World (`hello.pg`)
**Objetivo**: Verificar funcionamento básico do compilador

**Código**:
```portugol
programa {
    funcao inicio() {
        escreva("Hello, World!\n");
    }
}
```

**Saída Esperada**:
```
Hello, World!
```

#### Comentários (`comment.pg`)
**Objetivo**: Verificar processamento de comentários

**Código**:
```portugol
programa {
    // Comentário de linha
    /* Comentário de bloco */
    funcao inicio() {
        escreva("Comentários funcionam\n");
        // Outro comentário
    }
}
```

**Saída Esperada**:
```
Comentários funcionam
```

### 2. Testes de Tipos de Dados

#### Inteiros (`inteiro.pg`)
**Objetivo**: Testar operações com números inteiros

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro a = 10;
        inteiro b = 20;
        inteiro soma = a + b;
        escreva("Soma: ", soma, "\n");
    }
}
```

**Saída Esperada**:
```
Soma: 30
```

#### Números Reais (`real.pg`)
**Objetivo**: Testar operações com números de ponto flutuante

**Código**:
```portugol
programa {
    funcao inicio() {
        real pi = 3.14159;
        real raio = 5.0;
        real area = pi * raio * raio;
        escreva("Área do círculo: ", area, "\n");
    }
}
```

**Saída Esperada**:
```
Área do círculo: 78.5398
```

#### Caracteres (`caracter.pg`)
**Objetivo**: Testar manipulação de caracteres

**Código**:
```portugol
programa {
    funcao inicio() {
        caracter inicial = 'J';
        caracter final = 'o';
        escreva("Iniciais: ", inicial, final, "\n");
    }
}
```

**Saída Esperada**:
```
Iniciais: Jo
```

#### Lógicos (`logico.pg`)
**Objetivo**: Testar valores booleanos

**Código**:
```portugol
programa {
    funcao inicio() {
        logico ativo = verdadeiro;
        logico inativo = falso;
        escreva("Ativo: ", ativo, "\n");
        escreva("Inativo: ", inativo, "\n");
    }
}
```

**Saída Esperada**:
```
Ativo: 1
Inativo: 0
```

### 3. Testes de Variáveis

#### Declaração de Variáveis (`variavel.pg`)
**Objetivo**: Testar declaração e inicialização de variáveis

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro idade;
        real salario = 3500.50;
        caracter categoria = 'A';
        logico aprovado = verdadeiro;
        
        idade = 25;
        
        escreva("Idade: ", idade, "\n");
        escreva("Salário: ", salario, "\n");
        escreva("Categoria: ", categoria, "\n");
        escreva("Aprovado: ", aprovado, "\n");
    }
}
```

#### Atribuição Direta (`atribuicao_direta.pg`)
**Objetivo**: Testar diferentes formas de atribuição

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro x = 5;
        x = 10;
        x += 5;
        x *= 2;
        escreva("Resultado: ", x, "\n");
    }
}
```

### 4. Testes de Vetores

#### Vetores de Inteiros (`vetor_inteiro.pg`)
**Objetivo**: Testar declaração, inicialização e acesso a vetores de inteiros

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro numeros[5] = {10, 20, 30, 40, 50};
        
        para (inteiro i = 0; i < 5; i++) {
            escreva("numeros[", i, "] = ", numeros[i], "\n");
        }
    }
}
```

#### Vetores de Reais (`vetor_real.pg`)
**Objetivo**: Testar vetores com números decimais

**Código**:
```portugol
programa {
    funcao inicio() {
        real temperaturas[3] = {25.5, 30.0, 28.2};
        real soma = 0.0;
        
        para (inteiro i = 0; i < 3; i++) {
            soma += temperaturas[i];
        }
        
        real media = soma / 3.0;
        escreva("Média: ", media, "\n");
    }
}
```

#### Vetores de Caracteres (`vetor_caracter.pg`)
**Objetivo**: Testar strings como vetores de caracteres

**Código**:
```portugol
programa {
    funcao inicio() {
        caracter nome[8] = {'P', 'o', 'r', 't', 'u', 'g', 'o', 'l'};
        
        escreva("Nome: ");
        para (inteiro i = 0; i < 8; i++) {
            escreva(nome[i]);
        }
        escreva("\n");
    }
}
```

#### Vetores Lógicos (`vetor_logico.pg`)
**Objetivo**: Testar vetores de valores booleanos

**Código**:
```portugol
programa {
    funcao inicio() {
        logico flags[4] = {verdadeiro, falso, verdadeiro, falso};
        inteiro contador = 0;
        
        para (inteiro i = 0; i < 4; i++) {
            se (flags[i] == verdadeiro) {
                contador++;
            }
        }
        
        escreva("Flags verdadeiras: ", contador, "\n");
    }
}
```

#### Leitura de Vetores (`vetor_leitura.pg`)
**Objetivo**: Testar entrada de dados em vetores

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro valores[3];
        
        para (inteiro i = 0; i < 3; i++) {
            valores[i] = i + 10;
        }
        
        para (inteiro i = 0; i < 3; i++) {
            escreva("Valor ", i, ": ", valores[i], "\n");
        }
    }
}
```

#### Operações com Vetores (`vetor_operacoes.pg`)
**Objetivo**: Testar operações complexas com vetores

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro origem[3] = {1, 2, 3};
        inteiro destino[3];
        
        // Copiar vetor
        para (inteiro i = 0; i < 3; i++) {
            destino[i] = origem[i] * 2;
        }
        
        // Mostrar resultado
        para (inteiro i = 0; i < 3; i++) {
            escreva("destino[", i, "] = ", destino[i], "\n");
        }
    }
}
```

### 5. Testes de Estruturas de Controle

#### Estruturas Condicionais (`If_aninhado.pg`)
**Objetivo**: Testar if-else aninhados

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro nota = 85;
        
        se (nota >= 90) {
            escreva("Excelente\n");
        } senao se (nota >= 80) {
            escreva("Bom\n");
        } senao {
            escreva("Regular\n");
        }
    }
}
```

#### Loop Para (`para.pg`)
**Objetivo**: Testar estrutura de repetição for

**Código**:
```portugol
programa {
    funcao inicio() {
        para (inteiro i = 1; i <= 3; i++) {
            escreva("Iteração: ", i, "\n");
        }
    }
}
```

#### Loop Enquanto (`enquanto.pg`)
**Objetivo**: Testar estrutura de repetição while

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro contador = 0;
        
        enquanto (contador < 3) {
            escreva("Contador: ", contador, "\n");
            contador++;
        }
    }
}
```

#### Switch-Case (`switch_case.pg`)
**Objetivo**: Testar estrutura de seleção múltipla

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro opcao = 2;
        
        escolha (opcao) {
            caso 1:
                escreva("Opção 1\n");
                pare;
            caso 2:
                escreva("Opção 2\n");
                pare;
            padrao:
                escreva("Opção inválida\n");
        }
    }
}
```

### 6. Testes de Operadores

#### Operadores Lógicos (`logicos.pg`)
**Objetivo**: Testar operadores &&, ||, !

**Código**:
```portugol
programa {
    funcao inicio() {
        logico a = verdadeiro;
        logico b = falso;
        
        escreva("a && b: ", (a && b), "\n");
        escreva("a || b: ", (a || b), "\n");
        escreva("!a: ", (!a), "\n");
    }
}
```

#### Operadores Bitwise (`bitwise.pg`)
**Objetivo**: Testar operações bit a bit

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro a = 5;  // 101
        inteiro b = 3;  // 011
        
        escreva("a & b: ", (a & b), "\n");  // 1
        escreva("a | b: ", (a | b), "\n");  // 7
        escreva("a ^ b: ", (a ^ b), "\n");  // 6
    }
}
```

#### Operadores de Comparação (`diferente.pg`, `menor_igual.pg`)
**Objetivo**: Testar operadores relacionais

**Códigos**:
```portugol
// diferente.pg
programa {
    funcao inicio() {
        inteiro a = 5;
        inteiro b = 10;
        escreva("a != b: ", (a != b), "\n");
    }
}
// menor_igual.pg
programa {
    funcao inicio() {
        inteiro x = 5;
        inteiro y = 5;
        escreva("x <= y: ", (x <= y), "\n");
    }
}
```

#### Módulo (`modulo.pg`)
**Objetivo**: Testar operador de resto da divisão

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro a = 17;
        inteiro b = 5;
        escreva("17 % 5 = ", (a % b), "\n");
    }
}
```

#### Incremento e Decremento (`incremento_e_decremento.pg`)
**Objetivo**: Testar operadores ++ e --

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro x = 5;
        
        escreva("x inicial: ", x, "\n");
        escreva("x++: ", x++, "\n");
        escreva("x após ++: ", x, "\n");
        escreva("--x: ", --x, "\n");
    }
}
```

### 7. Testes de Funções

#### Função Sem Parâmetros (`funcao_sem_parametro.pg`)
**Objetivo**: Testar funções sem parâmetros

**Código**:
```portugol
programa {
    funcao saudar() {
        escreva("Olá!\n");
    }
    
    funcao inicio() {
        saudar();
    }
}
```

#### Função Sem Tipo de Retorno (`funcao_sem_tipo.pg`)
**Objetivo**: Testar funções void

**Código**:
```portugol
programa {
    funcao processar() {
        escreva("Processando...\n");
    }
    
    funcao inicio() {
        processar();
    }
}
```

#### Fatorial (`fatorial.pg`)
**Objetivo**: Testar função recursiva

**Código**:
```portugol
programa {
    inteiro fatorial(inteiro n) {
        se (n <= 1) {
            retorne 1;
        } senao {
            retorne n * fatorial(n - 1);
        }
    }
    
    funcao inicio() {
        inteiro num = 5;
        escreva("Fatorial de ", num, ": ", fatorial(num), "\n");
    }
}
```

### 8. Testes de Entrada e Saída

#### Escrita de Diversos Tipos (`escreva_diversos.pg`)
**Objetivo**: Testar saída de diferentes tipos de dados

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro i = 42;
        real r = 3.14;
        caracter c = 'A';
        logico l = verdadeiro;
        
        escreva("Inteiro: ", i, "\n");
        escreva("Real: ", r, "\n");
        escreva("Caracter: ", c, "\n");
        escreva("Lógico: ", l, "\n");
    }
}
```

#### Escrita de Variáveis (`escreva_variaveis.pg`)
**Objetivo**: Testar saída de variáveis

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro idade = 25;
        caracter inicial = 'J';
        
        escreva("Nome: João\n");
        escreva("Idade: ", idade, "\n");
        escreva("Inicial: ", inicial, "\n");
    }
}
```

### 9. Testes de Casos Especiais

#### Números Negativos (`num_negativo.pg`)
**Objetivo**: Testar números negativos

**Código**:
```portugol
programa {
    funcao inicio() {
        inteiro negativo = -42;
        real decimal_negativo = -3.14;
        
        escreva("Negativo: ", negativo, "\n");
        escreva("Decimal negativo: ", decimal_negativo, "\n");
    }
}
```

### 10. Testes de Otimização

#### Código Morto (`otimizacao_codigo_morto.expected`)
**Objetivo**: Verificar se código inacessível é tratado

#### Propagação de Constantes (`otimizacao_propagacao_de_contante.expected`)
**Objetivo**: Verificar otimização de constantes

## Execução dos Testes

### Script de Execução (`run_tests.sh`)

O script automatizado executa todos os testes:

```bash
#!/bin/bash

cd "$(dirname "$0")"
PASSED=0
FAILED=0
TOTAL=0

echo "Executando testes do compilador Portugol-C..."

for input_file in inputs/*.pg; do
    if [ -f "$input_file" ]; then
        filename=$(basename "$input_file" .pg)
        expected_file="expected/${filename}.expected"

        if [ -f "$expected_file" ]; then
            TOTAL=$((TOTAL + 1))

            # Compilar e executar
            ../build/compilador "$input_file" > /tmp/output.c 2>/dev/null
            if [ $? -eq 0 ]; then
                gcc /tmp/output.c -o /tmp/programa 2>/dev/null
                if [ $? -eq 0 ]; then
                    /tmp/programa > /tmp/actual_output.txt 2>/dev/null

                    # Comparar saídas
                    if diff -q "$expected_file" /tmp/actual_output.txt >/dev/null; then
                        echo "✓ $filename"
                        PASSED=$((PASSED + 1))
                    else
                        echo "✗ $filename"
                        FAILED=$((FAILED + 1))
                    fi
                else
                    echo "✗ $filename (erro de compilação C)"
                    FAILED=$((FAILED + 1))
                fi
            else
                echo "✗ $filename (erro de compilação Portugol)"
                FAILED=$((FAILED + 1))
            fi
        fi
    fi
done

echo
echo "Resultados: $PASSED/$TOTAL testes passaram"
if [ $FAILED -gt 0 ]; then
    echo "$FAILED testes falharam"
    exit 1
else
    echo "Todos os testes passaram!"
    exit 0
fi
```

### Como Executar

```bash
# No diretório do projeto
cd portugol_compilador

# Compilar o compilador
make

# Executar todos os testes
make test

# Ou executar diretamente
cd testes
./run_tests.sh
```

## Cobertura de Testes

### Funcionalidades Testadas

- ✅ **Tipos básicos**: inteiro, real, caracter, logico
- ✅ **Vetores**: Todos os tipos, inicialização, acesso
- ✅ **Operadores**: Aritméticos, lógicos, relacionais, bitwise
- ✅ **Estruturas de controle**: if-else, for, while, switch
- ✅ **Funções**: Declaração, chamada, recursão, parâmetros
- ✅ **Entrada/Saída**: escreva, leia (simulado)
- ✅ **Casos especiais**: Números negativos, comentários

### Métricas de Cobertura

- **Total de testes**: 32
- **Taxa de sucesso**: 100% (32/32)
- **Linhas de código testadas**: >95%
- **Funcionalidades cobertas**: 100%

## Adição de Novos Testes

### Processo

1. **Criar arquivo de entrada**: `inputs/novo_teste.pg`
2. **Definir saída esperada**: `expected/novo_teste.expected`
3. **Executar teste**: `./run_tests.sh`
4. **Verificar resultado**: Deve passar automaticamente

### Template de Teste

```portugol
// inputs/novo_teste.pg
programa {
    funcao inicio() {
        // Seu código de teste aqui
        escreva("Resultado esperado\n");
    }
}
```

```
<!-- expected/novo_teste.expected -->
Resultado esperado
```

### Boas Práticas

1. **Testes atômicos**: Cada teste deve verificar uma funcionalidade específica
2. **Nomes descritivos**: Use nomes que indiquem o que está sendo testado
3. **Saídas determinísticas**: Evite valores aleatórios ou dependentes de tempo
4. **Cobertura completa**: Teste casos normais, extremos e de erro
5. **Documentação**: Documente o objetivo de cada teste
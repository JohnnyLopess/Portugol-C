# Tipos de Dados

O compilador Portugol-C oferece suporte a diferentes tipos de dados primitivos, permitindo a criação de programas robustos e versáteis.

## Tipos Suportados

### Inteiro
- **Palavra-chave:** `inteiro`
- **Equivalente em C:** `int`
- **Descrição:** Números inteiros com sinal
- **Exemplo:**
```portugol
inteiro idade;
inteiro contador = 10;
```

### Real
- **Palavra-chave:** `real`
- **Equivalente em C:** `float`
- **Descrição:** Números de ponto flutuante
- **Exemplo:**
```portugol
real altura;
real preco = 19.99;
real pi = 3.14159;
```

### Caracter
- **Palavra-chave:** `caracter`
- **Equivalente em C:** `char`
- **Descrição:** Caracteres ASCII individuais
- **Exemplo:**
```portugol
caracter letra;
caracter inicial = 'A';
caracter simbolo = '@';
```

### Logico
- **Palavra-chave:** `logico`
- **Equivalente em C:** `int` (0 ou 1)
- **Descrição:** Valores booleanos verdadeiro ou falso
- **Exemplo:**
```portugol
logico ativo;
logico valido = verdadeiro;
logico concluido = falso;
```

## Declaração de Variáveis

### Sintaxe Básica
```portugol
tipo nome_variavel;
tipo nome_variavel = valor_inicial;
```

### Exemplos de Declarações
```portugol
// Declarações simples
inteiro x;
real nota;
caracter grade;
logico aprovado;

// Declarações com inicialização
inteiro idade = 25;
real salario = 3500.50;
caracter categoria = 'A';
logico ativo = verdadeiro;
```

## Inicialização

Todas as variáveis podem ser inicializadas no momento da declaração ou receber valores posteriormente através de atribuições.

### Valores Padrão
- **inteiro:** 0 (quando não inicializado explicitamente)
- **real:** 0.0
- **caracter:** '\0' (caractere nulo)
- **logico:** falso

### Literais

#### Inteiros
- Números inteiros positivos ou negativos
- Exemplos: `42`, `-15`, `0`, `1000`

#### Reais
- Números decimais com ponto como separador
- Exemplos: `3.14`, `-2.5`, `0.0`, `100.99`

#### Caracteres
- Caracteres entre aspas simples
- Exemplos: `'a'`, `'Z'`, `'9'`, `'@'`

#### Lógicos
- Palavras-chave: `verdadeiro` e `falso`
- Equivalem a 1 e 0 respectivamente em C

## Conversões de Tipo

O compilador realiza conversões automáticas quando necessário:

### Conversões Implícitas
- `inteiro` → `real`: Automática quando necessário
- `caracter` → `inteiro`: Valor ASCII do caractere
- `logico` → `inteiro`: verdadeiro=1, falso=0

### Exemplos de Uso
```portugol
programa {
    funcao inicio() {
        inteiro num = 42;
        real decimal = 3.14;
        caracter letra = 'A';
        logico status = verdadeiro;
        
        escreva("Número: ", num, "\n");
        escreva("Decimal: ", decimal, "\n");
        escreva("Letra: ", letra, "\n");
        escreva("Status: ", status, "\n");
    }
}
```

## Limitações

- Não há verificação de overflow/underflow em tempo de execução
- Strings devem ser implementadas como vetores de caracteres
- Não há garbage collection automático
- Precisão de números reais limitada pelo tipo `float` do C

## Boas Práticas

1. **Inicialize variáveis:** Sempre inicialize variáveis antes do uso
2. **Nomes descritivos:** Use nomes que descrevam o propósito da variável
3. **Tipo apropriado:** Escolha o tipo mais adequado para cada situação
4. **Conversões explícitas:** Seja explícito em conversões quando possível

```portugol
// Boa prática
inteiro idade = 0;
real salario = 0.0;
caracter categoria = 'N';
logico ativo = falso;

// Em vez de
inteiro x;
real y;
caracter z;
logico w;
```

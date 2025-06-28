# Como Usar o Compilador

## Visão Geral

O Compilador Portugol-C traduz programas escrititos em Portugol para código C equivalente. O processo é simples e direto.

## Estrutura Básica de um Programa Portugol

Todo programa Portugol deve seguir esta estrutura:

```portugol
programa {
    funcao inicio() {
        // Seu código aqui
    }
}
```

## Compilando um Arquivo

### Passo 1: Criar um arquivo Portugol

Crie um arquivo com extensão `.pg`:

```bash
# Exemplo: criar hello.pg
echo 'programa {
    funcao inicio() {
        escreva("Hello, World!")
    }
}' > hello.pg
```

### Passo 2: Compilar o arquivo

```bash
# Compilar um arquivo específico
make run FILE=hello.pg

# Ou usar um arquivo da pasta de exemplos
make run FILE=exemplos/exemplo1.pg
```

### Passo 3: Executar o código C gerado

```bash
# Compilar o código C gerado
gcc build/saida.c -o programa

# Executar o programa
./programa
```

## Comandos Disponíveis

### Compilação

```bash
# Compilar o compilador
make

# Compilar e executar um arquivo Portugol
make run FILE=<caminho_para_arquivo.pg>

# Limpar arquivos gerados
make clean
```

### Testes

```bash
# Executar todos os testes
make test

# Verificar versão do GCC
make check_gcc_version
```

## Exemplos de Uso

### Exemplo 1: Variáveis e Operações

```portugol
programa {
    funcao inicio() {
        inteiro idade
        real altura
        idade = 25
        altura = 1.75
        escreva("Idade: ", idade)
        escreva("Altura: ", altura)
    }
}
```

### Exemplo 2: Estruturas de Controle

```portugol
programa {
    funcao inicio() {
        inteiro numero
        leia(numero)
        
        se (numero > 0) {
            escreva("Número positivo")
        } senao {
            escreva("Número não positivo")
        }
    }
}
```

### Exemplo 3: Vetores

```portugol
programa {
    funcao inicio() {
        inteiro v[3]
        v[0] = 10
        v[1] = 20
        v[2] = 30
        
        escreva("Primeiro elemento: ", v[0])
    }
}
```

### Exemplo 4: Laços

```portugol
programa {
    funcao inicio() {
        inteiro i
        
        para (i = 1; i <= 5; i = i + 1) {
            escreva("Número: ", i)
        }
    }
}
```

## Saída Esperada

Após a compilação, o compilador gera:

1. **build/saida.c** - Código C equivalente
2. **Mensagens de debug** - Durante a compilação (opcional)
3. **Verificação de erros** - Análise léxica e sintática

## Fluxo Completo

```bash
# 1. Escrever código Portugol
nano meu_programa.pg

# 2. Compilar
make run FILE=meu_programa.pg

# 3. Verificar saída C gerada
cat build/saida.c

# 4. Compilar e executar o C
gcc build/saida.c -o meu_programa
./meu_programa
```

## Dicas Importantes

!!! tip "Sintaxe"
    - Use chaves `{}` para delimitar blocos
    - Termine comandos com ponto e vírgula quando necessário
    - Declare variáveis antes de usar

!!! warning "Cuidados"
    - Nomes de variáveis devem começar com letra
    - Tipos de dados devem ser declarados explicitamente
    - Arrays precisam ter tamanho fixo definido

!!! note "Observação"
    - O compilador gera código C otimizado
    - Verificações de erro são feitas automaticamente
    - Suporte a comentários de linha (`//`) e bloco (`/* */`)
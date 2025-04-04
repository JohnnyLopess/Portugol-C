# 📦 Sprint 1 — Compilador Portugol → C

## ✅ Objetivo

Construir a base funcional do compilador utilizando Flex e Bison, com tradução de comandos básicos do Portugol (de acordo com o Portugol Studio) para código C válido.

---

## 🗂️ Estrutura de Diretórios

```
portugol_compilador/
├── exemplos/
│   └── exemplo1.pg          # Arquivo de entrada em Portugol usado para testes
├── lex.l                    # Arquivo Flex com regras léxicas
├── yacc.y                   # Arquivo Bison com a gramática e geração de código C
├── main.c                   # Função principal que inicia o compilador
├── makefile                 # Script de compilação automatizada
├── lex.yy.c                 # Gerado pelo Flex a partir de lex.l
├── y.tab.c                  # Gerado pelo Bison a partir de yacc.y
├── y.tab.h                  # Header gerado pelo Bison com definições de tokens
├── saida.c                  # Código C gerado como saída pelo compilador
```

---

## 📝 Descrição dos Arquivos

- **`lex.l`**: Define os padrões léxicos (tokens) usados no Portugol, como palavras-chave, identificadores, números, operadores, etc.
- **`yacc.y`**: Define a gramática do Portugol e traduz comandos como `var`, `leia`, `escreva` e expressões aritméticas para C.
- **`main.c`**: Inicia a análise sintática, imprimindo mensagens e lidando com erros.
- **`makefile`**: Automatiza a geração do compilador (`make`, `flex`, `bison`, `gcc`).
- **`exemplos/exemplo1.pg`**: Um programa de teste escrito em Portugol para alimentar o compilador.
- **`lex.yy.c`**, **`y.tab.c`**, **`y.tab.h`**: Arquivos intermediários gerados automaticamente por Flex e Bison.
- **`saida.c`**: Arquivo final de saída contendo o código C traduzido.

---

## 🧪 Funcionalidades Concluídas

- Reconhecimento e tradução de:
  - Declarações de variáveis (`var`)
  - Leitura de dados (`leia`)
  - Escrita de dados (`escreva`)
  - Atribuições com expressões aritméticas (`=`, `+`, `-`)
- Geração de código C pronto para compilação com `gcc`.

---

## 🏁 Status da Sprint

🎯 Sprint 1 concluída com sucesso.  
A base do compilador está funcional e preparada para evoluções.

---

## 🚀 Como testar o compilador

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemplo1.pg
```

O compilador irá gerar um arquivo chamado `saida.c` com o código equivalente em C.

### 3. Compile o código C gerado

```bash
gcc saida.c -o programa
./programa
```

---

### 🧹 Limpando arquivos gerados

Caso necessário, você pode executar o comando abaixo para remover todos os arquivos gerados automaticamente (como `lex.yy.c`, `y.tab.c`, `y.tab.h`, `saida.c`, etc.):

```bash
make clean
```
---


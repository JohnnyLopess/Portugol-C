# 📦 Sprint 9 — Comentários em Portugol ((25/05 - 31/05))

| Matrícula | Nome                                      | Nick no GitHub |                                                      📸                                                       |
| :-------: | ----------------------------------------- | -------------- | :----------------------------------------------------------------------------------------------------------: |
| x |  x                 | x       |  [](https://github.com/)   |


## Objetivo:
- Implementar um sistema de conversão de comentários do Portugol `//`, `/*` `*/` para C.

---

## 🧪 Funcionalidades Concluídas

### 🧩 Palavras-chave adicionadas
- `//`
- `/*`
- `*/`

### 🔢 Operadores relacionais reconhecidos
- `//`
- `/*`
- `*/`

## 🚀 Como testar as novas funcionalidades ?

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemploX.pg
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


## ✅ Critérios de aceitação

| Critério | Descrição | Status |
|---------|-----------|--------|
| 🔤 **Comentários** | Código comentado, limpo e modular. | ✅ |
| 🔤 **Testes** | Implementar casos de testes para cada um dos recursos | ✅ |

---

## 📁 Arquivos modificados

- `lex.l`: Adição de tokens relacionais e palavras-chave de decisão
- `yacc.y`: Regras novas para blocos condicionais e operadores lógicos
- `exemplos/exemploX.pg`: Script Portugol usado como teste da sprint

---

## 🔚 Conclusão

A Sprint 9 foi **concluída com sucesso**, consolidando a implementação de um sistema de conversão de comentários da linguagem Portugol — `//`, `/*` e `*/` — para a sintaxe equivalente da linguagem C, garantindo que os comentários sejam preservados corretamente no código traduzido.

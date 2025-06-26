# Sprint 5 — Tipagem e Robustez + P1 (27/04 - 03/05)

| Matrícula | Nome                                      | Nick no GitHub |                                                      📸                                                       |
| :-------: | ----------------------------------------- | -------------- | :----------------------------------------------------------------------------------------------------------: |
| 211061977 | João Victor Costa Andrade                 | jvcostta       |  [<img src="https://avatars.githubusercontent.com/u/124215106?v=4" width=50>](https://github.com/jvcostta)   |


## Objetivo:
- Ampliar o suporte para novos tipos de dados `inteiro`, `real` e `caracter` e corrigir a regra de declaração de variáveis no analisador sintático.

---

## 🧪 Funcionalidades Concluídas
- Suporte mais robusto para tipagem de dados `inteiro`, `real` e `caracter` e regra de declaração corrigida

## 🚀 Como testar as novas funcionalidades ?

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemplo5.pg
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
| 🔤 **Declaração** | Declaração de variáveis com tipo funcionando corretamente. | ✅ |
| 🧠 **Compilação** | Compilação correta no C (int, float, char). | ✅ |
| 🧪 **Exemplo testado** | Arquivo `exemplo5.pg` executado e traduzido corretamente | ✅ |

---

## 📁 Arquivos modificados

- `lex.l`: Adição de tokens relacionais e palavras-chave de decisão
- `yacc.y`: Regras novas para blocos condicionais e operadores lógicos
- `exemplos/exemplo5.pg`: Script Portugol usado como teste da sprint

---

##  Conclusão

- A Sprint 5 foi **concluída com sucesso**, consolidando a ampliação do suporte a novos tipos de dados — `inteiro`, `real` e `caracter` — e a correção da regra de declaração de variáveis no analisador sintático, tornando a análise mais robusta e alinhada à sintaxe da linguagem Portugol.

# Sprint 3 — Estruturas de Repetição (enquanto ... faca ... fimenquanto) (13/04 - 19/04)

| Matrícula | Nome                                      | Nick no GitHub |                                                      📸                                                       |
| :-------: | ----------------------------------------- | -------------- | :----------------------------------------------------------------------------------------------------------: |
| x |  x                 | x       |  [](https://github.com/)   |

 
## Objetivo:
- Adicionar suporte à estrutura de repetições `enquanto`, `faca` e `fimenquanto` e operadores relacionais, gerando código C válido com blocos `while`.

---

## 🧪 Funcionalidades Concluídas

### 🧩 Palavras-chave adicionadas
- `enquanto`
- `faca`
- `fimenquanto`

## 🚀 Como testar as novas funcionalidades ?

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemplo3.pg
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
| 🔤 **Laços de repetição são reconhecidos e compilados corretamente.** | Tokens para `enquanto`, `faca` e `fimenquanto` e operadores de repetição | ✅ |
| 🧾 **saida.c funcional** | Arquivo C gerado compila e executa corretamente | ✅ |

---

## 📁 Arquivos modificados

- `lex.l`: Adição de tokens relacionais e palavras-chave de decisão
- `yacc.y`: Regras novas para blocos de repetição e operadores lógicos
- `exemplos/exemplo3.pg`: Script Portugol usado como teste da sprint

---

## 🔚 Conclusão

A Sprint 3 foi **concluída com sucesso**, consolidando a base do compilador com controle de fluxo de repetição. O sistema agora suporta repetições simples e compostas, sendo possível testar condições usando operadores de repetição com tradução correta para C.

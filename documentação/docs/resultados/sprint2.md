# 📦 Sprint 2 — Controle de Fluxo (Condicionais)
 
**Objetivo:** Adicionar suporte a estruturas condicionais `se`, `senao`, `fimse` e operadores relacionais, gerando código C válido com blocos `if` e `else`.

---

## 🧪 Funcionalidades Concluídas

### 🧩 Palavras-chave adicionadas
- `se`
- `entao`
- `senao`
- `fimse`

### 🔢 Operadores relacionais reconhecidos
- `==` (igual)
- `!=` (diferente)
- `<`, `>`, `<=`, `>=`


## 🚀 Como testar as novas funcionalidades ?

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemplo2.pg
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
| 🔤 **Léxico** | Tokens para `se`, `entao`, `senao`, `fimse` e operadores relacionais | ✅ |
| 🧠 **Sintático** | Regras no `yacc.y` para condicionais | ✅ |
| 🔁 **Blocos de decisão** | Suporte a `if` simples e `if/else` com múltiplos comandos | ✅ |
| 💬 **Expressões relacionais** | Suporte completo a comparações entre expressões | ✅ |
| 🧪 **Exemplo testado** | Arquivo `exemplo2.pg` executado e traduzido corretamente | ✅ |
| 🧾 **saida.c funcional** | Arquivo C gerado compila e executa corretamente | ✅ |

---

## 📁 Arquivos modificados

- `lex.l`: Adição de tokens relacionais e palavras-chave de decisão
- `yacc.y`: Regras novas para blocos condicionais e operadores lógicos
- `exemplos/exemplo2.pg`: Script Portugol usado como teste da sprint

---

## 🔚 Conclusão

A Sprint 2 foi **concluída com sucesso**, consolidando a base do compilador com controle de fluxo condicional. O sistema agora suporta decisões simples e compostas, sendo possível testar condições usando operadores relacionais com tradução correta para C.

**Próxima Sprint:** Implementação de laços de repetição `enquanto ... faca ... fimenquanto`.
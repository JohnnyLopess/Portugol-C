# Sprint 4 — Estruturas de Repetição: Para (23/04 a 29/04)


| Matrícula | Nome                                      | Nick no GitHub |                                                      📸                                                       |
| :-------: | ----------------------------------------- | -------------- | :----------------------------------------------------------------------------------------------------------: |
| x |  x                 | x       |  [](https://github.com/)   |

 
## Objetivo:
- Adicionar suporte às estruturas de repetição `para`, `de`, `ate`, `fimpara`
 e operadores relacionais, gerando código C válido.

---

## 🧪 Funcionalidades Concluídas

### 🧩 Palavras-chave adicionadas
- `para`
- `de`
- `ate`
- `fimpara`


## 🚀 Como testar as novas funcionalidades ?

### 1. Compile o compilador com o Makefile

```bash
make
```

> Isso irá rodar `flex`, `bison` e `gcc` automaticamente para gerar o binário `compilador`.

### 2. Execute com um arquivo de exemplo

```bash
./compilador < exemplos/exemplo4.pg
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
| 🔤 **Laços de repetição são reconhecidos e compilados corretamente.** | Tokens para `para`, `de`, `ate`, `fimpara` e operadores de repetição | ✅ |
| 🧾 **saida.c funcional** | Quarto exemplo `exemplo4.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente. | ✅ |

---

## 📁 Arquivos modificados

- `lex.l`: Adição de tokens relacionais e palavras-chave de decisão
- `yacc.y`: Regras novas para blocos condicionais e operadores lógicos
- `exemplos/exemplo4.pg`: Script Portugol usado como teste da sprint

---

##  Conclusão

A Sprint 2 foi **concluída com sucesso**, consolidando a base do compilador com controle de fluxo condicional. O sistema agora suporta decisões simples e compostas, sendo possível testar condições usando operadores relacionais com tradução correta para C.

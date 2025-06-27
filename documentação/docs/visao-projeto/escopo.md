# 📘 Escopo da Linguagem - Tradutor Portugol → C

Este documento descreve o **escopo da linguagem Portugol** que será utilizado no projeto do Compilador Portugol → C. O escopo está **baseado no Portugol Studio**, garantindo compatibilidade e permitindo testes diretos na própria IDE do Portugol Studio.

---

## ✅ Estruturas de Controle

- `se ... entao ... fimse`
- `se ... entao ... senao ... fimse`
- `enquanto ... faca ... fimenquanto`
- `para ... de ... ate ... faca ... fimpara`
- `repita ... ate`

---

## ✅ Entrada e Saída de Dados

- `leia(variavel)`
- `escreva(...)`

---

## ✅ Declaração de Variáveis

- Bloco `var` com os seguintes tipos:
  - `inteiro`
  - `real`
  - `caracter`
  - `logico`

Exemplo:
```portugol
var
    inteiro x, y
    real z
```

---

## ✅ Operadores Suportados

### Aritméticos
- `+` (adição)
- `-` (subtração)
- `*` (multiplicação)
- `/` (divisão real)

### Relacionais
- `=` (igual)
- `<>` (diferente)
- `<`, `>`, `<=`, `>=`

### Lógicos
- `e`
- `ou`
- `nao`

### Bit a Bit Unarios

- `&` (bitwise AND)
- `~` (bitwise NOT)
- `|` (bitwise OR)
- `^` (bitwise XOR)

---

## ✅ Tipos de Dados

- `inteiro`
- `real`
- `caracter`
- `logico`

---

## ✅ Comentários

- Linha: `// comentário`
- Bloco: `{ comentário }`

---

## ✅ Outros Elementos

- O escopo de cada funcao é delimitado por abre e fecha chaves (`{}`)
- `const` → declaração de constantes
- `retorne` → retorno de valor em funções
- `procedimento` / `funcao` → modularização de código
- Suporte a `vetores` e `matrizes`

---

## 🔎 Observação

Durante o desenvolvimento, esse escopo poderá ser **ajustado de forma incremental**, mas toda funcionalidade nova será validada antes com testes no **Portugol Studio**, garantindo compatibilidade total.


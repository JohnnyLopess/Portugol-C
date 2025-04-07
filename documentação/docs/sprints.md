# 📘 Projeto Tradutor Portugol → C

Este é o repositório do projeto da disciplina **Compiladores 1 (2025/1)**, ministrada pelo professor Dr. Sergio Freitas na UnB. Nosso grupo está desenvolvendo um **tradutor de Portugol para C**, utilizando as ferramentas **Flex** e **Bison**.

## ⚙️ Ferramentas 

### Bison

Bison é uma ferramenta de geração de analisadores sintáticos (parsers) que trabalha em conjunto com o Flex. É o sucessor do Yacc (Yet Another Compiler Compiler) e é mantido pelo projeto GNU.

#### Uso no Projeto Portugol → C

- Definir a gramática da linguagem Portugol
- Gerar código C equivalente
- Tratar estruturas de controle 
- Manipular expressões e declarações

### Flex

O Flex é uma ferramenta moderna que gera analisadores léxicos (scanners). É o sucessor do programa Lex original do Unix e é amplamente utilizado no desenvolvimento de compiladores.

#### Uso no Projeto Portugol → C

- Reconhecer tokens da linguagem Portugol (palavras-chave, identificadores, números)
- Gerar o arquivo lex.yy.c que implementa o scanner
- Integrar com o parser Bison para análise completa do código

## 📅 Organização por Sprints

O desenvolvimento foi dividido em **6 sprints quinzenais**, iniciando em **02/04/2025** e terminando com a entrega final em **27/06/2025**. Utilizamos **issues** no GitHub para organizar as tarefas de cada sprint com critérios claros de aceitação (_definition of done_).

---

## 🧩 Sprint 1 – Setup do Compilador e Primeiros Comandos (02/04 a 16/04)

**Objetivos:**
- Definir escopo da linguagem Portugol
- Criar estrutura de pastas e arquivos
- Configurar o ambiente de compilação com Flex, Bison e GCC.
- Criar um compilador inicial que reconheça e traduza comandos básicos.

**Critérios de Aceitação:**
- Scanner reconhece tokens básicos
- Ambiente compilável (makefile, main.c, lex.l, yacc.y)
- Reconhecimento de:

    - `inicio`, `fim`
    - `var`, `declaração de variáveis`
    - `leia`, `escreva`
    - Atribuições e expressões aritméticas simples

- Geração de `saida.c` com main, scanf, printf, etc.
- Projeto compila com `make`
- Arquivo `exemplo1.pg` funciona


---

## 🧩 Sprint 2 – Controle de Fluxo (Condicionais) (17/04 a 30/04)

**Objetivos:**
Adicionar suporte à estrutura de decisão se ... entao ... senao ... fimse e operadores relacionais.

**Critérios de Aceitação:**
- Reconhecimento dos tokens:
    - `se`, `entao`, `senao`, `fimse`
    - `==`, `!=`, `<`, `>`, `<=`, `>=`
- Tradução para `if (...) { ... } else { ... }`
- Código com estruturas condicionais em Portugol é convertido corretamente para C.
- `saida.c` compila e executa com a lógica esperada

## 🧩 Sprint 3 – Estruturas de Repetição (enquanto ... faca ... fimenquanto) (01/05 a 15/05)

**Objetivos:**
Adicionar suporte à estrutura de repetição com tradução para while.

**Critérios de Aceitação:**
- `enquanto`, `faca`, `fimenquanto`
- Laços enquanto são reconhecidos e traduzidos
- Comandos internos são executados corretamente em saida.c

---

## 🧩 Sprint 4 – Controle de fluxo + P2 (16/05 a 30/05)

**Objetivos:**
- Implementar estruturas: `se`, `enquanto`, etc.
- Traduzir controle de fluxo para C
- Realizar a apresentação do P2

**Critérios de Aceitação:**
- Estruturas traduzidas corretamente
- Código C legível e funcional
- Apresentação do P2 realizada

---

## 🧩 Sprint 5 – Tipagem e robustez (31/05 a 13/06)

**Objetivos:**
- Adicionar verificação de variáveis
- Tratar tipos e escopos simples
- Melhorar mensagens de erro

**Critérios de Aceitação:**
- Verificação de variáveis não declaradas
- Tratamento básico de tipos
- Erros bem localizados e informativos

---

## 🧩 Sprint 6 – Finalização e entrega (14/06 a 27/06)

**Objetivos:**
- Refatorar e organizar o código
- Testar com múltiplos arquivos
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Projeto entregue e funcional
- Código C gerado compila corretamente
- Casos de teste bem documentados

---

## 👥 Participantes

- (Adicione aqui os nomes dos integrantes do grupo)

---

> Qualquer dúvida ou sugestão, entre em contato via [Issues](https://github.com/SEU_USUARIO/SEU_REPOSITORIO/issues).

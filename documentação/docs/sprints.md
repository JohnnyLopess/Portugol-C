# 📘 Projeto Tradutor Portugol → C

Este é o repositório do projeto da disciplina **Compiladores 1 (2025/1)**, ministrada pelo professor Dr. Sergio Freitas na UnB. O objetivo do projeto é desenvolver um tradutor de Portugol para C, utilizando as ferramentas Flex e Bison para construção dos analisadores léxico e sintático..

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

### GCC e Makefile

- Ferramentas para compilar o código e automatizar o processo de build.

## 📅 Organização por Sprints

O desenvolvimento foi dividido em **12 sprints semanais**, iniciando em **02/04/2025** e terminando com a entrega final em **27/06/2025**. Utilizamos **issues** no GitHub para organizar as tarefas de cada sprint com critérios claros de aceitação (_definition of done_).

---

## 🧩 Sprint 1 – Estrutura Inicial e Comandos Básicos (02/04 a 08/04)

**Objetivos:**
- Definir escopo da linguagem Portugol suportada(UniVali).
- Criar a estrutura inicial do projeto (pastas, Makefile, arquivos principais).
- Configurar ambiente de desenvolvimento (Flex, Bison, GCC).
- Criar um compilador inicial que reconheça e traduza comandos básicos.
- Implementar o reconhecimento e tradução dos seguintes elementos:
    - `inicio`, `fim`
    - `var`, `declaração de variáveis`
    - `leia`, `escreva`
    - Atribuições e expressões aritméticas simples(`+`, `-`, `*`, `/`).

**Critérios de Aceitação:**
- Projeto compila corretamente usando `make`.
- Geração de arquivo `saida.c` funcional.
- Primeiro exemplo `exemplo1.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente.


---

## 🧩 Sprint 2 – Implementação de Estruturas Condicionais (09/04 a 15/04)

**Objetivos:**
- Adicionar suporte à estrutura condicional:
    - `se`, `entao`, `senao`, `fimse`
- Implementar operadores relacionais:
    - `==`, `!=`, `<`, `>`, `<=`, `>=`

**Critérios de Aceitação:**
- Condições corretamente analisadas e compiladas.
- Código com estruturas condicionais em Portugol é convertido corretamente para C.
- Segundo exemplo `exemplo2.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente.

## 🧩 Sprint 3 – Implementação de Estruturas de Repetição: Enquanto (16/04 a 22/04)

**Objetivos:**
- Adicionar suporte às estruturas de repetição:
    - `enquanto`, `faca`, `fimenquanto`

**Critérios de Aceitação:**

- Laços de repetição são reconhecidos e compilados corretamente.
- Terceiro exemplo `exemplo3.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente.

---

## 🧩 Sprint 4 – Estruturas de Repetição: Para (23/04 a 29/04)

**Objetivos:**
- Adicionar suporte às estruturas de repetição:
    - `para`, `de`, `ate`, `fimpara`

**Critérios de Aceitação:**
- Laços de repetição são reconhecidos e compilados corretamente.
- Quarto exemplo `exemplo4.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente.

---

## 🧩 Sprint 5 – Tipagem de Variáveis(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (30/04 a 06/05)

**Objetivos:**
- Ampliar o suporte para novos tipos de dados:
    - `inteiro`, `real` e `caractere`
- Corrigir a regra de declaração de variáveis no analisador sintático.

**Critérios de Aceitação:**
- Declaração de variáveis com tipo funcionando corretamente.
- Compilação correta no C (int, float, char).

---

## 🧩 Sprint 6 – Leitura e Escrita de Diferentes Tipos(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---

## 🧩 Sprint 7 – Análise Semântica Inicial (07/05 a 13/05)

**Objetivos:**
- Verificar se variáveis são declaradas antes do uso.
- Implementar tabela de símbolos simples para armazenamento de identificadores e seus tipos.

**Critérios de Aceitação:**
- Erros de variáveis não declaradas detectados.
- Execução abortada em caso de erro semântico.

---

## 🧩 Sprint 8 – Tratamento de Erros e Robustez (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---

## 🧩 Sprint 9 – Leitura e Escrita de Diferentes Tipos(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---

## 🧩 Sprint 10 – Leitura e Escrita de Diferentes Tipos(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---

## 🧩 Sprint 11 – Leitura e Escrita de Diferentes Tipos(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---

## 🧩 Sprint 12 – Leitura e Escrita de Diferentes Tipos(Correção de Erros encontrados no desenvolvimento do POnto de Controle 1) (07/05 a 13/05)

**Objetivos:**
- Ajustar a geração do `scanf` e `printf` para cada tipo de variável.
- Exibir mensagens apropriadas ao tipo (ex: `%d`, `%f`, `%c`).
- Entregar no Teams (até 27/06)

**Critérios de Aceitação:**
- Leitura e escrita de variáveis de diferentes tipos funcionando corretamente.

---
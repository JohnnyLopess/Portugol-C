## ⚙️ Ferramentas 

### Bison

Bison é uma ferramenta de geração de analisadores sintáticos (parsers), mantida pelo projeto GNU e sucessora do Yacc (Yet Another Compiler Compiler). Neste projeto, o Bison é utilizado para definir a gramática da linguagem Portugol, permitindo identificar e estruturar corretamente expressões, declarações e comandos de controle de fluxo. A ferramenta gera código C correspondente à estrutura sintática reconhecida, integrando-se ao Flex para compor o analisador completo do compilador.

### Flex

Flex é uma ferramenta moderna utilizada para gerar analisadores léxicos (scanners), sendo o sucessor do tradicional Lex do Unix. Neste projeto, o Flex é responsável por reconhecer os tokens da linguagem Portugol, como palavras-chave, identificadores e números. Ele gera automaticamente o arquivo lex.yy.c, que implementa o scanner léxico e integra-se ao Bison para permitir a análise completa do código-fonte durante o processo de compilação.

### GCC e Makefile

- Ferramentas para compilar o código e automatizar o processo de build.

## 📅 Organização por Sprints

O desenvolvimento foi dividido em **13 sprints**, sendo elas semanais, iniciando em **30/03/2025** e terminando com a entrega final em **27/06/2025**. Utilizamos o **gitpages** no GitHub para organizar as tarefas de cada sprint com critérios claros de aceitação (_definition of done_).

---

## 🧩 Sprint 1 –Setup do Compilador e Primeiros Comandos (30/03 - 05/04)

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

## 🧩 Sprint 2 – Controle de Fluxo(Condicionais) (06/04 - 12/04)

**Objetivos:**
- Adicionar suporte à estrutura condicional:
    - `se`, `entao`, `senao`, `fimse`
- Implementar operadores relacionais:
    - `==`, `!=`, `<`, `>`, `<=`, `>=`

**Critérios de Aceitação:**
- Condições corretamente analisadas e compiladas.
- Código com estruturas condicionais em Portugol é convertido corretamente para C.
- Segundo exemplo `exemplo2.pg`, que teste as funcionalidades implementadas, compilado e executado corretamente.

## 🧩 Sprint 3 – Estrutura de Repetição(enquanto…faca…fimenquanto) (13/04 - 19/04)

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

## 🧩 Sprint 5 – Tipagem e Robustez + P1 (27/04 - 03/05)

**Objetivos:**
- Ampliar o suporte para novos tipos de dados:
    - `inteiro`, `real` e `caractere`
- Corrigir a regra de declaração de variáveis no analisador sintático.

**Critérios de Aceitação:**
- Declaração de variáveis com tipo funcionando corretamente.
- Compilação correta no C (int, float, char).

---

## 🧩 Sprint 6 – Sistema de Testes Automatizados (04/05 - 10/05)

**Objetivos:**
- implementar um sistema de testes automatizados completo para o compilador Portugol-C que permite verificar se a geração de código C está funcionando conforme o esperado.

**Critérios de Aceitação:**
- Sistema de Testes Automatizados funcionando corretamente.

---

## 🧩 Sprint 7 – AST (11/05 - 17/05)

**Objetivos:**
- Construção da Árvore de Derivação Sintática

---

## 🧩 Sprint 8 – Recursos Avançados do Portugol (18/05 - 24/05)

**Objetivos:**
- Implementar recursos “senão se” e “switch/case (escolha, caso, fimcaso) ”

**Critérios de Aceitação:**
- Implementar casos de testes para cada um dos recursos
- Todos testes devem estar funcionando
---  

## 🧩 Sprint 9 – Comentários em Portugol ((25/05 - 31/05))

**Objetivos:**
- Conversão de comentários do Portugol (//, /* */) para C.

**Critérios de Aceitação:**
- Código comentado, limpo e modular.
- Implementação de casos de teste

---

## 🧩 Sprint 10 – Novos Tipos + P2 (01/06 a 07/06)

**Objetivos:**
- Reconhecimento e tratamento dos tipos null e lógico (booleano) e apresentação do P2
---

## 🧩 Sprint 11 – Análise Semântica, Tabela de Símbolos + Disponibilização do GitHub 

**Objetivos:**
- Verificar se variáveis são declaradas antes do uso.
- Implementar tabela de símbolos simples para armazenamento de identificadores e seus tipos.
- Disponibilizar Repositório.

**Critérios de Aceitação:**
- Erros de variáveis não declaradas detectados.
- Execução abortada em caso de erro semântico.

---

## 🧩 Sprint 12 – Correções e Integração Final (15/06 - 21/06)

**Objetivos:**
- Correção de bugs e inconsistências
- Organização do código final
- Últimos testes com múltiplos arquivos .pg


## 🧩 Sprint 13 – Entrega e Apresentação Final (22/06 - 28/06)

**Objetivos:**
- Preparação para entrega do projeto, entrevista/apresentação finals

---
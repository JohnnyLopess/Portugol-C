# 📘 Projeto Tradutor Portugol → C

Este é o repositório do projeto da disciplina **Compiladores 1 (2025/1)**, ministrada pelo professor Dr. Sergio Freitas na UnB. Nosso grupo está desenvolvendo um **tradutor de Portugol para C**, utilizando as ferramentas **Flex** e **Bison**.

## 📅 Organização por Sprints

O desenvolvimento foi dividido em **6 sprints quinzenais**, iniciando em **02/04/2025** e terminando com a entrega final em **27/06/2025**. Utilizamos **issues** no GitHub para organizar as tarefas de cada sprint com critérios claros de aceitação (_definition of done_).

---

## 🧩 Sprint 1 – Estrutura inicial + Scanner (02/04 a 16/04)

**Objetivos:**
- Definir escopo da linguagem Portugol
- Criar estrutura de pastas e arquivos
- Implementar scanner com Flex
- Testar tokens com arquivos de entrada

**Critérios de Aceitação:**
- Scanner reconhece tokens básicos
- Projeto compila com `make`
- Arquivo `exemplo1.pg` funciona

---

## 🧩 Sprint 2 – Parser básico + P1 (17/04 a 30/04)

**Objetivos:**
- Criar parser com Bison (`leia`, `escreva`, atribuições)
- Iniciar análise sintática de expressões
- Realizar a apresentação do P1

**Critérios de Aceitação:**
- Parser e scanner integrados
- Estruturas básicas reconhecidas
- Apresentação do P1 realizada

---

## 🧩 Sprint 3 – AST + Tradução para C (01/05 a 15/05)

**Objetivos:**
- Construção da AST
- Início da geração de código C
- Traduzir `leia`, `escreva`, `x = ...`

**Critérios de Aceitação:**
- AST funcional
- Código C gerado corretamente
- Documentação de uso do tradutor

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

## 🚀 Ferramentas Utilizadas

- **Flex** (scanner)
- **Bison** (parser)
- **C** (back-end do tradutor)
- **GitHub Projects** (gerenciamento de tarefas)

---

## 👥 Participantes

- (Adicione aqui os nomes dos integrantes do grupo)

---

> Qualquer dúvida ou sugestão, entre em contato via [Issues](https://github.com/SEU_USUARIO/SEU_REPOSITORIO/issues).

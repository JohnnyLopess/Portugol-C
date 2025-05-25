# Projeto Tradutor Portugol → C

## ⚙️ Ferramentas

### Bison

- Bison é uma ferramenta de geração de analisadores sintáticos (parsers), mantida pelo projeto GNU e sucessora do Yacc (Yet Another Compiler Compiler). Neste projeto, o Bison é utilizado para definir a gramática da linguagem Portugol, permitindo identificar e estruturar corretamente expressões, declarações e comandos de controle de fluxo. A ferramenta gera código C correspondente à estrutura sintática reconhecida, integrando-se ao Flex para compor o analisador completo do compilador.

### Flex

- Flex é uma ferramenta moderna utilizada para gerar **analisadores léxicos** (scanners), sendo o sucessor do tradicional Lex do Unix. Neste projeto, o Flex é responsável por reconhecer os tokens da linguagem Portugol, como palavras-chave, identificadores e números. Ele gera automaticamente o arquivo `lex.yy.c`, que implementa o scanner léxico e integra-se ao Bison para permitir a análise completa do código-fonte durante o processo de compilação.

### GCC e Makefile
- Ferramentas para compilar o código e automatizar o processo de build

## 📅 Organização por Sprints

O desenvolvimento foi dividido em **6 sprints quinzenais**, iniciando em **02/04/2025** e terminando com a entrega final em **27/06/2025**. Utilizamos **issues** no GitHub para organizar as tarefas de cada sprint com critérios claros de aceitação (_definition of done_).

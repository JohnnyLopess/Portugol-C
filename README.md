<!-- Título centralizado -->
<div align="center">
  <h2>Compilador </h2>
</div> 

<!-- Título centralizado -->
<div align="center">
  <h2>🎯 Objetivo </h2>
</div> 

Este projeto tem como objetivo traduzir programas escritos em Portugol para a linguagem C, utilizando as ferramentas Flex e Bison.

<!-- Título centralizado -->
<div align="center">
  <h2>👩🏾‍💻 Funcionalidades </h2>
</div> 

Este projeto oferece as seguintes funcionalidades:

- Tradução de programas em Portugol para C.
- Execução de testes automatizados para validar a tradução.

<!-- Título centralizado -->
<div align="center">
  <h2>🤞 Como executar o projeto </h2>
</div> 

### 1. 🔑 Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas no seu sistema:

- `gcc` (compilador C) - versão 11.4.0
- `flex` (gerador de analisadores léxicos)- versão 2.6.4
- `bison` (gerador de analisadores sintáticos) - versão 3.8.2

### 2. 📑 Compilar o projeto

Para compilar o compilador, execute o comando:

```bash
make
```
Isso irá gerar o executável `compilador`.

### 3. 📂 Traduzir um arquivo da pasta `exemplos`

Para traduzir um arquivo de exemplo da pasta `exemplos`, siga os passos abaixo:

1. Execute o comando:

```bash
make run FILE=exemplos/nome_exemplo.pg
```

2. O compilador irá gerar um arquivo chamado `saida.c` dentro da pasta `build` com o código equivalente em C.

3. Para compilar e executar o código traduzido, use os comandos:
```bash
gcc saida.c -o programa
./programa
```
### 4. 🧪 Executar os testes automatizados

Para executar os testes automatizados, siga os passos abaixo:

1. Execute o comando:
```bash
make test
```

2. O sistema irá:
   - Compilar o compilador se necessário
   - Executar cada arquivo `.pg` da pasta `testes/inputs`
   - Gerar o código C correspondente em `build/test_outputs`
   - Comparar o resultado com o arquivo esperado em `testes/expected`
   - Exibir o resultado:
     - ✅ Indica que o teste passou
     - ❌ Indica que o teste falhou, mostrando as diferenças

### 4.1 🧩 Adicionar novos casos de teste

Para adicionar um novo caso de teste:

1. Crie um arquivo de entrada na pasta `testes/inputs` com extensão `.pg`
   - Exemplo: `testes/inputs/meu_teste.pg`

2. Crie o arquivo com a saída esperada na pasta `testes/expected` com o mesmo nome base e extensão `.expected`
   - Exemplo: `testes/expected/meu_teste.expected`

3. Execute `make test` para verificar se o compilador gera o resultado esperado

**Nota:** O compilador gera os arquivos de saída na pasta `build/saida.c` durante o teste, e esses são copiados para `build/test_outputs/nome_do_teste.c` para verificação.

### 5. 🧹 Limpar arquivos gerados
Para remover os arquivos gerados automaticamente (como `lex.yy.c`, `y.tab.c`, `y.tab.h`, `saida.c`, etc.), execute:
```bash
make clean
```

<div align="center">
  <h2>⚙️ Configurações do projeto </h2>
</div>

O projeto utiliza Flex e Bison para análise léxica e sintática, além de um Makefile para automação das tarefas de compilação e testes.

<div align="center">
  <h2>👩‍💻 Colaboradores </h2>
</div> 
<!-- Foto dos participantes do grupo -->
<center> 
  
  <table style="width: 100%;">
  <tr>
    <td align="center"><a href="https://github.com/jvcostta"><img style="border-radius: 50%;" src="https://github.com/jvcostta.png" width="100px;" alt="Imagem de João"/><br /><sub><b>João Costa</b></sub></a></td>
    <td align="center"><a href="https://github.com/Joao151104"><img style="border-radius: 50%;" src="https://github.com/Joao151104.png" width="100px;" alt="Imagem de João"/><br /><sub><b>João Filipe</b></sub></a></td>
    <td align="center"><a href="https://github.com/JohnnyLopess"><img style="border-radius: 50%;" src="https://github.com/Johnnylopess.png" width="100px;" alt="Imagem de Johnny"/><br /><sub><b>Johnny Lopes</b></sub></a></td>
    <td align="center"><a href="https://github.com/caiolamego"><img style="border-radius: 50%;" src="https://github.com/caiolamego.png" width="100px;" alt="Imagem de caio lamego"/><br /><sub><b>Caio Lamego</b></sub></a></td>
    <td align="center"><a href="https://github.com/MateusPy"><img style="border-radius: 50%;" src="https://github.com/MateusPy.png" width="100px;" alt="Imagem de Mateus Orlando"/><br /><sub><b>Mateus Orlando</b></sub></a></td>
    <td align="center"><a href="https://github.com/Stain19"><img style="border-radius: 50%;" src="https://github.com/Stain19.png" width="100px;" alt="Imagem de Pedro Braga"/><br /><sub><b>Pedro Braga</b></sub></a></td>
  </tr>
</table> 

</center>

<div align="center">
  <h2>📄 Documentação </h2>
</div>

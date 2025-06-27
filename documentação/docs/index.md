# Bem-vindo ao Compilador Portugol-C

Este projeto faz parte da disciplina de **Compiladores 1 (2025/1)**, Ministrada pelo professor Dr. Sergio Freitas na Universidade de Brasília e tem como objetivo desenvolver um compilador, consolidando os conceitos aprendidos ao longo do semestre. A equipe é formada por estudantes dedicados que aplicam a metodologia **Problem Based Learning (PBL)** para integrar teoria e prática.


## 🚀 Sobre o Projeto

Este compilador traduz programas escritos em **Portugol** — com sintaxe inspirada no Portugol Studio — para a linguagem **C**, utilizando as ferramentas **Flex** (para análise léxica) e **Bison** (para análise sintática). 

### ✨ Principais Características

- 🔄 **Tradução completa**: Portugol → C
- 🧪 **32 testes automatizados** garantindo qualidade
- ⚡ **Otimizações integradas**: propagação de constantes e eliminação de código morto
- 📊 **Suporte a vetores**: arrays de todos os tipos
- 🎯 **Análise semântica**: verificação de tipos e escopos
- 🔍 **Relatórios de erro** claros e precisos

### 🛠️ Funcionalidades Implementadas

| Categoria | Funcionalidades |
|-----------|----------------|
| **Tipos de Dados** | `inteiro`, `real`, `caracter`, `logico` |
| **Estruturas** | Vetores unidimensionais, variáveis simples |
| **Controle** | `se/senao`, `enquanto`, `para`, `escolha/caso` |
| **Operadores** | Aritméticos, relacionais, lógicos, bitwise |
| **I/O** | `leia()`, `escreva()` com múltiplos argumentos |
| **Funções** | Declaração, parâmetros, tipos de retorno |


## Nossa Equipe

<center> 
  
  <table style="width: 100%;">
  <tr>
    <td align="center"><a href="https://github.com/jvcostta"><img style="border-radius: 50%;" src="https://github.com/jvcostta.png" width="100px;" alt="Imagem de João"/><br /><sub><b>João Costa</b></sub></a></td>
    <td align="center"><a href="https://github.com/Joao151104"><img style="border-radius: 50%;" src="https://github.com/Joao151104.png" width="100px;" alt="Imagem de João"/><br /><sub><b>João Filipe</b></sub></a></td>
    <td align="center"><a href="https://github.com/JohnnyLopess"><img style="border-radius: 50%;" src="https://github.com/Johnnylopess.png" width="100px;" alt="Imagem de Johnny"/><br /><sub><b>Johnny Lopes</b></sub></a></td>
    <td align="center"><a href="https://github.com/caiolamego"><img style="border-radius: 50%;" src="https://github.com/caiolamego.png" width="100px;" alt="Imagem de Caio Lamego"/><br /><sub><b>Caio Lamego</b></sub></a></td>
    <td align="center"><a href="https://github.com/MateusPy"><img style="border-radius: 50%;" src="https://github.com/MateusPy.png" width="100px;" alt="Imagem de Mateus Orlando"/><br /><sub><b>Mateus Orlando</b></sub></a></td>
    <td align="center"><a href="https://github.com/Stain19"><img style="border-radius: 50%;" src="https://github.com/Stain19.png" width="100px;" alt="Imagem de Pedro Braga"/><br /><sub><b>Pedro Braga</b></sub></a></td>
  </tr>
</table> 

</center>

## 🎯 Começando

### Instalação Rápida

```bash
# Clonar o repositório
git clone https://github.com/JohnnyLopess/Portugol-C.git
cd Portugol-C/portugol_compilador

# Instalar dependências (Ubuntu/Debian)
sudo apt install -y gcc flex bison make

# Compilar o projeto
make

# Executar testes
make test
```

### Primeiro Programa

```portugol
programa {
    funcao inicio() {
        inteiro idade
        idade = 25
        escreva("Minha idade é: ", idade)
    }
}
```

```bash
# Compilar
make run FILE=meu_programa.pg

# Resultado em build/saida.c:
# #include <stdio.h>
# int main() {
#     int idade;
#     idade = 25;
#     printf("Minha idade é: %d\n", idade);
#     return 0;
# }
```

## 📊 Qualidade e Testes

### 🧪 Sistema de Testes Robusto
- **32 casos de teste** automatizados
- **100% de taxa de sucesso**
- **Cobertura completa** das funcionalidades
- **CI/CD integrado** com GitHub Actions

### 📈 Métricas de Qualidade
- ✅ Todos os tipos de dados testados
- ✅ Estruturas de controle validadas  
- ✅ Operadores verificados
- ✅ Vetores completamente suportados
- ✅ Otimizações funcionais

## 🔗 Links Importantes

- � **Repositório**: [GitHub - Portugol-C](https://github.com/JohnnyLopess/Portugol-C)
- 📖 **Documentação Completa**: Navegue pelas seções desta documentação
- 🧪 **Sistema de Testes**: Veja todos os casos de teste implementados
- 🏗️ **Arquitetura**: Entenda como o compilador funciona internamente
---
**🎓 Disciplina**: Compiladores 1 (2025/1)  
**🏫 Universidade**: Universidade de Brasília (UnB)  
**👨‍🏫 Professor**: Dr. Sergio Freitas  
**📚 Metodologia**: Problem Based Learning (PBL)
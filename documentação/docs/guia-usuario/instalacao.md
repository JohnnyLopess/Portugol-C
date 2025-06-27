# Instalação

## Pré-requisitos

Para compilar e executar o Compilador Portugol-C, você precisa ter instalado:

### Ferramentas Obrigatórias

- **GCC** (versão 11.4.0 ou superior)
- **Flex** (versão 2.6.4 ou superior) - Gerador de analisadores léxicos
- **Bison** (versão 3.8.2 ou superior) - Gerador de analisadores sintáticos
- **Make** - Para automatizar o processo de compilação

### Sistema Operacional

O compilador foi testado e funciona em:
- Linux (Ubuntu 20.04+)
- macOS (com Homebrew)
- Windows (com WSL2)

## Instalação no Ubuntu/Debian

```bash
# Atualizar repositórios
sudo apt update

# Instalar dependências
sudo apt install -y gcc flex bison make

# Verificar versões
gcc --version
flex --version
bison --version
make --version
```

## Instalação no macOS

```bash
# Instalar Homebrew (se não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependências
brew install gcc flex bison make

# Verificar versões
gcc --version
flex --version
bison --version
make --version
```

## Instalação no Windows (WSL2)

1. Instalar o WSL2 seguindo a [documentação oficial da Microsoft](https://docs.microsoft.com/pt-br/windows/wsl/install)
2. Escolher uma distribuição Linux (recomendamos Ubuntu)
3. Seguir os passos da instalação no Ubuntu/Debian

## Clonando o Repositório

```bash
# Clonar o repositório
git clone https://github.com/JohnnyLopess/Portugol-C.git

# Entrar no diretório
cd Portugol-C/portugol_compilador
```

## Compilação do Projeto

```bash
# Compilar o compilador
make

# Verificar se a compilação foi bem-sucedida
ls build/
# Deve mostrar: compilador, lex.yy.c, y.tab.c, y.tab.h
```

## Verificação da Instalação

Para verificar se tudo foi instalado corretamente:

```bash
# Executar os testes automatizados
make test

# Se todos os testes passarem, a instalação está correta
```

## Problemas Comuns

### Erro de versão do GCC

```
Erro: Versão do GCC incorreta.
```

**Solução**: Instale o GCC versão 11 ou superior:

```bash
sudo apt install gcc-11
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
```

### Flex ou Bison não encontrado

```
command not found: flex
command not found: bison
```

**Solução**: Instale as ferramentas:

```bash
sudo apt install flex bison
```

### Problemas de permissão

```
Permission denied
```

**Solução**: Verifique as permissões do diretório:

```bash
chmod +x portugol_compilador/
cd portugol_compilador/
```
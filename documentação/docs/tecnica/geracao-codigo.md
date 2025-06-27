# Geração de Código

A geração de código é a fase final do compilador Portugol-C, responsável por transformar a árvore sintática abstrata (AST) em código C equivalente. Este documento descreve o processo de tradução, otimizações implementadas e a estrutura do código gerado.

## Visão Geral

### Processo de Geração
1. **Travessia da AST**: Percorre a árvore sintática em ordem
2. **Tradução de Construtos**: Converte cada nó em código C equivalente
3. **Gerenciamento de Símbolos**: Mapeia identificadores Portugol para C
4. **Otimizações**: Aplica otimizações básicas no código gerado
5. **Formatação**: Produz código C legível e bem formatado

### Arquivos Envolvidos
- `src/main.c`: Controlador principal da geração
- `src/ast.c`: Funções de travessia da AST
- `src/simbolos.c`: Gerenciamento da tabela de símbolos
- `src/tipos.h`: Definições de tipos e mapeamentos

## Mapeamento de Tipos

### Tipos Primitivos

| Portugol | C | Observações |
|----------|---|-------------|
| `inteiro` | `int` | 32 bits com sinal |
| `real` | `float` | Ponto flutuante IEEE 754 |
| `caracter` | `char` | 8 bits ASCII |
| `logico` | `int` | 0 = falso, 1 = verdadeiro |

### Implementação do Mapeamento
```c
// Em tipos.h
typedef enum {
    TIPO_INT = 1,
    TIPO_FLOAT = 2,
    TIPO_CHAR = 3,
    TIPO_BOOL = 4,
    TIPO_VOID = 5,
    TIPO_VETOR = 0x100  // Flag para vetores
} TipoData;

const char* tipo_para_c(int tipo) {
    switch (tipo & ~TIPO_VETOR) {
        case TIPO_INT:   return "int";
        case TIPO_FLOAT: return "float";
        case TIPO_CHAR:  return "char";
        case TIPO_BOOL:  return "int";
        case TIPO_VOID:  return "void";
        default:         return "int";
    }
}
```

### Vetores e Arrays
```c
// Declaração de vetor em Portugol
inteiro numeros[10];

// Código C gerado
int numeros[10];

// Inicialização de vetor
inteiro valores[3] = {1, 2, 3};

// Código C gerado
int valores[3] = {1, 2, 3};
```

## Estrutura do Código Gerado

### Template Básico
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarações de funções
int funcao1(int param1, float param2);
void funcao2();

// Implementações das funções
int funcao1(int param1, float param2) {
    // Corpo da função
}

void funcao2() {
    // Corpo da função
}

// Função principal
int main() {
    inicio();  // Chama a função inicio() do Portugol
    return 0;
}
```

### Funções de Travessia da AST

#### Função Principal
```c
void gerar_codigo(AST_Node* raiz, FILE* saida) {
    if (!raiz) return;
    
    // Cabeçalho
    fprintf(saida, "#include <stdio.h>\n");
    fprintf(saida, "#include <stdlib.h>\n");
    fprintf(saida, "#include <string.h>\n\n");
    
    // Declarações forward
    gerar_declaracoes_forward(raiz->dados.programa.funcoes, saida);
    
    // Implementações das funções
    gerar_funcoes(raiz->dados.programa.funcoes, saida);
    
    // Função main
    fprintf(saida, "\nint main() {\n");
    fprintf(saida, "    inicio();\n");
    fprintf(saida, "    return 0;\n");
    fprintf(saida, "}\n");
}
```

#### Geração de Funções
```c
void gerar_funcoes(AST_Node* funcoes, FILE* saida) {
    AST_Node* atual = funcoes;
    
    while (atual) {
        if (atual->tipo == NO_FUNCAO) {
            // Assinatura da função
            fprintf(saida, "%s %s(", 
                    tipo_para_c(atual->dados.funcao.tipo_retorno),
                    atual->dados.funcao.nome);
            
            // Parâmetros
            gerar_parametros(atual->dados.funcao.parametros, saida);
            fprintf(saida, ") {\n");
            
            // Corpo da função
            gerar_bloco(atual->dados.funcao.corpo, saida, 1);
            
            fprintf(saida, "}\n\n");
        }
        atual = atual->proximo;
    }
}
```

#### Geração de Comandos
```c
void gerar_comando(AST_Node* comando, FILE* saida, int nivel) {
    if (!comando) return;
    
    switch (comando->tipo) {
        case NO_DECLARACAO:
            gerar_declaracao(comando, saida, nivel);
            break;
            
        case NO_ATRIBUICAO:
            gerar_atribuicao(comando, saida, nivel);
            break;
            
        case NO_SE:
            gerar_se(comando, saida, nivel);
            break;
            
        case NO_PARA:
            gerar_para(comando, saida, nivel);
            break;
            
        case NO_ENQUANTO:
            gerar_enquanto(comando, saida, nivel);
            break;
            
        case NO_ESCOLHA:
            gerar_escolha(comando, saida, nivel);
            break;
            
        case NO_RETORNE:
            gerar_retorne(comando, saida, nivel);
            break;
            
        case NO_CHAMADA_FUNCAO:
            gerar_chamada_funcao(comando, saida, nivel);
            break;
            
        default:
            fprintf(stderr, "Comando não implementado: %d\n", comando->tipo);
    }
}
```

## Tradução de Construtos

### Estruturas de Controle

#### Comando Se-Senão
```c
void gerar_se(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    fprintf(saida, "if (");
    gerar_expressao(no->dados.se.condicao, saida);
    fprintf(saida, ") {\n");
    
    gerar_comando(no->dados.se.entao, saida, nivel + 1);
    
    identar(saida, nivel);
    fprintf(saida, "}");
    
    if (no->dados.se.senao) {
        fprintf(saida, " else {\n");
        gerar_comando(no->dados.se.senao, saida, nivel + 1);
        identar(saida, nivel);
        fprintf(saida, "}");
    }
    
    fprintf(saida, "\n");
}
```

**Exemplo de Tradução:**
```portugol
se (idade >= 18) {
    escreva("Maior de idade\n");
} senao {
    escreva("Menor de idade\n");
}
```

**Código C Gerado:**
```c
if (idade >= 18) {
    printf("Maior de idade\n");
} else {
    printf("Menor de idade\n");
}
```

#### Loop Para
```c
void gerar_para(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    fprintf(saida, "for (");
    
    // Inicialização
    gerar_comando_inline(no->dados.para.inicializacao, saida);
    fprintf(saida, "; ");
    
    // Condição
    gerar_expressao(no->dados.para.condicao, saida);
    fprintf(saida, "; ");
    
    // Incremento
    gerar_comando_inline(no->dados.para.incremento, saida);
    fprintf(saida, ") {\n");
    
    // Corpo
    gerar_comando(no->dados.para.corpo, saida, nivel + 1);
    
    identar(saida, nivel);
    fprintf(saida, "}\n");
}
```

**Exemplo de Tradução:**
```portugol
para (inteiro i = 0; i < 10; i++) {
    escreva(i, "\n");
}
```

**Código C Gerado:**
```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

#### Loop Enquanto
```c
void gerar_enquanto(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    fprintf(saida, "while (");
    gerar_expressao(no->dados.enquanto.condicao, saida);
    fprintf(saida, ") {\n");
    
    gerar_comando(no->dados.enquanto.corpo, saida, nivel + 1);
    
    identar(saida, nivel);
    fprintf(saida, "}\n");
}
```

#### Switch-Case
```c
void gerar_escolha(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    fprintf(saida, "switch (");
    gerar_expressao(no->dados.escolha.expressao, saida);
    fprintf(saida, ") {\n");
    
    // Gerar casos
    AST_Node* caso = no->dados.escolha.casos;
    while (caso) {
        if (caso->tipo == NO_CASO) {
            identar(saida, nivel + 1);
            fprintf(saida, "case ");
            gerar_expressao(caso->dados.caso.valor, saida);
            fprintf(saida, ":\n");
            
            gerar_comando(caso->dados.caso.comandos, saida, nivel + 2);
            
            identar(saida, nivel + 2);
            fprintf(saida, "break;\n");
        } else if (caso->tipo == NO_PADRAO) {
            identar(saida, nivel + 1);
            fprintf(saida, "default:\n");
            gerar_comando(caso->dados.padrao.comandos, saida, nivel + 2);
            identar(saida, nivel + 2);
            fprintf(saida, "break;\n");
        }
        caso = caso->proximo;
    }
    
    identar(saida, nivel);
    fprintf(saida, "}\n");
}
```

### Expressões

#### Expressões Aritméticas
```c
void gerar_expressao(AST_Node* no, FILE* saida) {
    if (!no) return;
    
    switch (no->tipo) {
        case NO_LITERAL_INT:
            fprintf(saida, "%d", no->dados.literal.valor.intval);
            break;
            
        case NO_LITERAL_FLOAT:
            fprintf(saida, "%.3f", no->dados.literal.valor.realval);
            break;
            
        case NO_LITERAL_CHAR:
            fprintf(saida, "'%c'", no->dados.literal.valor.charval);
            break;
            
        case NO_LITERAL_BOOL:
            fprintf(saida, "%d", no->dados.literal.valor.boolval);
            break;
            
        case NO_IDENTIFICADOR:
            fprintf(saida, "%s", no->dados.identificador.nome);
            break;
            
        case NO_OPERACAO_BINARIA:
            gerar_operacao_binaria(no, saida);
            break;
            
        case NO_OPERACAO_UNARIA:
            gerar_operacao_unaria(no, saida);
            break;
            
        case NO_ACESSO_VETOR:
            gerar_acesso_vetor(no, saida);
            break;
            
        case NO_CHAMADA_FUNCAO:
            gerar_chamada_funcao_expr(no, saida);
            break;
    }
}
```

#### Operações Binárias
```c
void gerar_operacao_binaria(AST_Node* no, FILE* saida) {
    int operador = no->dados.operacao_binaria.operador;
    
    // Parênteses para preservar precedência
    int precisa_parenteses = operador_precisa_parenteses(operador);
    
    if (precisa_parenteses) fprintf(saida, "(");
    
    gerar_expressao(no->dados.operacao_binaria.esquerda, saida);
    
    switch (operador) {
        case OP_SOMA:           fprintf(saida, " + "); break;
        case OP_SUBTRACAO:      fprintf(saida, " - "); break;
        case OP_MULTIPLICACAO:  fprintf(saida, " * "); break;
        case OP_DIVISAO:        fprintf(saida, " / "); break;
        case OP_MODULO:         fprintf(saida, " %% "); break;
        case OP_IGUAL:          fprintf(saida, " == "); break;
        case OP_DIFERENTE:      fprintf(saida, " != "); break;
        case OP_MENOR:          fprintf(saida, " < "); break;
        case OP_MENOR_IGUAL:    fprintf(saida, " <= "); break;
        case OP_MAIOR:          fprintf(saida, " > "); break;
        case OP_MAIOR_IGUAL:    fprintf(saida, " >= "); break;
        case OP_E_LOGICO:       fprintf(saida, " && "); break;
        case OP_OU_LOGICO:      fprintf(saida, " || "); break;
        case OP_E_BITWISE:      fprintf(saida, " & "); break;
        case OP_OU_BITWISE:     fprintf(saida, " | "); break;
        case OP_XOR_BITWISE:    fprintf(saida, " ^ "); break;
        case OP_DESLOC_ESQ:     fprintf(saida, " << "); break;
        case OP_DESLOC_DIR:     fprintf(saida, " >> "); break;
    }
    
    gerar_expressao(no->dados.operacao_binaria.direita, saida);
    
    if (precisa_parenteses) fprintf(saida, ")");
}
```

### Entrada e Saída

#### Comando Escreva
```c
void gerar_escreva(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    fprintf(saida, "printf(");
    
    AST_Node* arg = no->dados.escreva.argumentos;
    int primeiro = 1;
    
    while (arg) {
        if (!primeiro) {
            fprintf(saida, ", ");
        }
        
        if (arg->tipo == NO_LITERAL_STRING) {
            fprintf(saida, "\"%s\"", arg->dados.literal.valor.strval);
        } else {
            // Determinar formato baseado no tipo
            int tipo = obter_tipo_expressao(arg);
            switch (tipo) {
                case TIPO_INT:
                    fprintf(saida, "\"%%d\", ");
                    break;
                case TIPO_FLOAT:
                    fprintf(saida, "\"%%f\", ");
                    break;
                case TIPO_CHAR:
                    fprintf(saida, "\"%%c\", ");
                    break;
                case TIPO_BOOL:
                    fprintf(saida, "\"%%d\", ");
                    break;
            }
            gerar_expressao(arg, saida);
        }
        
        primeiro = 0;
        arg = arg->proximo;
    }
    
    fprintf(saida, ");\n");
}
```

**Exemplo de Tradução:**
```portugol
escreva("Idade: ", idade, "\n");
```

**Código C Gerado:**
```c
printf("Idade: %d\n", idade);
```

#### Comando Leia
```c
void gerar_leia(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    
    AST_Node* var = no->dados.leia.variavel;
    int tipo = obter_tipo_variavel(var->dados.identificador.nome);
    
    switch (tipo) {
        case TIPO_INT:
            fprintf(saida, "scanf(\"%%d\", &%s);\n", var->dados.identificador.nome);
            break;
        case TIPO_FLOAT:
            fprintf(saida, "scanf(\"%%f\", &%s);\n", var->dados.identificador.nome);
            break;
        case TIPO_CHAR:
            fprintf(saida, "scanf(\" %%c\", &%s);\n", var->dados.identificador.nome);
            break;
    }
}
```

## Otimizações Implementadas

### 1. Propagação de Constantes

```c
AST_Node* otimizar_propagacao_contantes(AST_Node* no) {
    if (!no) return NULL;
    
    if (no->tipo == NO_OPERACAO_BINARIA) {
        AST_Node* esq = otimizar_propagacao_contantes(no->dados.operacao_binaria.esquerda);
        AST_Node* dir = otimizar_propagacao_contantes(no->dados.operacao_binaria.direita);
        
        // Se ambos são literais, calcular em tempo de compilação
        if (esq->tipo == NO_LITERAL_INT && dir->tipo == NO_LITERAL_INT) {
            int resultado = calcular_operacao_constante(
                no->dados.operacao_binaria.operador,
                esq->dados.literal.valor.intval,
                dir->dados.literal.valor.intval
            );
            
            // Substituir pela constante calculada
            liberar_ast(no);
            return criar_no_literal_int(resultado);
        }
        
        no->dados.operacao_binaria.esquerda = esq;
        no->dados.operacao_binaria.direita = dir;
    }
    
    return no;
}
```

**Exemplo:**
```portugol
// Código original
inteiro x = 5 + 3 * 2;

// Após otimização (em tempo de compilação)
inteiro x = 11;
```

### 2. Eliminação de Código Morto

```c
AST_Node* otimizar_codigo_morto(AST_Node* no) {
    if (!no) return NULL;
    
    if (no->tipo == NO_SE) {
        AST_Node* condicao = no->dados.se.condicao;
        
        // Se condição é literal constante
        if (condicao->tipo == NO_LITERAL_BOOL) {
            if (condicao->dados.literal.valor.boolval) {
                // Condição sempre verdadeira - manter apenas o 'então'
                return no->dados.se.entao;
            } else {
                // Condição sempre falsa - manter apenas o 'senão'
                return no->dados.se.senao;
            }
        }
    }
    
    return no;
}
```

**Exemplo:**
```portugol
// Código original
se (verdadeiro) {
    escreva("Sempre executado\n");
} senao {
    escreva("Nunca executado\n");
}

// Após otimização
escreva("Sempre executado\n");
```

### 3. Simplificação Algébrica

```c
AST_Node* otimizar_algebra(AST_Node* no) {
    if (!no || no->tipo != NO_OPERACAO_BINARIA) return no;
    
    int op = no->dados.operacao_binaria.operador;
    AST_Node* esq = no->dados.operacao_binaria.esquerda;
    AST_Node* dir = no->dados.operacao_binaria.direita;
    
    // x + 0 = x
    if (op == OP_SOMA && dir->tipo == NO_LITERAL_INT && 
        dir->dados.literal.valor.intval == 0) {
        return esq;
    }
    
    // x * 1 = x
    if (op == OP_MULTIPLICACAO && dir->tipo == NO_LITERAL_INT && 
        dir->dados.literal.valor.intval == 1) {
        return esq;
    }
    
    // x * 0 = 0
    if (op == OP_MULTIPLICACAO && dir->tipo == NO_LITERAL_INT && 
        dir->dados.literal.valor.intval == 0) {
        return criar_no_literal_int(0);
    }
    
    return no;
}
```

## Formatação e Legibilidade

### Identação
```c
void identar(FILE* saida, int nivel) {
    for (int i = 0; i < nivel; i++) {
        fprintf(saida, "    ");  // 4 espaços por nível
    }
}
```

### Comentários no Código Gerado
```c
void gerar_comentario_funcao(AST_Node* funcao, FILE* saida) {
    fprintf(saida, "/* Função: %s */\n", funcao->dados.funcao.nome);
    fprintf(saida, "/* Traduzida do Portugol */\n");
}
```

### Formatação de Declarações
```c
void gerar_declaracao(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    
    int tipo = no->dados.declaracao.tipo;
    const char* nome = no->dados.declaracao.nome;
    
    if (tipo & TIPO_VETOR) {
        fprintf(saida, "%s %s[%d]", 
                tipo_para_c(tipo), nome, no->dados.declaracao.tamanho);
        
        if (no->dados.declaracao.inicializacao) {
            fprintf(saida, " = ");
            gerar_inicializacao_vetor(no->dados.declaracao.inicializacao, saida);
        }
    } else {
        fprintf(saida, "%s %s", tipo_para_c(tipo), nome);
        
        if (no->dados.declaracao.valor_inicial) {
            fprintf(saida, " = ");
            gerar_expressao(no->dados.declaracao.valor_inicial, saida);
        }
    }
    
    fprintf(saida, ";\n");
}
```

## Tratamento de Erros

### Verificação de Tipos
```c
void verificar_tipos_operacao(AST_Node* no) {
    if (no->tipo != NO_OPERACAO_BINARIA) return;
    
    int tipo_esq = obter_tipo_expressao(no->dados.operacao_binaria.esquerda);
    int tipo_dir = obter_tipo_expressao(no->dados.operacao_binaria.direita);
    int operador = no->dados.operacao_binaria.operador;
    
    if (!tipos_compativeis(tipo_esq, tipo_dir, operador)) {
        erro_geracao("Tipos incompatíveis na operação %s: %s e %s",
                    nome_operador(operador),
                    nome_tipo(tipo_esq),
                    nome_tipo(tipo_dir));
    }
}
```

### Função de Erro
```c
void erro_geracao(const char* formato, ...) {
    va_list args;
    va_start(args, formato);
    
    fprintf(stderr, "Erro na geração de código: ");
    vfprintf(stderr, formato, args);
    fprintf(stderr, "\n");
    
    va_end(args);
    exit(1);
}
```

## Exemplo Completo

### Código Portugol de Entrada
```portugol
programa {
    inteiro fatorial(inteiro n) {
        se (n <= 1) {
            retorne 1;
        } senao {
            retorne n * fatorial(n - 1);
        }
    }
    
    funcao inicio() {
        inteiro numero;
        escreva("Digite um número: ");
        leia(numero);
        
        inteiro resultado = fatorial(numero);
        escreva("Fatorial de ", numero, " é ", resultado, "\n");
    }
}
```

### Código C Gerado
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Declarações de funções */
int fatorial(int n);
void inicio();

/* Função: fatorial */
/* Traduzida do Portugol */
int fatorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * fatorial(n - 1);
    }
}

/* Função: inicio */
/* Traduzida do Portugol */
void inicio() {
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    
    int resultado = fatorial(numero);
    printf("Fatorial de %d é %d\n", numero, resultado);
}

int main() {
    inicio();
    return 0;
}
```

## Performance e Qualidade

### Métricas de Qualidade
```c
typedef struct {
    int linhas_geradas;
    int funcoes_geradas;
    int otimizacoes_aplicadas;
    double tempo_geracao;
    size_t memoria_usada;
} MetricasGeracao;

void medir_geracao(AST_Node* raiz, MetricasGeracao* metricas) {
    clock_t inicio = clock();
    
    // Processo de geração...
    
    metricas->tempo_geracao = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    metricas->linhas_geradas = contar_linhas_geradas();
    metricas->funcoes_geradas = contar_funcoes_geradas();
    metricas->otimizacoes_aplicadas = contador_otimizacoes;
}
```

### Validação do Código Gerado
```c
int validar_codigo_gerado(const char* arquivo_c) {
    char comando[256];
    sprintf(comando, "gcc -fsyntax-only %s 2>/dev/null", arquivo_c);
    
    int resultado = system(comando);
    return (resultado == 0);
}
```

## Extensibilidade

### Adicionando Novos Construtos
```c
// Template para novos tipos de nó
void gerar_novo_comando(AST_Node* no, FILE* saida, int nivel) {
    identar(saida, nivel);
    
    // Lógica específica do comando
    switch (no->dados.novo_comando.subtipo) {
        case SUBTIPO_A:
            // Implementação específica
            break;
        case SUBTIPO_B:
            // Implementação específica
            break;
    }
    
    fprintf(saida, ";\n");
}

// Registrar na função principal
void gerar_comando(AST_Node* comando, FILE* saida, int nivel) {
    switch (comando->tipo) {
        // ... casos existentes ...
        case NO_NOVO_COMANDO:
            gerar_novo_comando(comando, saida, nivel);
            break;
    }
}
```

A geração de código é responsável por produzir código C limpo, eficiente e correto a partir da AST do Portugol. As otimizações implementadas melhoram a qualidade do código gerado, enquanto a estrutura modular permite fácil extensão para novas funcionalidades.

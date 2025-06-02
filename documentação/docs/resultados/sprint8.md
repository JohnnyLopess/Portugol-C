# 📦 Sprint 8 — Recursos Avançados do Portugol (18/05 - 24/05)

| Matrícula | Nome                                      | Nick no GitHub |                                                      📸                                                       |
| :-------: | ----------------------------------------- | -------------- | :----------------------------------------------------------------------------------------------------------: |
| x |  x                 | x       |  [](https://github.com/)   |


## Objetivo:
- Implementar recursos `senaose`, `escolha`, `caso`, `fimcaso`, gerando código C válido com blocos `switch/case `.


---

## 🧪 Funcionalidades Concluídas

### 🧩 Palavras-chave adicionadas
- `senaose`
- `escolha`
- `caso`
- `fimcaso`

## 🚀 Como testar as novas funcionalidades ?

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

---

### 🧹 Limpando arquivos gerados

Caso necessário, você pode executar o comando abaixo para remover todos os arquivos gerados automaticamente (como `lex.yy.c`, `y.tab.c`, `y.tab.h`, `saida.c`, etc.):

```bash
make clean
```
---


## ✅ Critérios de aceitação

| Critério | Descrição | Status |
|---------|-----------|--------|
| 🔤 **Testes** | Implementar casos de testes para cada um dos recursos | ✅ |
| 🔤 **Testes2** | Todos testes devem estar funcionando | ✅ |


---

## 📁 Arquivos modificados

- `lex.l`: ..

---

## 🔚 Conclusão

A Sprint 8 foi **concluída com sucesso**, consolidando a implementação dos recursos `senaose`, `escolha`, `caso` e `fimcaso`, com a geração de código C equivalente utilizando estruturas `switch/case`, ampliando significativamente o suporte a comandos condicionais no compilador Portugol-C.

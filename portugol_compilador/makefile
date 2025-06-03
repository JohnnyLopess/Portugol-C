CC = gcc
LEX = flex
YACC = bison
SRC_DIR = src
BUILD_DIR = build
EXPECTED_GCC_VERSION_PREFIX = 11

all: check_gcc_version $(BUILD_DIR)/compilador

.PHONY: all clean run test check_gcc_version

check_gcc_version:
	@echo "Verificando versão do GCC..."
	@GCC_PATH=$$(command -v $(CC)); \
	if [ -z "$$GCC_PATH" ]; then \
	    echo "Erro: Compilador '$(CC)' não encontrado no PATH."; \
	    echo "Por favor, instale o GCC com versão que comece com '$(EXPECTED_GCC_VERSION_PREFIX)'."; \
	    exit 1; \
	fi; \
	CURRENT_GCC_DUMPVERSION=$$($(CC) -dumpversion 2>/dev/null); \
	if [ -z "$$CURRENT_GCC_DUMPVERSION" ]; then \
	    echo "Erro: Não foi possível obter a versão de '$(CC)' usando '-dumpversion'."; \
	    echo "Verifique se '$(CC)' é um compilador GCC válido."; \
	    exit 1; \
	fi;	\
	if ! echo "$$CURRENT_GCC_DUMPVERSION" | grep -q -E "^$(EXPECTED_GCC_VERSION_PREFIX)"; then \
		echo "Erro: Versão do GCC incorreta."; \
	    echo "Esperado: um prefixo que corresponda a '$(EXPECTED_GCC_VERSION_PREFIX)'. Encontrado: '$$CURRENT_GCC_DUMPVERSION'."; \
	    echo "Por favor, certifique-se de que '$(CC)' no seu PATH é a versão correta ou ajuste EXPECTED_GCC_VERSION_PREFIX no Makefile."; \
	    exit 1; \
	fi

$(BUILD_DIR)/compilador: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/y.tab.c $(SRC_DIR)/main.c
	$(CC) -Isrc -o $@ $^ $(SRC_DIR)/ast.c $(SRC_DIR)/simbolos.c

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lex.l
	$(LEX) -o $@ $<

$(BUILD_DIR)/y.tab.c $(BUILD_DIR)/y.tab.h: $(SRC_DIR)/yacc.y
	$(YACC) -d -o $(BUILD_DIR)/y.tab.c $<

run: all
	@if [ -z "$(FILE)" ]; then \
		echo "Erro: Você deve especificar o arquivo com FILE=<caminho_para_o_arquivo>."; \
		exit 1; \
	fi
	cd $(BUILD_DIR) && ./compilador < ../$(FILE)

clean:
	rm -rf $(BUILD_DIR)/* ./compilador saida.c

test:
	bash testes/run_tests.sh
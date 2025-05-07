CC = gcc
LEX = flex
YACC = bison
SRC_DIR = src
BUILD_DIR = build

all: $(BUILD_DIR)/compilador

$(BUILD_DIR)/compilador: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/y.tab.c $(SRC_DIR)/main.c
	$(CC) -o $@ $^

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lex.l
	$(LEX) -o $@ $<

$(BUILD_DIR)/y.tab.c $(BUILD_DIR)/y.tab.h: $(SRC_DIR)/yacc.y
	$(YACC) -d -o $(BUILD_DIR)/y.tab.c $<

run: all
	@if [ -z "$(FILE)" ]; then \
		echo "Erro: Você deve especificar o arquivo com FILE=<nome_do_arquivo>."; \
		echo "Exemplo: make run FILE=exemplo5.pg"; \
		exit 1; \
	fi
	./build/compilador < exemplos/$(FILE)
	mv saida.c $(BUILD_DIR)/saida.c

clean:
	rm -rf $(BUILD_DIR)/* ./compilador saida.c

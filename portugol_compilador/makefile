all: compilador

compilador: lex.yy.c y.tab.c main.c
	gcc -o compilador y.tab.c lex.yy.c main.c -lfl

lex.yy.c: lex.l
	flex lex.l

y.tab.c: yacc.y
	bison -dy yacc.y

clean:
	rm -f compilador lex.yy.c y.tab.c y.tab.h

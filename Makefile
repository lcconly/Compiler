parser:syntax.tab.c lex.yy.c syntax.tab.h main.c Node.h Node.c
	gcc  syntax.tab.c main.c Node.c -lfl -ly -o parser

syntax.tab.h syntax.tab.c:syntax.y
	bison -d syntax.y

lex.yy.c:lexical.l
	flex lexical.l

.PHONY:run clean
run:parser
	./parser test.c

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c parser

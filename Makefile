# 编译目标：目录下的所有.c和.h文件
CFILES = $(shell find src/ -name "*.c")
HFILES = $(shell find include/ -name "*.h")

syntax.tab.h syntax.tab.c:syntax.y
	bison -d syntax.y

lex.yy.c:lexical.l
	flex lexical.l

parser:$(CFILES) $(HFILES) syntax.tab.c syntax.tab.h lex.yy.c
	gcc $(CFILES) syntax.tab.c -lfl -ly -o parser

.PHONY:run clean
run:parser
	./parser test.cmm

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c parser

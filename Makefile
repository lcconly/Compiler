# 编译目标：目录下的所有.c和.h文件
CFILES = $(shell find src/ -name "*.c")
HFILES = $(shell find include/ -name "*.h")

parser:$(CFILES) $(HFILES) syntax.tab.c syntax.tab.h lex.yy.c
	gcc $(CFILES) syntax.tab.c -g -lfl -ly -o parser

syntax.tab.h syntax.tab.c:syntax.y
	bison -d syntax.y

lex.yy.c:lexical.l
	flex lexical.l

.PHONY:run clean coredump
run:parser
	./parser test.cmm out.ir
coredump:
	gdb ./parser ./core

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c parser core *.*~ */*.*~ *.ir

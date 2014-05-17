#ifndef __HSAH_TABLE_H__
#define __HSAH_TABLE_H__
/*************************************************************************
	> File Name: hash_table.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Wed 09 Apr 2014 08:21:08 PM CST
 ************************************************************************/
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#define MAXHARSHSIZE 16384
typedef struct Type_ Type;
typedef struct FieldList_ FieldList;
struct Type_{
    enum{basic,array,structure} kind;
    union{
        int basic;
        struct{Type *elem;int size;}array;
        FieldList *structure;
    }u;
};
typedef struct Operand_* Operand; 
struct Operand_ {
	enum { VARIABLE,CONSTANT,TEMP_ADDRESS,VAR_ADDRESS,TEMP,LABEL,VAR_MEMORY,TEMP_MEMORY } kind; 
	union {
		int var_no;
		int value; 
		int lable_no;
		int temp_no;
		//int relop;//0:> 1:< 2:>= 3:<= 4:== 5:!=
		//...
	} u; 
};
struct FieldList_{
    char* name;
    Type *type;
	Operand intercode;
	FieldList *variable;
    FieldList *tail;
};

/*hash_pjw*/
unsigned int hash_pjw(char *name);
/*insert node to the list*/
bool insert(FieldList *node,FieldList **list);
/*fetch the node from the list*/
FieldList *fetch(char* name,FieldList **list);
/*print the whole list*/
void show_hash_table(FieldList **list); 
#endif 

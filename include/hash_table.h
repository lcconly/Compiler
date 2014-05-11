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
#include"IR.h"
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
struct FieldList_{
    char* name;
    Type *type;
	struct Operand_ intercode;
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

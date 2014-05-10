#ifndef __IR_H__
#define __IR_H__
/*************************************************************************
	> File Name: IR.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sat 10 May 2014 08:16:17 PM CST
 ************************************************************************/

#include"semantic_analysis.h"
#define DATASIZE 10
typedef struct Operand_* Operand; 
struct Operand_ {
	enum { VARIABLE,CONSTANT,TEMP_ADDRESS,VAR_ADDRESS,TEMP,LABLE,VAR_MEMORY,TEMP_MEMORY } kind; 
	union {
		int var_no;
		int value; 
		int lable_no;
		int temp_no;
		//int relop;//0:> 1:< 2:>= 3:<= 4:== 5:!=
		//...
	} u; 
};
struct InterCode {
	enum { ASSIGN,ADD,SUB,MUL,DIV,GOTO,IF,RETURN,DEC,ARG,CALL,PARAM,READ,WRITE} kind; 
	union {
		struct {
			Operand right, left;
		} assign;
		struct { 
			Operand result, op1, op2;  
		} binop; 
        struct {
            char *relop;
            Operand op1,op2,lable;
        } if_type;
        struct{
            Operand returnop;
            char *name;
        } call_fun;
        struct{
            Operand op;
            int size;
        }array;
        Operand op;
		char *name;
        //...
	} u; 
};
struct InterCodes{
    struct InterCode code;
    struct InterCodes *prev,*next;
};
struct InterCodes *ir_head=NULL;
int var_num=0;
int temp_num=0;
int lable_num=0;
/*打印中间代码到文件*/
void printCodeToFile(char *filename);
/*根据Operand输出中间代码的符号*/
char* printOperand(Operand op);
#endif

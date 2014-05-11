#ifndef __IR_H__
#define __IR_H__
/*************************************************************************
	> File Name: IR.h
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sat 10 May 2014 08:16:17 PM CST
 ************************************************************************/

#include"semantic_analysis.h"
#include"list.h"
#include<stdarg.h>
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
	enum { ASSIGN_IR,ADD_IR,SUB_IR,MUL_IR,DIV_IR,GOTO_IR,IF_IR,RETURN_IR,DEC_IR,ARG_IR,CALL_IR,PARAM_IR,READ_IR,WRITE_IR} kind; 
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
    ListHead queue;
};
ListHead ir_head;
int var_num=0;
int temp_num=0;
int lable_num=0;
/*打印中间代码到文件*/
void printCodeToFile(char *filename);
/*根据Operand输出中间代码的符号*/
char* printOperand(Operand op);
/*从尾部插入多个internodes*/
void insertCodes(int n, ...);
/*赋值operand*/
Operand initOperand(int kind,int data);
/*产生assign中间代码*/
struct InterCodes* gen_assign(int kind,Operand right,Operand left);
/*产生Binop中间代码*/
struct InterCodes* gen_binop(int kind,Operand result,Operand op1,Operand op2);
/*产生if_type中间代码*/
struct InterCodes* gen_iftype(int kind,char* relop,Operand result,Operand op1,Operand op2,Operand lable);
/*产生Callfun中间代码*/
struct InterCodes* gen_callfun(int kind,Operand returnop,char* name);
/*产生array中间代码*/
struct InterCodes* gen_array(int kind,Operand op,int size);
/*产生ID中间代码*/
struct InterCodes* gen_id(int kind,char *name);
/*产生var中间代码*/
struct InterCodes* gen_var(int kind,Operand op);
/*查找符号表的中间代码*/
struct InterCodes* gen_var(int kind,Operand op);
/*从符号表中获取中间代码*/
Operand lookup(FieldList** list,char *name);
#endif

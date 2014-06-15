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
#define DATASIZE 100
/*typedef struct Operand_* Operand; 
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
};*/
struct InterCode {
	enum { ASSIGN_IR,ADD_IR,SUB_IR,MUL_IR,DIV_IR,FUNC_IR,GOTO_IR,IF_IR,RETURN_IR,DEC_IR,ARG_IR,CALL_IR,PARAM_IR,READ_IR,WRITE_IR,LABEL_IR} kind; 
	union {
		struct {
			Operand right, left;//!!!!后面左右用翻了！！！！！！！
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
static int var_num=0;
static int temp_num=0;
static int lable_num=0;
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
struct InterCodes* gen_iftype(int kind,char* relop,Operand op1,Operand op2,Operand lable);
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
/*产生立即数的operand*/
Operand get_value(int data);
/*产生零时变量的operand*/
Operand new_temp(int kind);
/*产生变量的operand*/
Operand new_variable(int kind);
/*产生lable的operand*/
Operand new_lable();
/*加入read和write函数*/
void add_func_read_and_write();
/*获取结构体内部偏移*/
//int getOffset(FieldList *field,char *name);
/*获取数组内部偏移*/
int getOffset(Type *type,int tag);
/*翻译exp*/
void translate_Exp(struct TreeNode* root,Operand op);
/*翻译逻辑表达*/
void translate_Cond(struct TreeNode* root,Operand lable1,Operand lable2);
/*翻译stmt*/
void translate_Stmt(struct TreeNode* root);
/*插入中间代码到符号表*/
void inser_field_code(FieldList** list,char *name,Operand op);
/*遍历args的子树*/
FieldList* translate_args(struct TreeNode *root,FieldList *args);
/*从根部翻译*/
void translate(struct TreeNode* root);
/*翻译fundec*/
void translate_fundec(struct TreeNode *root);
/*获取数组大小*/
int getArraySize(Type *type);
/*翻译declist*/
void translate_declist(struct TreeNode *root);
/*打印中间代码到屏幕*/
void printCodeToTerminal(struct InterCodes* temp);
/*单链表反转*/
FieldList *listreverse(FieldList *pHead)  ;
/*判断operand相等*/
bool charge_op_equal(Operand op1,Operand op2);
/*优化死代码*/
void optimize_dead_code();
/*优化立即数代码*/
void optimize_constant_code();
/*优化立即数二元运算代码*/
void optimize_constant_op_code();
/*优化变量二进制运算代码*/
void optimize_binop_code();
/*优化memory代码*/
//void optimize_memory_code();
/*优化*/
void optimize();
#endif

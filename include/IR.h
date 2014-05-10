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
typedef struct Operand_* Operand; 
struct Operand_ {
	enum { VARIABLE,CONSTANT,TEMP_ADDRESS,VAR_ADDRESS,TEMP,LABLE,VAR_MEMORY,TEMP_MEMORY } kind; 
	union {
		int var_no;
		int value; 
		int lable_no;
		int temp_no;
		int relop;//0:> 1:< 2:>= 3:<= 4:== 5:!=
		//...
	} u; 
};
struct InterCode {
	enum { ASSIGN, ADD, SUB, MUL, ...  } kind; 
	union {
		struct {
			Operand right, left;
		} assign;
		struct { 
			Operand result, op1, op2;  
		} binop; 
		//...
	} u; 
}
#endif

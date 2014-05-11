/*************************************************************************
	> File Name: IR_translate.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sun 11 May 2014 01:49:13 PM CST
 ************************************************************************/

#include"IR.h"
/*从尾部插入多个internodes*/
void insertCodes(int n, ...){
    va_list codelist;
    va_start(codelist,n);
    struct InterCodes* code_temp;
    int i;
    for(i=0;i<n;i++){
        code_temp=va_arg(codelist,struct InterCodes*);
        if(code_temp==NULL){
            printf("insertCodes a NULL code!!!\n");
            continue;
        }
		list_add_after(&ir_head,&code_temp->queue);
	} 
    va_end(codelist);
}

/*赋值operand*/
Operand initOperand(int kind,int data){
	Operand op=(Operand)malloc(sizeof(struct Operand_));
	op->kind=kind;
	switch(kind){	
		case VARIABLE:
			(op->u).var_no=data;
			break;
		case CONSTANT:
			(op->u).value=data;
			break;
		case TEMP_ADDRESS:
			(op->u).temp_no=data;
			break;
		case VAR_ADDRESS:
			(op->u).var_no=data;
			break;
		case TEMP:
			(op->u).temp_no=data;
			break;
		case LABLE:
			(op->u).lable_no=data;
			break;
		case VAR_MEMORY:
			(op->u).var_no=data;
			break;
		case TEMP_MEMORY:
			(op->u).temp_no=data;
			break;
		default:
			printf("Operand kind error!!!\n");
			break;
	}
}

/*产生assign中间代码*/
struct InterCodes* gen_assign(int kind,Operand right,Operand left){
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.assign.right=right;
	(temp->code).u.assign.left=left;
	return temp;
}

/*产生Binop中间代码*/
struct InterCodes* gen_binop(int kind,Operand result,Operand op1,Operand op2){
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.binop.result=result;
	(temp->code).u.binop.op1=op1;
	(temp->code).u.binop.op2=op2;
	return temp;
}

/*产生if_type中间代码*/
struct InterCodes* gen_iftype(int kind,char* relop,Operand result,Operand op1,Operand op2,Operand lable){
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	strcpy((temp->code).u.if_type.relop,relop);
	(temp->code).u.if_type.op1=op1;
	(temp->code).u.if_type.op2=op2;
	(temp->code).u.if_type.lable=lable;		
	return temp;
}

/*产生Callfun中间代码*/
struct InterCodes*  gen_callfun(int kind,Operand returnop,char* name){	
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.call_fun.returnop=returnop;
	strcpy((temp->code).u.call_fun.name,name);	
	return temp;
}

/*产生array中间代码*/
struct InterCodes* gen_array(int kind,Operand op,int size){	
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.array.op=op;
	(temp->code).u.array.size=size;		
	return temp;
}

/*产生ID中间代码*/
struct InterCodes* gen_id(int kind,char *name){	
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	strcpy((temp->code).u.name,name);	
	return temp;
}

/*产生var中间代码*/
struct InterCodes* gen_var(int kind,Operand op){
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.op=op;	
	return temp;
}

/*从符号表中获取中间代码*/
Operand lookup(FieldList** list,char *name){	
	unsigned int index=hash_pjw(name);
	FieldList *p;
	p=list[index];
	while(p!=NULL){
		if(!strcmp(p->name,name)){
			return p->intercode;
		}
		p=p->tail;
	}
	return NULL;
}

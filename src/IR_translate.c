/*************************************************************************
	> File Name: IR_translate.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sun 11 May 2014 01:49:13 PM CST
 ************************************************************************/
#include"../include/IR.h"
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
/*从符号表中获取中间代码*/
void inser_field_code(FieldList** list,char *name,Operand op){	
	unsigned int index=hash_pjw(name);
	FieldList *p;
	p=list[index];
	while(p!=NULL){
		if(!strcmp(p->name,name)){
			p->intercode=op;
		}
		p=p->tail;
	}
}
/*产生立即数的operand*/
Operand get_value(int data){
    return initOperand(CONSTANT,data);   
}
/*产生零时变量的operand*/
Operand new_temp(int kind){
    temp_num++;
    return initOperand(kind,temp_num-1);
}
/*产生变量的operand*/
Operand new_variable(int kind){
    var_num++;
    return initOperand(kind,var_num-1);
}
/*产生lable的operand*/
Operand new_lable(){
    lable_num++;
    return initOperand(LABLE,lable_num-1);
}
/*加入read和write函数*/
void add_func_read_and_write(){
	FieldList *read=(FieldList*)malloc(sizeof(FieldList));
	read->name="read";
	read->variable=NULL;
	read->type=(Type*)malloc(sizeof(Type));
	read->type->kind=basic;
	(read->type->u).basic=0;
	insert(read,funcList);
	FieldList *write=(FieldList*)malloc(sizeof(FieldList));
	write->name="write";
	write->variable=(FieldList *)malloc(sizeof(FieldList));
	write->variable->type=(Type*)malloc(sizeof(Type));
	write->variable->type->kind=basic;
	(write->variable->type->u).basic=0;	
	write->variable->tail=NULL;
	write->type=(Type*)malloc(sizeof(Type));
	write->type->kind=basic;
	(write->type->u).basic=0;
	insert(write,funcList);
}
/*翻译exp*/
Operand translate_Exp(struct TreeNode *root){
	assert(root!=NULL);
	switch(root->childnum){
		case 0:{
			struct TreeNode* child=root->childNode[0];
			Operand temp;
			if(!strcmp(child->data,"INT")){
			    temp=initOperand(CONSTANT,atoi(child->sub_data));
                return  temp;
            }
            else if(!strcmp(child->data,"ID")){
                temp=lookup(varList,child->sub_data);
                if(temp==NULL){
                    if(fetch(child->sub_data,varList)->type->kind==0) 
                        temp=new_variable(VARIABLE);
                    else temp=new_variable(VAR_ADDRESS);
                    inser_field_code(varList,child->sub_data,temp);
                    return temp;
                }
                else
                    return temp;
            }
            else{
                printf("error Exp childnum 0!!!\n");
                break;
            }
        }
        case 1:{
            struct TreeNode *child=root->childNode[0];
            if(!strcmp(child->data,"MINUS")){
                Operand op1=initOperand(CONSTANT,0);
                Operand op2=translate_Exp(root->childNode[1]);
                Operand result=new_temp(TEMP);
                insertCodes(1,gen_binop(SUB_IR,result,op1,op2));
                return result;
            }
            else if(!strcmp(child->data,"NOT")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                Operand code1=initOperand(CONSTANT,1);
                Operand var=new_temp(TEMP);
                insertCodes(1,gen_assign(ASSIGN_IR,code0,var));
                translate_Cond(root,lable1,lable2);
                insertCodes(3,gen_var(LABLE,lable1),gen_assign(ASSIGN_IR,code1,var),gen_var(LABLE,lable2));
                return var;
            }
            else{
                printf("error Exp childnum 1!!!\n");
                break;
            }
        }
        case 2:{
            struct TreeNode *child=root->childNode[1];
            if(!strcmp(child->data,"ASSIGNOP")){
                Operand left=translate_Exp(root->childNode[0]);
                Operand right=translate_Exp(root->childNode[1]);
                insertCodes(1,gen_assign(ASSIGN_IR,right,left));
                return NULL;
            }
            else if(!strcmp(child->data,"PLUS")){
                Operand op1=translate_Exp(root->childNode[0]);
                Operand op2=translate_Exp(root->childNode[2]);
                Operand result=new_temp(TEMP);//----------判断零时地址或者数据
                insertCodes(1,gen_binop(ADD_IR,result,op1,op2));
                return result;
            }
            else if(!strcmp(child->data,"MINUS")){
                Operand op1=translate_Exp(root->childNode[0]);
                Operand op2=translate_Exp(root->childNode[2]);
                Operand result=new_temp(TEMP);//----------判断零时地址或者数据
                insertCodes(1,gen_binop(SUB_IR,result,op1,op2));
                return result;
            }
            else if(!strcmp(child->data,"STAR")){
                Operand op1=translate_Exp(root->childNode[0]);
                Operand op2=translate_Exp(root->childNode[2]);
                Operand result=new_temp(TEMP);//----------判断零时地址或者数据
                insertCodes(1,gen_binop(MUL_IR,result,op1,op2));
                return result;
            }
            else if(!strcmp(child->data,"DIV")){
                Operand op1=translate_Exp(root->childNode[0]);
                Operand op2=translate_Exp(root->childNode[2]);
                Operand result=new_temp(TEMP);//----------判断零时地址或者数据
                insertCodes(1,gen_binop(DIV_IR,result,op1,op2));
                return result;
            }
            else if(!strcmp(child->data,"Exp")){
                return translate_Exp(root->childNode[1]);
            }
            else if(!strcmp(child->data,"LP")){
                child=root->childNode[0];
                Operand result=new_temp(TEMP);
                if(!strcmp(child->sub_data,"read")){
                    insertCodes(1,gen_var(READ_IR,result));
                    return result;
                }
                insertCodes(1,gen_callfun(CALL_IR,result,child->sub_data));
                return result;
            }
            else if(!strcmp(child->data,"DOT")){
                
            }
            else if(!strcmp(child->data,"AND")||!strcmp(child->data,"OR")||!strcmp(child->data,"RELOP")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                Operand code1=initOperand(CONSTANT,1);
                Operand var=new_temp(TEMP);
                insertCodes(1,gen_assign(ASSIGN_IR,code0,var));
                translate_Cond(root,lable1,lable2);
                insertCodes(3,gen_var(LABLE,lable1),gen_assign(ASSIGN_IR,code1,var),gen_var(LABLE,lable2));
                return var;
            }
            else {
                printf("error Exp childnum 2!!!\n");
                break;
            }
        }
        case 3:{
            
        }
	}
}
/*翻译逻辑表达*/
void translate_Cond(struct TreeNode *root,Operand lable1,Operand lable2){
}
/*翻译stmt*/
void translate_Stmt(struct TreeNode *root,Operand op){
}
/*翻译args*/
void translate_args(struct TreeNode *root,Operand op){
}

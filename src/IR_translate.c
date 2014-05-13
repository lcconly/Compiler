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
struct InterCodes* gen_iftype(int kind,char* relop,Operand op1,Operand op2,Operand lable){
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

/*获取结构体内部偏移*/
/*int getOffset(FieldList *field,char *name){
    assert((field->type->u).structure!=NULL);
    FieldList *structure=(field->type->u).structure;
    int offset=0;
    int array_size;
    while(structure->tail!=NULL){
        if(structure->type->kind==basic)
            offset+=4;
        else if(structure->type->kind==array){
            Type *type=structure->type;
            while(type->u.elem!=)
        }
    }
}*/
/*获取数组内部偏移*/
int getOffset(Type *type,int tag){
    int i=0,result=0;
    int arrSize[DATASIZE];
    while(type!=NULL){
        arrSize[i]=(type->u).array.size;
        i++;
        type=(type->u).array.elem;
    }
    for(;tag>0;tag--)
        result*=arrSize[i-tag];
    return result;
}

/*翻译exp*/
void translate_Exp(struct TreeNode *root,Operand op){
	assert(root!=NULL);
	switch(root->childnum){
		case 0:{
			struct TreeNode* child=root->childNode[0];
			Operand temp;
			if(!strcmp(child->data,"INT")){
			    temp=initOperand(CONSTANT,atoi(child->sub_data));
                insertCodes(1,gen_assign(ASSIGN_IR,op,temp));
            }
            else if(!strcmp(child->data,"ID")){
                temp=lookup(varList,child->sub_data);
                if(temp==NULL){
                    if(fetch(child->sub_data,varList)->type->kind==0) 
                        temp=new_variable(VARIABLE);
                    else temp=new_variable(VAR_ADDRESS);
                    inser_field_code(varList,child->sub_data,temp);
                    break;
                }
                insertCodes(1,gen_assign(ASSIGN_IR,op,temp));
            }
            else{
                printf("error Exp childnum 0!!!\n");
                break;
            }
            break;
        }
        case 1:{
            struct TreeNode *child=root->childNode[0];
            if(!strcmp(child->data,"MINUS")){
                Operand t1=new_temp(TEMP);
                Operand op1=initOperand(CONSTANT,0);
                translate_Exp(root->childNode[1],t1);
                insertCodes(1,gen_binop(SUB_IR,op,op1,t1));
            }
            else if(!strcmp(child->data,"NOT")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                insertCodes(1,gen_assign(ASSIGN_IR,op,code0));
                Operand code1=initOperand(CONSTANT,1);
                translate_Cond(root,lable1,lable2);
                insertCodes(3,gen_var(LABLE,lable1),gen_assign(ASSIGN_IR,op,code1),gen_var(LABLE,lable2));
            }
            else{
                printf("error Exp childnum 1!!!\n");
                break;
            }
            break;
        }
        case 2:{
            struct TreeNode *child=root->childNode[1];
            if(!strcmp(child->data,"ASSIGNOP")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(2,gen_assign(ASSIGN_IR,t2,t1),gen_assign(ASSIGN_IR,t1,op));
            }
            else if(!strcmp(child->data,"PLUS")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(ADD_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"MINUS")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(SUB_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"STAR")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(MUL_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"DIV")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(DIV_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"Exp")){
                translate_Exp(root->childNode[1],op);
            }
            else if(!strcmp(child->data,"LP")){
                child=root->childNode[0];
                if(!strcmp(child->sub_data,"read")){
                    insertCodes(1,gen_var(READ_IR,op));
                }
                insertCodes(1,gen_callfun(CALL_IR,op,child->sub_data));
            }
            else if(!strcmp(child->data,"DOT")){
            //    Operand op=translate_Exp(root->childNode[0]);
            //    FieldList *field=fetch(root->childNode[0]->childNode[0]->sub_data,varList);
            //    FieldList *structType=fetch((field->type->u).structure->name,structList);
            //    int offset=getOffset(structType,root->childNode[2]->sub_data);
                printf("Can not translate the code: Contain structure and function parameters of structure type!\n");
            }
            else if(!strcmp(child->data,"AND")||!strcmp(child->data,"OR")||!strcmp(child->data,"RELOP")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                insertCodes(1,gen_assign(ASSIGN_IR,op,code0));
                Operand code1=initOperand(CONSTANT,1);
                translate_Cond(root,lable1,lable2);
                insertCodes(3,gen_var(LABLE,lable1),gen_assign(ASSIGN_IR,op,code1),gen_var(LABLE,lable2));
            }
            else {
                printf("error Exp childnum 2!!!\n");
                break;
            }
        }
        case 3:{
            struct TreeNode *child=root->childNode[0];
            if(!strcmp(child->data,"Exp")){
                char *name;
                int tag=0;//记录层树
                while(child!=NULL){
                    //tag++;
                    if(child->data,"ID"){
                        strcpy(name,child->sub_data);
                        break;
                    }
                    tag++;
                    child=child->childNode[0];
                }
                Operand op1=new_temp(TEMP);
                translate_Exp(root->childNode[0],op1);
                Operand op2=new_temp(TEMP);
                Operand op3=new_temp(TEMP);
                translate_Exp(root->childNode[2],op2);
                Operand op4=initOperand(CONSTANT,4*getOffset(fetch(name,varList)->type,tag));
                insertCodes(2,gen_binop(MUL_IR,op3,op2,op4),gen_binop(ADD_IR,op,op1,op3));
            }
            else if(!strcmp(root->data,"ID")){
                FieldList *field=(FieldList*)malloc(sizeof(FieldList));
                field=translate_args(root->childNode[2],field);
                if(!strcmp(child->sub_data,"write"))
                    insertCodes(1,gen_var(WRITE_IR,field->intercode));
                else{
                    FieldList *p,*q;
                    p=field;
                    q=p;
                    while(p!=NULL){
                        insertCodes(1,gen_var(ARG_IR,p->intercode));
                        p=p->tail;
                        free(q);
                        q=p;
                    }
                    insertCodes(1,gen_callfun(CALL_IR,op,child->sub_data));
                }
            }
            else{
                printf("error Exp childnum 3!!!\n");
                break; 
            }
        }
        default:
            printf("Error childnum!!!\n");
            break;
    }
}
/*遍历args的子树*/
FieldList* translate_args(struct TreeNode *root,FieldList *args){
    int i=0;
    Operand op=new_temp(TEMP);
    if(root!=NULL){
        FieldList *temp=NULL;
        Type *temp_type;
        if(!strcmp(root->data,"Args"))
            if(!strcmp(root->childNode[0]->data,"Exp")){
                if((temp_type=travel_exp_tree(root->childNode[0]))!=NULL) {
                    temp=(FieldList *)malloc(sizeof(FieldList));
                    translate_Exp(root->childNode[0],op);
                    temp->type=temp_type;
                    temp->intercode=op;
                }
            }
        if(temp!=NULL){
            if(args==NULL){
                temp->tail=NULL;
                args=temp;
            }
            else{
                FieldList *p=args;
                while(p->tail!=NULL)
                    p=p->tail;
                p->tail=temp;
                //printf("----------%d\n",temp->type->kind);
                temp->tail=NULL;
            }
        }
        for(i=0;i<=root->childnum;i++)
            args=translate_args(root->childNode[i],args);
    }
    return args;
}

/*翻译逻辑表达*/
void translate_Cond(struct TreeNode *root,Operand lable1,Operand lable2){
    switch(root->childnum){
        case 1:{
            if(!strcmp(root->childNode[0]->data,"NOT")){
                translate_Cond(root->childNode[1],lable1,lable2);
                return ;
            }
            break;
        }
        case 2:{
            if(!strcmp(root->childNode[1]->data,"RELOP")){
                Operand t1=new_temp(TEMP);
                Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(2,gen_iftype(IF_IR,root->childNode[1]->sub_data,t1,t2,lable1),gen_var(LABLE,lable2));
                return ;
            }
            if(!strcmp(root->childNode[1]->data,"AND")){
                Operand lable=new_lable();
                translate_Cond(root->childNode[0],lable,lable2);
                insertCodes(1,gen_var(LABLE,lable));
                translate_Cond(root->childNode[2],lable1,lable2);
                return ;
            }
            if(!strcmp(root->childNode[1]->data,"OR")){
                Operand lable=new_lable();
                translate_Cond(root->childNode[0],lable1,lable);
                insertCodes(1,gen_var(LABLE,lable));
                translate_Cond(root->childNode[2],lable1,lable2);
                return ;
            }
            break;
        }
        default:
            printf("error cond childnum!!\n");
            return ;
    }
    Operand t1=new_temp(TEMP);
    translate_Exp(root,t1);
    insertCodes(2,gen_iftype(IF_IR,"!=",t1,initOperand(CONSTANT,0),lable1),gen_var(LABLE,lable2));
}

/*翻译stmt*/
void translate_Stmt(struct TreeNode *root){
    switch(root->childnum){
        case 0:{
            translate(root->childNode[0]);
            break;
        }
        case 1:{
            translate_Exp(root->childNode[0],NULL);
            break;
        }
        case 2:{
            Operand t1=new_temp(TEMP);
            translate_Exp(root->childNode[1],t1);
            insertCodes(1,gen_var(RETURN_IR,t1));
            break;
        }
        case 4:{
            if(!strcmp(root->childNode[0]->data,"IF")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                translate_Cond(root->childNode[2],lable1,lable2);
                insertCodes(1,gen_var(LABLE,lable1));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(LABLE,lable2));
                break;
            }
            else if(!strcmp(root->childNode[0]->data,"WHILE")){
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand lable3=new_lable();
                insertCodes(1,gen_var(LABLE,lable1));
                translate_Cond(root->childNode[2],lable2,lable3);
                insertCodes(1,gen_var(LABLE,lable2));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(GOTO_IR,lable1));
                insertCodes(1,gen_var(LABLE,lable3)); 
            }
        }
        case 6:{
                Operand lable1=new_lable();
                Operand lable2=new_lable();
                Operand lable3=new_lable();
                translate_Cond(root->childNode[2],lable1,lable2);
                insertCodes(1,gen_var(LABLE,lable1));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(GOTO_IR,lable3));
                insertCodes(1,gen_var(LABLE,lable2));
                translate_Stmt(root->childNode[6]);
                insertCodes(1,gen_var(LABLE,lable3)); 
        }
        default:
            printf("error Stmt childnum!!!\n");
            break;
    }
}

/*翻译fundec*/
void translate_fundec(struct TreeNode *root){

}

/*从根部翻译*/
void translate(struct TreeNode* root){
    int i=0;
    struct TreeNode *temp=NULL;
    for(i=0; i<=root->childnum; i++){
        temp=root->childNode[i];
        if(!strcmp(temp->data,"FunDec")){
            translate_fundec(temp);
            continue;
        }
        else if(!strcmp(temp->data,"Stmt")){
            translate_Stmt(temp);
            continue;
        }
        translate(temp);
    }
}

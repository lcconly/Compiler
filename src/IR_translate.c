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
		printCodeToTerminal(code_temp);
		list_add_before(&ir_head,&code_temp->queue);
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
		case LABEL:
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
struct InterCodes* gen_iftype(int kind,char* relop,Operand op1,Operand op2,Operand label){
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.if_type.relop=relop;
	(temp->code).u.if_type.op1=op1;
	(temp->code).u.if_type.op2=op2;
	(temp->code).u.if_type.lable=label;		
	return temp;
}
/*产生Callfun中间代码*/
struct InterCodes*  gen_callfun(int kind,Operand returnop,char* name){	
	struct InterCodes *temp=(struct InterCodes*)malloc(sizeof(struct InterCodes));
	(temp->code).kind=kind;
	(temp->code).u.call_fun.returnop=returnop;
	(temp->code).u.call_fun.name=name;	
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
	//assert((temp->code).u.if_type.relop!=NULL);
	(temp->code).u.name=name;	
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
/*产生label的operand*/
Operand new_lable(){
    lable_num++;
    return initOperand(LABEL,lable_num-1);
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
    int i=0,result=1;
    int arrSize[DATASIZE];
    while(type!=NULL){
        arrSize[i]=(type->u).array.size;
        i++;
        type=(type->u).array.elem;
    }
    for(;tag>1;tag--)
        result*=arrSize[i-tag-1];
    return result;
}

/*获取数组大小*/
int getArraySize(Type *type){
    int result=1;
    while(type!=NULL){
        if(((type->u).array.elem)!=NULL){
            result*=(type->u).array.size;
        }
        type=(type->u).array.elem;
    }
    return result;
}
/*单链表反转*/
FieldList *listreverse(FieldList *pHead)  
{  
    FieldList *pList=pHead;  
    FieldList *paPre=NULL;  
    FieldList *paNext=NULL;  
    do  
    {  
            paNext=pList->tail;  
            pList->tail=paPre;  
            paPre=pList;  
            pList=paNext;  
        }while(pList!=NULL);  
    return paPre;  
} 
/*翻译exp*/
void translate_Exp(struct TreeNode *root,Operand op){
	//printf("translate_Exp!!\n");
	assert(root!=NULL);
    if(op==NULL)
        op=new_temp(TEMP);
	switch(root->childnum){
		case 0:{//INT || ID
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
                }
                insertCodes(1,gen_assign(ASSIGN_IR,op,temp));
                //op=*(&temp);
            }
            else{
                printf("error Exp childnum 0!!!\n");
                break;
            }
            break;
        }
        case 1:{//MINUS EXP || Not EXP
            struct TreeNode *child=root->childNode[0];
            if(!strcmp(child->data,"MINUS")){
                Operand t1=new_temp(TEMP);
                Operand op1=initOperand(CONSTANT,0);
                translate_Exp(root->childNode[1],t1);
                insertCodes(1,gen_binop(SUB_IR,op,op1,t1));
            }
            else if(!strcmp(child->data,"NOT")){
                Operand label1=new_lable();
                Operand label2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                insertCodes(1,gen_assign(ASSIGN_IR,op,code0));
                Operand code1=initOperand(CONSTANT,1);
                translate_Cond(root,label1,label2);
                insertCodes(3,gen_var(LABEL_IR,label1),gen_assign(ASSIGN_IR,op,code1),gen_var(LABEL_IR,label2));
            }
            else{
                printf("error Exp childnum 1!!!\n");
                break;
            }
            break;
        }
        case 2:{//EXP op EXP||LP EXP RP ||ID LP RP
            struct TreeNode *child=root->childNode[1];
            if(!strcmp(child->data,"ASSIGNOP")){
                Operand t1=NULL;//=new_temp(TEMP);
                if(root->childNode[0]->childnum==0){
                    t1=lookup(varList,root->childNode[0]->childNode[0]->sub_data);
                    if(t1==NULL){
                        if(fetch(root->childNode[0]->childNode[0]->sub_data,varList)->type->kind==0) 
                            t1=new_variable(VARIABLE);
                        else t1=new_variable(VAR_ADDRESS);
                        inser_field_code(varList,root->childNode[0]->childNode[0]->sub_data,t1);
                    }
                }
                else{
                    t1=new_temp(TEMP_MEMORY);
                    translate_Exp(root->childNode[0],t1);
                }
                Operand t2;
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                translate_Exp(root->childNode[2],t2);
                insertCodes(2,gen_assign(ASSIGN_IR,t1,t2),gen_assign(ASSIGN_IR,op,t1));
            }
            else if(!strcmp(child->data,"PLUS")){
                Operand t1,t2;
                if(root->childNode[0]->childnum==3&&!strcmp(root->childNode[0]->childNode[1]->data,"LB"))
                    t1=new_temp(TEMP_MEMORY);
                else t1=new_temp(TEMP);
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(ADD_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"MINUS")){
                Operand t1,t2;
                if(root->childNode[0]->childnum==3&&!strcmp(root->childNode[0]->childNode[1]->data,"LB"))
                    t1=new_temp(TEMP_MEMORY);
                else t1=new_temp(TEMP);
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(SUB_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"STAR")){
                Operand t1,t2;
                if(root->childNode[0]->childnum==3&&!strcmp(root->childNode[0]->childNode[1]->data,"LB"))
                    t1=new_temp(TEMP_MEMORY);
                else t1=new_temp(TEMP);
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_binop(MUL_IR,op,t1,t2));
            }
            else if(!strcmp(child->data,"DIV")){
                Operand t1,t2;
                if(root->childNode[0]->childnum==3&&!strcmp(root->childNode[0]->childNode[1]->data,"LB"))
                    t1=new_temp(TEMP_MEMORY);
                else t1=new_temp(TEMP);
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
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
					break;
                }
                insertCodes(1,gen_callfun(CALL_IR,op,child->sub_data));
            }
            else if(!strcmp(child->data,"DOT")){
            //    Operand op=translate_Exp(root->childNode[0]);
            //    FieldList *field=fetch(root->childNode[0]->childNode[0]->sub_data,varList);
            //    FieldList *structType=fetch((field->type->u).structure->name,structList);
            //    int offset=getOffset(structType,root->childNode[2]->sub_data);
                printf("Can not translate the code: Contain structure and function parameters of structure type!\n");
                fprintf(fopen("out.ir","w"),"Can not translate the code: Contain structure and function parameters of structure type!\n");
                exit(0);
            }
            else if(!strcmp(child->data,"AND")||!strcmp(child->data,"OR")||!strcmp(child->data,"RELOP")){
                Operand label1=new_lable();
                Operand label2=new_lable();
                Operand code0=initOperand(CONSTANT,0);
                insertCodes(1,gen_assign(ASSIGN_IR,op,code0));
                Operand code1=initOperand(CONSTANT,1);
                translate_Cond(root,label1,label2);
                insertCodes(3,gen_var(LABEL_IR,label1),gen_assign(ASSIGN_IR,op,code1),gen_var(LABEL_IR,label2));
            }
            else {
                printf("error Exp childnum 2!!!\n");
                break;
            }
			break;
        }
        case 3:{//ID LP ARGS RP || Exp LB Exp RB
            struct TreeNode *child=root->childNode[0];
            if(!strcmp(child->data,"Exp")){
                char *name;
                int tag=0;//记录层树
                while(child!=NULL){
                    //tag++;
                    if(!strcmp(child->data,"ID")){
                        //strcpy(name,child->sub_data);
                        name=child->sub_data;
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
				assert(fetch(name,varList)!=NULL);
                Operand op4=initOperand(CONSTANT,4*getOffset(fetch(name,varList)->type,tag));
                Operand arr=(Operand)malloc(sizeof(struct Operand_));
                arr->kind=TEMP;
                arr->u.temp_no=op->u.temp_no;
                insertCodes(2,gen_binop(MUL_IR,op3,op2,op4),gen_binop(ADD_IR,arr,op1,op3));
            }
            else if(!strcmp(child->data,"ID")){
                FieldList *field=NULL;
                field=translate_args(root->childNode[2],field);
                assert(field->intercode!=NULL);
                if(!strcmp(child->sub_data,"write"))
                    insertCodes(1,gen_var(WRITE_IR,field->intercode));
                else{
                    FieldList *p,*q;
                    p=listreverse(field);
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
			break;
        }
        default:
            printf("Error childnum!!!\n");
            break;
    }
}
/*遍历args的子树*/
FieldList* translate_args(struct TreeNode *root,FieldList *args){
	//printf("translate_args!!\n");
    int i=0;
    //Operand op=new_temp(TEMP);
    if(root!=NULL){
        FieldList *temp=NULL;
        //Type *temp_type;
        if(!strcmp(root->data,"Args"))
            if(!strcmp(root->childNode[0]->data,"Exp")){
                //if((temp_type=travel_exp_tree(root->childNode[0]))!=NULL) {
				Operand op;
                temp=(FieldList *)malloc(sizeof(FieldList));
                //    translate_Exp(root->childNode[0],op);
                //    temp->type=temp_type;
                if(root->childNode[0]->childnum==0&&!strcmp(root->childNode[0]->childNode[0]->data,"ID")){
                    op=lookup(varList,root->childNode[0]->childNode[0]->sub_data);
                    if(op==NULL){
                        if(fetch(root->childNode[0]->childNode[0]->sub_data,varList)->type->kind==0) 
                            op=new_variable(VARIABLE);
                        else op=new_variable(VAR_ADDRESS);
                        inser_field_code(varList,root->childNode[0]->childNode[0]->sub_data,op);
                    }
                }
                else if(root->childNode[0]->childnum==0&&!strcmp(root->childNode[0]->childNode[0]->data,"INT")){
                    op=initOperand(CONSTANT,atoi(root->childNode[0]->childNode[0]->sub_data));
                }
                else if(root->childNode[0]->childnum==1&&!strcmp(root->childNode[0]->childNode[0]->data,"MINUS")){
                    op=initOperand(CONSTANT,0-atoi(root->childNode[0]->childNode[1]->childNode[0]->sub_data));
                }
                else if(root->childNode[0]->childnum==2
                   &&(!strcmp(root->childNode[0]->childNode[1]->data,"Exp")||
                     !strcmp(root->childNode[0]->childNode[1]->data,"PLUS")||
                     !strcmp(root->childNode[0]->childNode[1]->data,"MINUS")||
                     !strcmp(root->childNode[0]->childNode[1]->data,"STAR")||
                     !strcmp(root->childNode[0]->childNode[1]->data,"DIV"))){
                    op=new_temp(TEMP);
                    translate_Exp(root->childNode[0],op);
                }
                else{
                    op=new_temp(TEMP_MEMORY);
                    translate_Exp(root->childNode[0],op);
                }
                temp->intercode=op;
                assert(temp->intercode!=NULL);
                //}
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
void translate_Cond(struct TreeNode *root,Operand label1,Operand label2){
	//printf("translate_Cond!!\n");
    switch(root->childnum){
        case 1:{
            if(!strcmp(root->childNode[0]->data,"NOT")){
                translate_Cond(root->childNode[1],label2,label1);
                return ;
            }
            break;
        }
        case 2:{
            if(!strcmp(root->childNode[1]->data,"RELOP")){
                Operand t1,t2;
                if(root->childNode[0]->childnum==3&&!strcmp(root->childNode[0]->childNode[1]->data,"LB"))
                    t1=new_temp(TEMP_MEMORY);
                else t1=new_temp(TEMP);
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                //Operand t1=new_temp(TEMP);
                //Operand t2=new_temp(TEMP);
                translate_Exp(root->childNode[0],t1);
                translate_Exp(root->childNode[2],t2);
                insertCodes(2,gen_iftype(IF_IR,root->childNode[1]->sub_data,t1,t2,label1),gen_var(GOTO_IR,label2));
                return ;
            }
            else if(!strcmp(root->childNode[1]->data,"AND")){
                Operand label=new_lable();
                translate_Cond(root->childNode[0],label,label2);
                insertCodes(1,gen_var(LABEL_IR,label));
                translate_Cond(root->childNode[2],label1,label2);
                return ;
            }
            else if(!strcmp(root->childNode[1]->data,"OR")){
                Operand label=new_lable();
                translate_Cond(root->childNode[0],label1,label);
                insertCodes(1,gen_var(LABEL_IR,label));
                translate_Cond(root->childNode[2],label1,label2);
                return ;
            }
            break;
        }
        default:
            printf("error cond childnum!!\n");
            break ;
    }
    Operand t1=new_temp(TEMP);
    translate_Exp(root,t1);
    insertCodes(2,gen_iftype(IF_IR,"!=",t1,initOperand(CONSTANT,0),label1),gen_var(GOTO_IR,label2));
}

/*翻译stmt*/
void translate_Stmt(struct TreeNode *root){
	//printf("translate_Stmt!!\n");
	switch(root->childnum){
        case 0:{//Compst
            translate(root->childNode[0]);
            break;
        }
        case 1:{//Exp SEMI
            translate_Exp(root->childNode[0],NULL);
            break;
        }
        case 2:{//RETURN EXP SEMI
            Operand t1=new_temp(TEMP);
            translate_Exp(root->childNode[1],t1);
            insertCodes(1,gen_var(RETURN_IR,t1));
            break;
        }
        case 4:{//IF||WHILE LP Exp RP Stmt
            if(!strcmp(root->childNode[0]->data,"IF")){
                Operand label1=new_lable();
                Operand label2=new_lable();
                translate_Cond(root->childNode[2],label1,label2);
                insertCodes(1,gen_var(LABEL_IR,label1));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(LABEL_IR,label2));
                break;
            }
            else if(!strcmp(root->childNode[0]->data,"WHILE")){
                Operand label1=new_lable();
                Operand label2=new_lable();
				Operand label3=new_lable();
                insertCodes(1,gen_var(LABEL_IR,label1));
                translate_Cond(root->childNode[2],label2,label3);
                insertCodes(1,gen_var(LABEL_IR,label2));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(GOTO_IR,label1));
                insertCodes(1,gen_var(LABEL_IR,label3)); 
				break;
			}
        }
        case 6:{//IF LP Exp RP Stmt ELSE Stmt
                Operand label1=new_lable();
                Operand label2=new_lable();
                Operand label3=new_lable();
                translate_Cond(root->childNode[2],label1,label2);
                insertCodes(1,gen_var(LABEL_IR,label1));
                translate_Stmt(root->childNode[4]);
                insertCodes(1,gen_var(GOTO_IR,label3));
                insertCodes(1,gen_var(LABEL_IR,label2));
                translate_Stmt(root->childNode[6]);
                insertCodes(1,gen_var(LABEL_IR,label3)); 
				break;	
		}
        default:
            printf("error Stmt childnum %d!!!\n",root->childnum);
            break;
    }
}

/*翻译fundec*/
void translate_fundec(struct TreeNode *root){
	//printf("function ---- %s\n",root->childNode[0]->sub_data);
	insertCodes(1,gen_id(FUNC_IR,root->childNode[0]->sub_data));
    FieldList *field=fetch(root->childNode[0]->sub_data,funcList)->variable;
    if(root->childnum==3){
        while(field!=NULL){
            if(field->type->kind==structure){
                printf("Can not translate the code: Contain structure and function parameters of structure type!\n");
                fprintf(fopen("out.ir","w"),"Can not translate the code: Contain structure and function parameters of structure type!\n");
                exit(0);
            }
            else if(field->type->kind==basic&&field->name!=NULL){
                Operand temp=lookup(varList,field->name);
                if(temp==NULL){
                    if(fetch(field->name,varList)->type->kind==0) 
                        temp=new_variable(VARIABLE);
                    else temp=new_variable(VAR_ADDRESS);
                    inser_field_code(varList,field->name,temp);
                }
                insertCodes(1,gen_array(PARAM_IR,temp,0));
            }
            else if(field->type->kind==array){
                Operand temp=lookup(varList,field->name);
                if(temp==NULL){
                    if(fetch(field->name,varList)->type->kind==0) 
                        temp=new_variable(VARIABLE);
                    else temp=new_variable(VAR_ADDRESS);
                    inser_field_code(varList,field->name,temp);
                }	
				temp->kind=VARIABLE;
                insertCodes(1,gen_array(PARAM_IR,temp,4*getArraySize(field->type)));
            }
            field=field->variable;
        }
    }
}
/*翻译declist*/
void translate_declist(struct TreeNode *root){
	//printf("translate_declist!!\n");
    int i=0;
    for(;i<=root->childnum;i++){
        if(!strcmp(root->data,"Dec")){
            if(root->childnum==2){
                Operand t1=new_variable(VARIABLE);
                Operand t2;
                if(root->childNode[2]->childnum==3&&!strcmp(root->childNode[2]->childNode[1]->data,"LB"))
                    t2=new_temp(TEMP_MEMORY);
                else t2=new_temp(TEMP);
                translate_Exp(root->childNode[2],t2);
                insertCodes(1,gen_assign(ASSIGN_IR,t1,t2));
                struct TreeNode *vardec=root->childNode[0];
                while(vardec!=NULL){
                    if(!strcmp(vardec->data,"ID"))
                        break;
                    vardec=vardec->childNode[0];
                }
                inser_field_code(varList,vardec->sub_data,t1);
                return ;
            }
            else if(root->childnum==0){
                if(!strcmp(root->childNode[0]->childNode[0]->data,"VarDec")){
                    //printf("!!!\n");
                    struct TreeNode *node;
                    node=root->childNode[0]->childNode[0];
                    while(strcmp(node->data,"ID")){
                        node=node->childNode[0];
                    }
                    FieldList *field=fetch(node->sub_data,varList);
                    Operand temp=lookup(varList,node->sub_data);
                    if(temp==NULL){
                        if(fetch(node->sub_data,varList)->type->kind==0) 
                            temp=new_variable(VARIABLE);
                        else temp=new_variable(VAR_ADDRESS);
                        inser_field_code(varList,node->sub_data,temp);
                    }
					Operand temp1=(Operand)malloc(sizeof(struct Operand_));
					temp1->kind=VARIABLE;
					temp1->u.var_no=temp->u.var_no;
                    //printf("size : %d\n",getArraySize(field->type));
                    insertCodes(1,gen_array(DEC_IR,temp1,4*getArraySize(field->type)));
                    return ;
                }
            }
        }
        translate_declist(root->childNode[i]);
    }

}

/*从根部翻译*/
void translate(struct TreeNode* root){
    int i=0;
    struct TreeNode *temp=NULL;
    for(i=0; i<=root->childnum; i++){
        temp=root->childNode[i];
        if(!strcmp(temp->data,"FunDec"))
            translate_fundec(temp);
        if(!strcmp(temp->data,"DecList")||!strcmp(temp->data,"ExtDecList"))
            translate_declist(temp);
        else if(!strcmp(temp->data,"Stmt"))
            translate_Stmt(temp);
        else translate(temp);
    }
}

/*判断operand相等*/
bool charge_op_equal(Operand op1,Operand op2){
	if(op1->kind!=op2->kind)
		return false;
	switch(op1->kind){	
		case VARIABLE:
			if((op1->u).var_no!=(op2->u).var_no)
				return false;
			break;
		case CONSTANT:
			if((op1->u).value!=(op2->u).value)
				return false;
			break;
		case TEMP_ADDRESS:
			if((op1->u).temp_no!=(op2->u).temp_no)
				return false;
			break;
		case VAR_ADDRESS:
			if((op1->u).var_no!=(op2->u).var_no)
				return false;
			break;
		case TEMP:
			if((op1->u).temp_no!=(op2->u).temp_no)
				return false;
			break;
		case LABEL:
			if((op1->u).lable_no!=(op2->u).lable_no)
				return false;
			break;
		case VAR_MEMORY:
			if((op1->u).var_no!=(op2->u).var_no)
				return false;
			break;
		case TEMP_MEMORY:
			if((op1->u).temp_no=(op2->u).temp_no)
				return false;
			break;
		default:
			printf("Operand kind error!!!\n");
			break;
	}
	return true;
}
/*优化*/
void optimize(){
	struct InterCodes *temp=list_entry(ir_head.next,struct InterCodes,queue);
    while(temp!=list_entry(&ir_head,struct InterCodes,queue)){
        struct InterCodes *next=list_entry(temp->queue.next,struct InterCodes,queue);
		int is_used=0;
        if(temp->code.kind==ASSIGN_IR)
			while(next!=list_entry(&ir_head,struct InterCodes,queue)){
				switch(next->code.kind){
					case ASSIGN_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.assign.right))
							is_used=1;
						break;
					case ADD_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op1)||
						charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op2))
							is_used=1;
						break;
					case SUB_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op1)||
						charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op2))
							is_used=1;
						break;
					case MUL_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op1)||
						charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op2))
							is_used=1;
						break;
					case DIV_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op1)||
						charge_op_equal(temp->code.u.assign.left,next->code.u.binop.op2))
							is_used=1;
						break;
					case LABEL_IR:
						break;
					case FUNC_IR:
						break;
					case GOTO_IR:	
						break;
					case IF_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.if_type.op1)||
						charge_op_equal(temp->code.u.assign.left,next->code.u.if_type.op2))
							is_used=1;
						break;
					case RETURN_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.op))
							is_used=1;
						break;
					case DEC_IR:
						break;
					case ARG_IR:
						if(charge_op_equal(temp->code.u.assign.left,next->code.u.op))
							is_used=1;
						break;
					case CALL_IR:
						break;
					case PARAM_IR:
						break;
					case READ_IR:
						break;
					case WRITE_IR:
						break;
					default:
						break;
				}
				if(is_used==1)
					break;
				next=list_entry(next->queue.next,struct InterCodes,queue);
			}
		struct InterCodes *p=temp;
        temp=list_entry(temp->queue.next,struct InterCodes,queue);
		if(is_used==1){
			list_del(&p->queue);
			free(p);
		}
    } 
}

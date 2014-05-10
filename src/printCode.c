/*************************************************************************
	> File Name: printCode.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sat 10 May 2014 09:43:31 PM CST
 ************************************************************************/

#include"IR.h"
/*根据Operand输出中间代码的符号*/
char* printOperand(Operand op){
	char* data;
	data=(char*)malloc(DATASIZE);
	switch(op->kind){
		case VARIABLE:
			sprintf(data,"v%d",(op->u).var_no);
			break;
		case CONSTANT:
			sprintf(data,"#%d",(op->u).value);
			break;
		case TEMP_ADDRESS:
			sprintf(data,"&t%d",(op->u).temp_no);
			break;
		case VAR_ADDRESS:
			sprintf(data,"&v%d",(op->u).var_no);
			break;
		case TEMP:
			sprintf(data,"t%d",(op->u).temp_no);
			break;
		case LABLE:
			sprintf(data,"lable%d",(op->u).lable_no);
			break;
		case VAR_MEMORY:
			sprintf(data,"*v%d",(op->u).var_no);
			break;
		case TEMP_MEMORY:
			sprintf(data,"*t%d",(op->u).temp_no);
			break;
		default:
			printf("Operand kind error!!!\n");
			break;
	}
	return data;
}
/*打印中间代码到文件*/
void printCodeToFile(char *filename){
	struct InterCodes *temp;
	if(ir_head!=NULL)
		temp=ir_head->next;
	else
		printf("error: ir_head is NULL!!!\n");
	FILE *fp=fopen(filename,"w");
	while(temp!=NULL){
		switch((temp->code).kind){
			case ASSIGN:
				fprintf(fp,"%s",printOperand((temp->code).u.assign.right));
				fprintf(fp," := ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.assign.left));
				break;
			case ADD:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," + ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case SUB:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," - ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case MUL:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," * ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case DIV:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," / ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case GOTO:	
				fprintf(fp,"GOTO ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case IF:
				fprintf(fp,"IF ");
				fprintf(fp,"%s",printOperand((temp->code).u.if_type.op1));
				fprintf(fp," %s ",(temp->code).u.if_type.relop);
				fprintf(fp,"%s",printOperand((temp->code).u.if_type.op2));
				fprintf(fp," GOTO ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.if_type.lable));
				break;
			case RETURN:
				fprintf(fp,"RETURN ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case DEC:
				fprintf(fp,"DEC ");
				fprintf(fp,"%s ",printOperand((temp->code).u.array.op));
				fprintf(fp,"%d\n",(temp->code).u.array.size);	
				break;
			case ARG:
				fprintf(fp,"ARG ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case CALL:
				fprintf(fp,"%s",printOperand((temp->code).u.call_fun.returnop));
				fprintf(fp," := CALL ");
				fprintf(fp,"%s\n",(temp->code).u.call_fun.name);
				break;
			case PARAM:
				fprintf(fp,"PARAM ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case READ:
				fprintf(fp,"READ ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case WRITE:
				fprintf(fp,"WRITE ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			default:
				printf("InterCodes kind type!!!\n");
				break;
		}
	}
}

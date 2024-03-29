/*************************************************************************
	> File Name: printCode.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Sat 10 May 2014 09:43:31 PM CST
 ************************************************************************/

#include "../include/IR.h"
/*根据Operand输出中间代码的符号*/
char* printOperand(Operand op){
	char* data;
	data=(char*)malloc(DATASIZE);
	assert(op!=NULL);
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
		case LABEL:
			sprintf(data,"label%d",(op->u).lable_no);
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
	struct InterCodes *temp=list_entry(ir_head.next,struct InterCodes,queue);
	FILE *fp=fopen(filename,"w");
	while(temp!=list_entry(&ir_head,struct InterCodes,queue)){
		switch((temp->code).kind){
			case ASSIGN_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.assign.right));
				fprintf(fp," := ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.assign.left));
				break;
			case ADD_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," + ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case SUB_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," - ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case MUL_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," * ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case DIV_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.binop.result));
				fprintf(fp," := ");
				fprintf(fp,"%s",printOperand((temp->code).u.binop.op1));
				fprintf(fp," / ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.binop.op2));
				break;
			case LABEL_IR:
				fprintf(fp,"LABEL %s :\n",printOperand((temp->code).u.op));
				break;
			case FUNC_IR:
				fprintf(fp,"FUNCTION %s :\n",(temp->code).u.name);
				break;
			case GOTO_IR:	
				fprintf(fp,"GOTO ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case IF_IR:
				fprintf(fp,"IF ");
				fprintf(fp,"%s",printOperand((temp->code).u.if_type.op1));
				fprintf(fp," %s ",(temp->code).u.if_type.relop);
				fprintf(fp,"%s",printOperand((temp->code).u.if_type.op2));
				fprintf(fp," GOTO ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.if_type.lable));
				break;
			case RETURN_IR:
				fprintf(fp,"RETURN ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case DEC_IR:
				fprintf(fp,"DEC ");
				fprintf(fp,"%s",printOperand((temp->code).u.array.op));
				if((temp->code).u.array.size!=0)
					fprintf(fp," %d\n",(temp->code).u.array.size);	
				else
					fprintf(fp,"\n");
				break;
			case ARG_IR:
				fprintf(fp,"ARG ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case CALL_IR:
				fprintf(fp,"%s",printOperand((temp->code).u.call_fun.returnop));
				fprintf(fp," := CALL ");
				fprintf(fp,"%s\n",(temp->code).u.call_fun.name);
				break;
			case PARAM_IR:
				fprintf(fp,"PARAM ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case READ_IR:
				fprintf(fp,"READ ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			case WRITE_IR:
				fprintf(fp,"WRITE ");
				fprintf(fp,"%s\n",printOperand((temp->code).u.op));
				break;
			default:
				printf("InterCodes kind type!!!\n");
				break;
		}
        temp=list_entry(temp->queue.next,struct InterCodes,queue);
	}
}
/*打印中间代码到屏幕*/
void printCodeToTerminal(struct InterCodes* temp){
	switch((temp->code).kind){
		case ASSIGN_IR:
			printf("%s",printOperand((temp->code).u.assign.right));
			printf(" := ");
			printf("%s\n",printOperand((temp->code).u.assign.left));
			break;
		case ADD_IR:
			printf("%s",printOperand((temp->code).u.binop.result));
			printf(" := ");
			printf("%s",printOperand((temp->code).u.binop.op1));
			printf(" + ");
			printf("%s\n",printOperand((temp->code).u.binop.op2));
			break;
		case SUB_IR:
			printf("%s",printOperand((temp->code).u.binop.result));
			printf(" := ");
			printf("%s",printOperand((temp->code).u.binop.op1));
			printf(" - ");
			printf("%s\n",printOperand((temp->code).u.binop.op2));
			break;
		case MUL_IR:
			printf("%s",printOperand((temp->code).u.binop.result));
			printf(" := ");
			printf("%s",printOperand((temp->code).u.binop.op1));
			printf(" * ");
			printf("%s\n",printOperand((temp->code).u.binop.op2));
			break;
		case DIV_IR:
			printf("%s",printOperand((temp->code).u.binop.result));
			printf(" := ");
			printf("%s",printOperand((temp->code).u.binop.op1));
			printf(" / ");
			printf("%s\n",printOperand((temp->code).u.binop.op2));
			break;
		case FUNC_IR:
			printf("FUNCTION %s :\n",(temp->code).u.name);
			break;
		case LABEL_IR:
			printf("LABEL %s :\n",printOperand((temp->code).u.op));
			break;
		case GOTO_IR:	
			printf("GOTO ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		case IF_IR:
			printf("IF ");
			printf("%s",printOperand((temp->code).u.if_type.op1));
			printf(" %s ",(temp->code).u.if_type.relop);
			printf("%s",printOperand((temp->code).u.if_type.op2));
			printf(" GOTO ");
			printf("%s\n",printOperand((temp->code).u.if_type.lable));
			break;
		case RETURN_IR:
			printf("RETURN ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		case DEC_IR:
			printf("DEC ");
			printf("%s",printOperand((temp->code).u.array.op));
			if((temp->code).u.array.size!=0)
				printf(" %d\n",(temp->code).u.array.size);	
			else
				printf("\n");
			break;
		case ARG_IR:
			printf("ARG ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		case CALL_IR:
			printf("%s",printOperand((temp->code).u.call_fun.returnop));
			printf(" := CALL ");
			printf("%s\n",(temp->code).u.call_fun.name);
			break;
		case PARAM_IR:
			printf("PARAM ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		case READ_IR:
			printf("READ ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		case WRITE_IR:
			printf("WRITE ");
			printf("%s\n",printOperand((temp->code).u.op));
			break;
		default:
			printf("InterCodes kind type!!!\n");
			break;

	}
}

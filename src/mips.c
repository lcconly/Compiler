/*************************************************************************
	> File Name: mips.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 12 Jun 2014 04:56:04 PM CST
 ************************************************************************/

#include "mips.h"
#include "IR.h"
/*设置便宜量*/
void set_offset(Operand op){

}
/*获取偏移量*/
void get_offset(Operand op){
    opoffset *temp=list_entry(opoff.next,struct OPOFFSET,queue);
    while(temp!=list_entry(&opoff,struct OPOFFSET ,queue)){
        
    }
}
/*mips打印函数*/
void mips_print(char *name){
	struct InterCodes *temp=list_entry(ir_head.next,struct InterCodes,queue);
	FILE *fp=fopen(name,"w");
	fprintf(fp,".data\n");
    fprintf(fp,"_prompt: .asciiz \"Enter an integer:\"");
    fprintf(fp,"_ret: .asciiz \"\\n\"\n");
    fprintf(fp,".globl main\n");
    fprintf(fp,".text\n");
    fprintf(fp,"read:\n");
    fprintf(fp,"   li $v0, 4\n");
    fprintf(fp,"   la $a0, _prompt\n");
    fprintf(fp,"   syscall\n");
    fprintf(fp,"   li $v0, 5\n");
    fprintf(fp,"   syscall\n");
    fprintf(fp,"   jr $ra\n\n");
    fprintf(fp,"write:\n");
    fprintf(fp,"   li $v0, 1\n");
    fprintf(fp,"   syscall\n");
    fprintf(fp,"   li $v0, 4\n");
    fprintf(fp,"   la $a0, _ret\n");
    fprintf(fp,"   syscall\n");
    fprintf(fp,"   move $v0, $0\n");
    fprintf(fp,"   jr $ra\n");
	while(temp!=list_entry(&ir_head,struct InterCodes,queue)){
		switch((temp->code).kind){
			case ASSIGN_IR:

 				break;
			case ADD_IR:

				break;
			case SUB_IR:

				break;
			case MUL_IR:

				break;
			case DIV_IR:

				break;
			case LABEL_IR:

				break;
			case FUNC_IR:

				break;
			case GOTO_IR:	

				break;
			case IF_IR:

				break;
			case RETURN_IR:

				break;
			case DEC_IR:

				break;
			case ARG_IR:

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
				printf("InterCodes kind type!!!\n");
				break;
		}
        temp=list_entry(temp->queue.next,struct InterCodes,queue);
	}

}

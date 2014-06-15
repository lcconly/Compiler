/*************************************************************************
	> File Name: mips.c
	> Author: liucheng
	> Mail: 1035377294@qq.com 
	> Created Time: Thu 12 Jun 2014 04:56:04 PM CST
 ************************************************************************/

#include "../include/mips.h"
#include "../include/IR.h"
int sp=-32;
/*设置便宜量*/
int set_offset(Operand op){
    int offset=get_offset(op);
    if(offset==-1){
        opoffset *temp=(opoffset *)malloc(sizeof(struct OPOFFSET));
        temp->op=op;
        temp->offset=sp;
        offset=sp;
        sp-=4;
        list_add_before(&opoff,&temp->queue);
    }
    return offset;
}
/*获取偏移量*/
int get_offset(Operand op){
    opoffset *temp=list_entry(opoff.next,struct OPOFFSET,queue);
    while(temp!=list_entry(&opoff,struct OPOFFSET ,queue)){
        if(op->kind==VAR_ADDRESS){
            if((temp->op->u).var_no==(op->u).var_no)
                break;
        }
        if(op->kind==TEMP_MEMORY){
            if((temp->op->u).temp_no==(op->u).temp_no)
                break;
        }
        if(temp->op->kind==op->kind){
            if(op->kind==CONSTANT&&(temp->op->u).value==(op->u).value)
                break;
            if(temp->op->kind==VARIABLE&&(temp->op->u).var_no==(op->u).var_no)
                break;
            if(temp->op->kind==TEMP&&(temp->op->u).temp_no==(op->u).var_no)
                break; 
        }
        temp=list_entry(temp->queue.next,struct OPOFFSET ,queue);
    }
    if(temp==list_entry(&opoff,struct OPOFFSET,queue))
        return -1;
    else 
        return temp->offset;
}
/*mips打印函数*/
void mips_print(char *name){
	struct InterCodes *temp=list_entry(ir_head.next,struct InterCodes,queue);
	FILE *fp=fopen(name,"w");
	fprintf(fp,".data\n");
    fprintf(fp,"_prompt: .asciiz \"Enter an integer:\"\n");
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
                if(temp->code.u.assign.right->kind!=TEMP_MEMORY&&temp->code.u.assign.left->kind==CONSTANT)
                    fprintf(fp,"   li $t0,%d\n",temp->code.u.assign.left->u.value);
                else if(temp->code.u.assign.right->kind!=TEMP_MEMORY&&temp->code.u.assign.left->kind!=TEMP_MEMORY)
                    fprintf(fp,"   lw $t0,%d($sp)\n",get_offset(temp->code.u.assign.left));
                else if(temp->code.u.assign.right->kind!=TEMP_MEMORY&&temp->code.u.assign.left->kind==TEMP_MEMORY){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.assign.left));
                    fprintf(fp,"   lw $t0,0($t1)\n");
                }
                else if(temp->code.u.assign.right->kind==TEMP_MEMORY){
                    if(temp->code.u.assign.left->kind==CONSTANT){
                        fprintf(fp,"   lw $t0,%d($sp)\n",get_offset(temp->code.u.assign.right));
                        fprintf(fp,"   li $t1,%d\n",temp->code.u.assign.left->u.value);
                    }
                    else{
                        fprintf(fp,"   lw $t0,%d($sp)\n",get_offset(temp->code.u.assign.right));
                        fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.assign.left));
                    }
                    fprintf(fp,"   sw $t1,0($t0)\n");
                }
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.assign.right));
 				break;
			case ADD_IR:
                if(temp->code.u.binop.op1->kind==VAR_ADDRESS&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   la $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   sub $t0,$t1,$2\n");
                }
                else if(temp->code.u.binop.op1->kind==VAR_ADDRESS&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   la $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   sub $t0,$t1,%d\n",temp->code.u.binop.op2->u.value);
                }
                else if(temp->code.u.binop.op1->kind!=VAR_ADDRESS&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   addi $t0,$t1,%d\n",temp->code.u.binop.op2->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   addi $t0,%d,%d\n",temp->code.u.binop.op1->u.value,temp->code.u.binop.op2->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   addi $t0,%d,$t1\n",temp->code.u.binop.op1->u.value);
                }
                else{
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   add $t0,$t1,$t2\n");
                }
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.binop.result));
				break;
			case SUB_IR:
                if(temp->code.u.binop.op1->kind!=CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   sub $t0,$t1,%d\n",temp->code.u.binop.op2->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   sub $t0,%d,$t1\n",temp->code.u.binop.op1->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT)
                    fprintf(fp,"   sub $t0,%d,%d\n",temp->code.u.binop.op1->u.value,temp->code.u.binop.op2->u.value);
                else{
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   sub $t0,$t1,$t2\n");
                }
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.binop.result));
				break;
			case MUL_IR: 
                if(temp->code.u.binop.op1->kind!=CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   mul $t0,$t1,%d\n",temp->code.u.binop.op2->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   mul $t0,%d,$t1\n",temp->code.u.binop.op1->u.value);
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT)
                    fprintf(fp,"   mul $t0,%d,%d\n",temp->code.u.binop.op1->u.value,temp->code.u.binop.op2->u.value);
                else{
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   mul $t0,$t1,$t2\n");
                }
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.binop.result));
				break;
			case DIV_IR:
                if(temp->code.u.binop.op1->kind!=CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   li $t2,%d\n",temp->code.u.binop.op2->u.value);
                    fprintf(fp,"   div $t1,$t2\n");
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   li $t1,%d\n",temp->code.u.binop.op1->u.value);
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   div $t1,$t2\n");
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   li $t1,%d\n",temp->code.u.binop.op1->u.value);
                    fprintf(fp,"   li $t2,%d\n",temp->code.u.binop.op2->u.value);
                    fprintf(fp,"   div $t1,$t2\n");
                }
                else {
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                    fprintf(fp,"   div $t1,$t2\n");
                }
                fprintf(fp,"   mflo $t0\n");
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.binop.result));
				break;
			case LABEL_IR:
                fprintf(fp,"lable%d:\n",temp->code.u.op->u.lable_no);
				break;
			case FUNC_IR:
                fprintf(fp,"%s:\n",temp->code.u.name);
				break;
			case GOTO_IR:	
                fprintf(fp,"   j lable%d\n",temp->code.u.op->u.lable_no);
				break;
			case IF_IR:
                if(temp->code.u.binop.op1->kind!=CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   li $t2,%d\n",temp->code.u.binop.op2->u.value);
                } 
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind!=CONSTANT){
                    fprintf(fp,"   li $t1,%d\n",temp->code.u.binop.op1->u.value);
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                }
                else if(temp->code.u.binop.op1->kind==CONSTANT&&temp->code.u.binop.op2->kind==CONSTANT){
                    fprintf(fp,"   li $t1,%d\n",temp->code.u.binop.op1->u.value);
                    fprintf(fp,"   li $t2,%d\n",temp->code.u.binop.op2->u.value);
                }
                else{
                    fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.binop.op1));
                    fprintf(fp,"   lw $t2,%d($sp)\n",get_offset(temp->code.u.binop.op2));
                }
                if(!strcmp(temp->code.u.if_type.relop,"=="))
                    fprintf(fp,"   beq $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
				else if(!strcmp(temp->code.u.if_type.relop,"!="))
                    fprintf(fp,"   bne $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
				else if(!strcmp(temp->code.u.if_type.relop,">"))
                    fprintf(fp,"   bgt $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
				else if(!strcmp(temp->code.u.if_type.relop,"<"))
                    fprintf(fp,"   blt $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
				else if(!strcmp(temp->code.u.if_type.relop,">="))
                    fprintf(fp,"   bge $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
				else if(!strcmp(temp->code.u.if_type.relop,"<="))
                    fprintf(fp,"   ble $t1 ,$t2 ,lable%d\n",temp->code.u.if_type.lable->u.lable_no);
                break;
			case RETURN_IR:
                fprintf(fp,"   move $v0,$t0\n");
                fprintf(fp,"   jr $ra\n");
				break;
			case DEC_IR:{
                opoffset *temp_op=(opoffset *)malloc(sizeof(struct OPOFFSET));
                temp_op->op=temp->code.u.array.op;
                temp_op->offset=sp;
                sp-=temp->code.u.array.size;
                list_add_before(&opoff,&temp_op->queue);
				break;
            }
			case ARG_IR:

				break;
			case CALL_IR:
                fprintf(fp,"   addi $sp,$sp,%d\n",sp);
                fprintf(fp,"   sw $ra,0($sp)\n");
                fprintf(fp,"   jal %s\n",temp->code.u.call_fun.name);
                fprintf(fp,"   move $t0,$v0\n");
                fprintf(fp,"   lw $ra,0($sp)\n");
                fprintf(fp,"   addi $sp,$sp,%d\n",-sp);
                set_offset(temp->code.u.call_fun.returnop);
				break;
			case PARAM_IR:
				break;
			case READ_IR:
                fprintf(fp,"   addi $sp,$sp,%d\n",sp);
                fprintf(fp,"   sw $ra,0($sp)\n");
                fprintf(fp,"   jal read\n");
                fprintf(fp,"   lw $ra,0($sp)\n");
                fprintf(fp,"   addi $sp,$sp,%d\n",-sp);
                fprintf(fp,"   move $t0,$v0\n");
                fprintf(fp,"   sw $t0,%d($sp)\n",set_offset(temp->code.u.op));
				break;
			case WRITE_IR:
                fprintf(fp,"   lw $t1,%d($sp)\n",get_offset(temp->code.u.op));
                fprintf(fp,"   move $a0,$t1\n");
                fprintf(fp,"   addi $sp,$sp,%d\n",sp);
                fprintf(fp,"   sw $ra,0($sp)\n");
                fprintf(fp,"   jal write\n");
                fprintf(fp,"   lw $ra,0($sp)\n");
                fprintf(fp,"   addi $sp,$sp,%d\n",-sp);
				break;
			default:
				printf("InterCodes kind type!!!\n");
				break;
		}
        temp=list_entry(temp->queue.next,struct InterCodes,queue);
	}
	fclose(fp);
}

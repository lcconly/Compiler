.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
   li $v0, 4
   la $a0, _prompt
   syscall
   li $v0, 5
   syscall
   jr $ra

write:
   li $v0, 1
   syscall
   li $v0, 4
   la $a0, _ret
   syscall
   move $v0, $0
   jr $ra
main:
   li $t0,1
   sw $t0,-32($sp)
   li $t0,3
   sw $t0,-36($sp)
   li $t0,13
   sw $t0,-40($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-44($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-48($sp)
   lw $t1,-48($sp)
   lw $t2,-40($sp)
   add $t0,$t1,$t2
   sw $t0,-52($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-56($sp)
   lw $t1,-56($sp)
   lw $t2,-40($sp)
   add $t0,$t1,$t2
   sw $t0,-60($sp)
   li $t0,42
   sw $t0,-64($sp)
   li $t0,0
   sw $t0,-68($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-72($sp)
   lw $t1,-72($sp)
   lw $t2,-40($sp)
   add $t0,$t1,$t2
   sw $t0,-76($sp)
   lw $t1,-76($sp)
   lw $t2,-44($sp)
   sub $t0,$t1,$t2
   sw $t0,-80($sp)
   lw $t1,-80($sp)
   lw $t2,-52($sp)
   sub $t0,$t1,$t2
   sw $t0,-84($sp)
   lw $t1,-84($sp)
   lw $t2,-60($sp)
   add $t0,$t1,$t2
   sw $t0,-60($sp)
lable0:
   lw $t1,-36($sp)
   lw $t2,-32($sp)
   sub $t0,$t1,$t2
   sw $t0,-88($sp)
   lw $t1,-60($sp)
   lw $t2,-88($sp)
   bgt $t1 ,$t2 ,lable1
   j lable2
lable1:
   lw $t1,-60($sp)
   lw $t2,-36($sp)
   sub $t0,$t1,$t2
   sw $t0,-92($sp)
   lw $t1,-32($sp)
   mul $t0,$t1,2
   sw $t0,-96($sp)
   lw $t1,-92($sp)
   lw $t2,-96($sp)
   add $t0,$t1,$t2
   sw $t0,-100($sp)
   lw $t1,-40($sp)
   lw $t2,-44($sp)
   mul $t0,$t1,$t2
   sw $t0,-104($sp)
   lw $t1,-100($sp)
   lw $t2,-104($sp)
   add $t0,$t1,$t2
   sw $t0,-108($sp)
   lw $t1,-108($sp)
   lw $t2,-60($sp)
   sub $t0,$t1,$t2
   sw $t0,-112($sp)
   lw $t1,-68($sp)
   mul $t0,$t1,4
   sw $t0,-116($sp)
   lw $t1,-64($sp)
   lw $t2,-116($sp)
   add $t0,$t1,$t2
   sw $t0,-120($sp)
   lw $t1,-120($sp)
   addi $t0,$t1,12
   sw $t0,-64($sp)
   lw $t1,-68($sp)
   addi $t0,$t1,1
   sw $t0,-68($sp)
   lw $t1,-68($sp)
   div $t0,$t1,3
   mflo $t0
   sw $t0,-124($sp)
   lw $t1,-124($sp)
   mul $t0,$t1,3
   sw $t0,-128($sp)
   lw $t1,-68($sp)
   lw $t2,-128($sp)
   sub $t0,$t1,$t2
   sw $t0,-132($sp)
   lw $t1,-32($sp)
   lw $t2,-32($sp)
   sub $t0,$t1,$t2
   sw $t0,-136($sp)
   lw $t1,-136($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-140($sp)
   lw $t1,-140($sp)
   lw $t2,-36($sp)
   sub $t0,$t1,$t2
   sw $t0,-144($sp)
   lw $t1,-132($sp)
   lw $t2,-144($sp)
   beq $t1 ,$t2 ,lable3
   j lable4
lable3:
   lw $t1,-60($sp)
   addi $t0,$t1,2
   sw $t0,-60($sp)
lable4:
   lw $t1,-60($sp)
   sub $t0,$t1,1
   sw $t0,-60($sp)
   j lable0
lable2:
   lw $t1,-64($sp)
   move $a0,$t1
   addi $sp,$sp,-148
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,148
   lw $t0,-64($sp)
   sw $t0,-68($sp)
lable5:
   lw $t1,-64($sp)
   li $t2,1222
   bge $t1 ,$t2 ,lable6
   j lable7
lable6:
   lw $t1,-64($sp)
   addi $t0,$t1,1024
   sw $t0,-68($sp)
   lw $t1,-64($sp)
   sub $t0,$t1,1
   sw $t0,-64($sp)
   lw $t0,-64($sp)
   sw $t0,-68($sp)
   j lable5
lable7:
   lw $t1,-64($sp)
   move $a0,$t1
   addi $sp,$sp,-148
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,148
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-32($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-36($sp)
   lw $t1,-32($sp)
   lw $t2,-36($sp)
   add $t0,$t1,$t2
   sw $t0,-40($sp)
   lw $t1,-40($sp)
   move $a0,$t1
   addi $sp,$sp,-148
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,148
   li $t0,0
   move $v0,$t0
   jr $ra

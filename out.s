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
power:
   move $t0,$a0
   sw $t0,-32($sp)
   move $t0,$a1
   sw $t0,-36($sp)
   li $t0,1
   sw $t0,-40($sp)
lable0:
   lw $t1,-36($sp)
   li $t2,0
   bgt $t1 ,$t2 ,lable1
   j lable2
lable1:
   lw $t1,-40($sp)
   lw $t2,-32($sp)
   mul $t0,$t1,$t2
   sw $t0,-40($sp)
   lw $t1,-36($sp)
   sub $t0,$t1,1
   sw $t0,-36($sp)
   j lable0
lable2:
   move $v0,$t0
   jr $ra
mod:
   move $t0,$a0
   sw $t0,-44($sp)
   move $t0,$a1
   sw $t0,-48($sp)
   lw $t1,-44($sp)
   lw $t2,-48($sp)
   div $t0,$t1,$t2
   mflo $t0
   sw $t0,-52($sp)
   lw $t1,-52($sp)
   lw $t2,-48($sp)
   mul $t0,$t1,$t2
   sw $t0,-56($sp)
   lw $t1,-44($sp)
   lw $t2,-56($sp)
   sub $t0,$t1,$t2
   sw $t0,-60($sp)
   move $v0,$t0
   jr $ra
getNumDigits:
   move $t0,$a0
   sw $t0,-64($sp)
   li $t0,0
   sw $t0,-68($sp)
   lw $t1,-64($sp)
   li $t2,0
   blt $t1 ,$t2 ,lable3
   j lable4
lable3:
   move $v0,$t0
   jr $ra
lable4:
lable5:
   lw $t1,-64($sp)
   li $t2,0
   bgt $t1 ,$t2 ,lable6
   j lable7
lable6:
   lw $t1,-64($sp)
   div $t0,$t1,10
   mflo $t0
   sw $t0,-64($sp)
   lw $t1,-68($sp)
   addi $t0,$t1,1
   sw $t0,-68($sp)
   j lable5
lable7:
   move $v0,$t0
   jr $ra
isNarcissistic:
   move $t0,$a0
   sw $t0,-72($sp)
   lw $a0,-72($sp)
   addi $sp,$sp,-76
   sw $ra,0($sp)
   jal getNumDigits
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,76
   sw $t0,-76($sp)
   lw $t0,-76($sp)
   sw $t0,-80($sp)
   li $t0,0
   sw $t0,-84($sp)
   lw $t0,-72($sp)
   sw $t0,-88($sp)
lable8:
   lw $t1,-88($sp)
   li $t2,0
   bgt $t1 ,$t2 ,lable9
   j lable10
lable9:
   lw $a1,-1($sp)
   lw $a0,-88($sp)
   addi $sp,$sp,-92
   sw $ra,0($sp)
   jal mod
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,92
   sw $t0,-92($sp)
   lw $t0,-92($sp)
   sw $t0,-96($sp)
   lw $t1,-88($sp)
   lw $t2,-96($sp)
   sub $t0,$t1,$t2
   sw $t0,-100($sp)
   lw $t1,-100($sp)
   div $t0,$t1,10
   mflo $t0
   sw $t0,-88($sp)
   lw $a1,-80($sp)
   lw $a0,-96($sp)
   addi $sp,$sp,-104
   sw $ra,0($sp)
   jal power
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,104
   sw $t0,-104($sp)
   lw $t1,-84($sp)
   lw $t2,-104($sp)
   add $t0,$t1,$t2
   sw $t0,-84($sp)
   j lable8
lable10:
   lw $t1,-84($sp)
   lw $t2,-72($sp)
   beq $t1 ,$t2 ,lable11
   j lable12
lable11:
   move $v0,$t0
   jr $ra
   j lable13
lable12:
   move $v0,$t0
   jr $ra
lable13:
printHexDigit:
   move $t0,$a0
   sw $t0,-108($sp)
   lw $t1,-108($sp)
   li $t2,10
   blt $t1 ,$t2 ,lable14
   j lable15
lable14:
   lw $t1,-108($sp)
   move $a0,$t1
   addi $sp,$sp,-112
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,112
   j lable16
lable15:
   li $t1,0
   move $a0,$t1
   addi $sp,$sp,-112
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,112
lable16:
   move $v0,$t0
   jr $ra
printHex:
   move $t0,$a0
   sw $t0,-112($sp)
   li $t0,0
   sw $t0,-132($sp)
lable17:
   lw $t1,-132($sp)
   li $t2,4
   blt $t1 ,$t2 ,lable18
   j lable19
lable18:
   lw $t1,-132($sp)
   mul $t0,$t1,4
   sw $t0,-136($sp)
   la $t1,-56($sp)
   lw $t2,-136($sp)
   sub $t0,$t1,$t2
   sw $t0,-140($sp)
   lw $a1,-1($sp)
   lw $a0,-112($sp)
   addi $sp,$sp,-144
   sw $ra,0($sp)
   jal mod
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,144
   sw $t0,-144($sp)
   lw $t0,-140($sp)
   lw $t1,-144($sp)
   sw $t1,0($t0)
   sw $t0,-140($sp)
   lw $t1,-112($sp)
   div $t0,$t1,16
   mflo $t0
   sw $t0,-112($sp)
   lw $t1,-132($sp)
   addi $t0,$t1,1
   sw $t0,-132($sp)
   j lable17
lable19:
   li $t0,3
   sw $t0,-132($sp)
lable20:
   lw $t1,-132($sp)
   li $t2,0
   bge $t1 ,$t2 ,lable21
   j lable22
lable21:
   lw $t1,-132($sp)
   mul $t0,$t1,4
   sw $t0,-148($sp)
   la $t1,-56($sp)
   lw $t2,-148($sp)
   sub $t0,$t1,$t2
   sw $t0,-152($sp)
   lw $a0,-152($sp)
   addi $sp,$sp,-156
   sw $ra,0($sp)
   jal printHexDigit
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,156
   sw $t0,-156($sp)
   lw $t1,-132($sp)
   sub $t0,$t1,1
   sw $t0,-132($sp)
   j lable20
lable22:
   move $v0,$t0
   jr $ra
main:
   li $t0,0
   sw $t0,-160($sp)
   li $t0,9400
   sw $t0,-164($sp)
lable23:
   lw $t1,-164($sp)
   li $t2,9500
   blt $t1 ,$t2 ,lable24
   j lable25
lable24:
   lw $a0,-164($sp)
   addi $sp,$sp,-168
   sw $ra,0($sp)
   jal isNarcissistic
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,168
   sw $t0,-168($sp)
   lw $t1,-168($sp)
   li $t2,1
   beq $t1 ,$t2 ,lable26
   j lable27
lable26:
   lw $a0,-164($sp)
   addi $sp,$sp,-172
   sw $ra,0($sp)
   jal printHex
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,172
   sw $t0,-172($sp)
   lw $t1,-160($sp)
   addi $t0,$t1,1
   sw $t0,-160($sp)
lable27:
   lw $t1,-164($sp)
   addi $t0,$t1,1
   sw $t0,-164($sp)
   j lable23
lable25:
   move $v0,$t0
   jr $ra

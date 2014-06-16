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
sort:
   move $t0,$a0
   sw $t0,-32($sp)
   li $t0,0
   sw $t0,-436($sp)
   li $t0,0
   sw $t0,-440($sp)
lable0:
   lw $t1,-436($sp)
   lw $t2,-32($sp)
   blt $t1 ,$t2 ,lable1
   j lable2
lable1:
   lw $t1,-436($sp)
   mul $t0,$t1,4
   sw $t0,-444($sp)
   la $t1,-36($sp)
   lw $t2,-444($sp)
   sub $t0,$t1,$t2
   sw $t0,-448($sp)
   lw $t1,-436($sp)
   mul $t0,$t1,2
   sw $t0,-452($sp)
   li $t1,100
   lw $t2,-452($sp)
   sub $t0,$t1,$t2
   sw $t0,-456($sp)
   lw $t0,-448($sp)
   lw $t1,-456($sp)
   sw $t1,0($t0)
   sw $t0,-448($sp)
   lw $t1,-436($sp)
   addi $t0,$t1,1
   sw $t0,-436($sp)
   j lable0
lable2:
   li $t0,0
   sw $t0,-436($sp)
lable3:
   lw $t1,-436($sp)
   lw $t2,-32($sp)
   blt $t1 ,$t2 ,lable4
   j lable5
lable4:
   li $t0,0
   sw $t0,-440($sp)
lable6:
   lw $t1,-440($sp)
   lw $t2,-436($sp)
   blt $t1 ,$t2 ,lable7
   j lable8
lable7:
   lw $t1,-436($sp)
   mul $t0,$t1,4
   sw $t0,-460($sp)
   la $t1,-36($sp)
   lw $t2,-460($sp)
   sub $t0,$t1,$t2
   sw $t0,-464($sp)
   lw $t1,-440($sp)
   mul $t0,$t1,4
   sw $t0,-468($sp)
   la $t1,-36($sp)
   lw $t2,-468($sp)
   sub $t0,$t1,$t2
   sw $t0,-472($sp)
   lw $t3,-464($sp)
   lw $t1,0($t3)
   lw $t3,-472($sp)
   lw $t2,0($t3)
   blt $t1 ,$t2 ,lable9
   j lable10
lable9:
   lw $t1,-436($sp)
   mul $t0,$t1,4
   sw $t0,-476($sp)
   la $t1,-36($sp)
   lw $t2,-476($sp)
   sub $t0,$t1,$t2
   sw $t0,-480($sp)
   lw $t1,-480($sp)
   lw $t0,0($t1)
   sw $t0,-484($sp)
   lw $t1,-436($sp)
   mul $t0,$t1,4
   sw $t0,-488($sp)
   la $t1,-36($sp)
   lw $t2,-488($sp)
   sub $t0,$t1,$t2
   sw $t0,-492($sp)
   lw $t1,-440($sp)
   mul $t0,$t1,4
   sw $t0,-496($sp)
   la $t1,-36($sp)
   lw $t2,-496($sp)
   sub $t0,$t1,$t2
   sw $t0,-500($sp)
   lw $t0,-492($sp)
   lw $t2,-500($sp)
   lw $t1,0($t2)
   sw $t1,0($t0)
   sw $t0,-492($sp)
   lw $t1,-440($sp)
   mul $t0,$t1,4
   sw $t0,-504($sp)
   la $t1,-36($sp)
   lw $t2,-504($sp)
   sub $t0,$t1,$t2
   sw $t0,-508($sp)
   lw $t0,-508($sp)
   lw $t1,-484($sp)
   sw $t1,0($t0)
   sw $t0,-508($sp)
lable10:
   lw $t1,-440($sp)
   addi $t0,$t1,1
   sw $t0,-440($sp)
   j lable6
lable8:
   lw $t1,-436($sp)
   addi $t0,$t1,1
   sw $t0,-436($sp)
   j lable3
lable5:
   li $t0,0
   sw $t0,-436($sp)
lable11:
   lw $t1,-436($sp)
   lw $t2,-32($sp)
   blt $t1 ,$t2 ,lable12
   j lable13
lable12:
   lw $t1,-436($sp)
   mul $t0,$t1,4
   sw $t0,-512($sp)
   la $t1,-36($sp)
   lw $t2,-512($sp)
   sub $t0,$t1,$t2
   sw $t0,-516($sp)
   lw $t2,-516($sp)
   lw $t1,0($t2)
   move $a0,$t1
   addi $sp,$sp,-520
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,520
   lw $t1,-436($sp)
   addi $t0,$t1,1
   sw $t0,-436($sp)
   j lable11
lable13:
   li $t0,0
   move $v0,$t0
   jr $ra
main:
   addi $sp,$sp,-520
   sw $ra,0($sp)
   jal read
   lw $ra,0($sp)
   addi $sp,$sp,520
   move $t0,$v0
   sw $t0,-520($sp)
   lw $t1,-520($sp)
   li $t2,100
   bge $t1 ,$t2 ,lable14
   j lable15
lable14:
   li $t1,-1
   move $a0,$t1
   addi $sp,$sp,-524
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,524
   j lable16
lable15:
   lw $a0,-520($sp)
   addi $sp,$sp,-524
   sw $ra,0($sp)
   jal sort
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,524
   sw $t0,-524($sp)
lable16:
   li $t0,0
   move $v0,$t0
   jr $ra

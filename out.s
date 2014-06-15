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
   la $t1,-32($sp)
   sub $t0,$t1,0
   sw $t0,-44($sp)
   lw $t0,-44($sp)
   li $t1,5
   sw $t1,0($t0)
   sw $t0,-44($sp)
   la $t1,-32($sp)
   sub $t0,$t1,4
   sw $t0,-48($sp)
   lw $t0,-48($sp)
   li $t1,8
   sw $t1,0($t0)
   sw $t0,-48($sp)
   la $t1,-32($sp)
   sub $t0,$t1,8
   sw $t0,-52($sp)
   lw $t0,-52($sp)
   li $t1,6
   sw $t1,0($t0)
   sw $t0,-52($sp)
   la $t1,-32($sp)
   sub $t0,$t1,0
   sw $t0,-56($sp)
   la $t1,-32($sp)
   sub $t0,$t1,4
   sw $t0,-60($sp)
   lw $t1,-56($sp)
   lw $t2,-60($sp)
   add $t0,$t1,$t2
   sw $t0,-64($sp)
   la $t1,-32($sp)
   sub $t0,$t1,8
   sw $t0,-68($sp)
   lw $t1,-64($sp)
   lw $t2,-68($sp)
   add $t0,$t1,$t2
   sw $t0,-72($sp)
   lw $t1,-72($sp)
   move $a0,$t1
   addi $sp,$sp,-76
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,76
   move $v0,$t0
   jr $ra

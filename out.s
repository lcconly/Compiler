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
inc:
   lw $t1,-1($sp)
   addi $t0,$t1,1
   sw $t0,-32($sp)
   move $v0,$t0
   jr $ra
main:
   li $t0,10
   sw $t0,-36($sp)
   addi $sp,$sp,-40
   sw $ra,0($sp)
   jal inc
   move $t0,$v0
   lw $ra,0($sp)
   addi $sp,$sp,40
   lw $t0,-40($sp)
   sw $t0,-36($sp)
   lw $t1,-36($sp)
   move $a0,$t1
   addi $sp,$sp,-44
   sw $ra,0($sp)
   jal write
   lw $ra,0($sp)
   addi $sp,$sp,44
   move $v0,$t0
   jr $ra

main:
    li $v0, 4
    la $a0, prom
    syscall
	li $v0, 5
	syscall
	move $t0, $v0
	li $t1, 1
	
for:
	bgt $t1, $t0, end
	move $a0, $t1
	li $v0, 1
	syscall
	la $a0, newline
	li $v0, 4
	syscall
	addi $t1, 1
	j for
	
end:
	jr $ra
	
.data
prom:
    .asciiz "Enter a number: "
newline:
	.asciiz "\n"
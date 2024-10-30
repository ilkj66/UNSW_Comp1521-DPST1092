main:
	li $v0, 4
	la $a0, prom
	syscall
	li $v0, 5
	syscall
	move $t0, $v0 #number
	li $v0, 1 #i
	move $t1, $v0
loop:
	bge $t1, $t0, end
	li $v0, 7
	rem $t2, $t1, $v0
	li $v0, 11
	rem $t3, $t1, $v0
	beqz $t2, print
	beqz $t3, print
	addi $t1, 1
	j loop
print:
	li $v0, 1
	move $a0, $t1
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	addi $t1, 1
	j loop
end:
	jr $ra
	
	
.data
prom:
	.asciiz "Enter a number: "
newline:
	.asciiz "\n"

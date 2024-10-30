main:
	la $a0, prom1
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $t0, $v0 #starting num. 
	la $a0, prom2
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $t1, $v0 #stopping num. 
	la $a0, prom3
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $t2, $v0 #step size. 
	move $t3, $t0 #i
	bgt $t1, $t0, if2
	bgez $t2, end
	
loop:
	blt $t3, $t1, end
	li $v0, 1
	move $a0, $t3
	syscall
	la $a0, newline
	li $v0, 4
	syscall
	add $t3, $t3, $t2
	j loop
	
if2:
	bltz $t2, end
loop2:
	bgt $t3, $t1, end
	li $v0, 1
	move $a0, $t3
	syscall
	la $a0, newline
	li $v0, 4
	syscall
	add $t3, $t3, $t2
	j loop2

end:
	jr $ra
	
	
.data
prom1:
	.asciiz "Enter the starting number: "
prom2:
	.asciiz "Enter the stopping number: "
prom3:
	.asciiz "Enter the step size: "
newline:
	.asciiz "\n"
	
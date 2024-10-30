
main:
	la $a0, prom
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	move $t0, $v0 #num
	blt $t0, 50, FL
	blt $t0, 65, PS
	blt $t0, 75, CR
	blt $t0, 85, DN
    la $a0, hd
	li $v0, 4
	syscall
	j end
FL:
	la $a0, fl
	li $v0, 4
	syscall
	j end
PS:
	la $a0, ps
	li $v0, 4
	syscall
	j end
CR:
	la $a0, cr
	li $v0, 4
	syscall
	j end
DN:
	la $a0, dn
	li $v0, 4
	syscall
	j end

end:
	jr $ra     
.data
prom:
	.asciiz "Enter a mark: "
fl:
	.asciiz "FL\n"
ps:
	.asciiz "PS\n"
cr:
	.asciiz "CR\n"
dn:
	.asciiz "DN\n"
hd:
	.asciiz "HD\n"

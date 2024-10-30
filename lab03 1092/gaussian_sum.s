main:
        la $a0, prom1
        li $v0, 4
        syscall
        li $v0, 5
        syscall
        move $t0, $v0 #number1
        la $a0, promp2
        li $v0, 4
        syscall
        li $v0, 5
        syscall
        move $t1, $v0 #number2
        sub $t2, $t1, $t0
        addi $t2, $t2, 1
        add $t3, $t0, $t1
        mul $t4, $t2, $t3
        li $v0, 2
        div $t4, $t4, $v0 #gaussian_sum
        li $v0, 4
        la $a0, promp3
        syscall
        move $a0, $t0
        li $v0, 1
        syscall
        li $v0, 4
        la $a0, promp4
        syscall
        move $a0, $t1
        li $v0, 1
        syscall
        li $v0, 4
        la $a0, promp5
        syscall
        move $a0, $t4
        li $v0, 1
        syscall
        li $v0, 4
        la $a0, promp6
        syscall
        jr $ra



.data
prom1:
        .asciiz "Enter first number: "
promp2:
        .asciiz "Enter second number: "
promp3:
        .asciiz "The sum of all numbers between "
promp4:
        .asciiz " and "
promp5:
        .asciiz " (inclusive) is: "
promp6:
        .asciiz "\n"
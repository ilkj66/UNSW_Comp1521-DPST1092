# Reads a line and prints whether it is a palindrome or not

LINE_LEN = 256

########################################################################
# .TEXT <main>
main:
	# Locals:
	#   - ...

	li	$v0, 4				# syscall 4: print_string
	la	$a0, line_prompt_str		#
	syscall					# printf("Enter a line of input: ");

	li	$v0, 8				# syscall 8: read_string
	la	$a0, line			#
	la	$a1, LINE_LEN			#
	syscall					# fgets(buffer, LINE_LEN, stdin)

	li $t0, 0
	la $s0, line
l:
	add $t8, $t0, $s0
	lb $t5, 0($t8)
	beq $t5, 0, next
	addi $t0, $t0, 1
	j l
next:
	li $t1, 0
	sub $t2, $t0, 2

loop:
	bge $t1, $t2, end_part
	
	la $s1, line
	add $s1, $s1, $t1
	lb $t6, 0($s1)

	la $s2, line
	add $s2, $s2, $t2
	lb $t7, 0($s2)

	beq $t6, $t7, add

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_not_palindrome_str	#
	syscall					# printf("not palindrome\n");

	j return

add:
	addi $t1, $t1, 1
	addi $t2, $t2, -1
	j loop

end_part:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_palindrome_str	#
	syscall					# printf("palindrome\n");

return:
	li	$v0, 0
	jr	$ra				# return 0;


########################################################################
# .DATA
	.data
# String literals
line_prompt_str:
	.asciiz	"Enter a line of input: "
result_not_palindrome_str:
	.asciiz	"not palindrome\n"
result_palindrome_str:
	.asciiz	"palindrome\n"

# Line of input stored here
line:
	.space	LINE_LEN
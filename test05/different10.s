# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#   - $t0: int x
	#   - $t2: int n_seen
	#   - $t3: temporary result
	#   - $t4: temporary result

slow_loop__init:
	li	$t2, 0				# n_seen = 0;
slow_loop__cond:
	bge	$t2, ARRAY_LEN, slow_loop__end	# while (n_seen < ARRAY_LEN) {

slow_loop__body:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, prompt_str			#
	syscall					#   printf("Enter a number: ");

	li	$v0, 5				#   syscall 5: read_int
	syscall					#
	move	$t0, $v0			#   scanf("%d", &x);
	li $t1, 0
find_loop:
	bge $t1, $t2, find_loop_end
	la $t5, numbers
	mul $t6, $t1, 4
	add $t5, $t5, $t6
	lw $v1, 0($t5)
	beq $t0, $v1, find_loop_step
	addi $t1, $t1, 1
	j find_loop
find_loop_step:
	j slow_loop__cond
find_loop_end:

	bne $t1, $t2, not_equal
	la $t5, numbers
	mul	$t3, $t2, 4			#
	add $t5, $t5, $t3
	sw	$t0, 0($t5)		#   numbers[n_seen] = x;

	addi	$t2, $t2, 1			#   n_seen++;
not_equal:
	j	slow_loop__cond
slow_loop__end:					# }

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_str			#
	syscall					# printf("10th different number was: ");

	li	$v0, 1				# syscall 1: print_int
	move	$a0, $t0			#
	syscall					# printf("%d", x);

	li	$v0, 11				# syscall 11: print_char	
	li	$a0, '\n'			#
	syscall					# putchar('\n');

	li	$v0, 0
	jr	$ra				# return 0;

########################################################################
# .DATA
	.data
numbers:
	.space 4 * ARRAY_LEN			# int numbers[ARRAY_LEN];
prompt_str:
	.asciiz	"Enter a number: "
result_str:
	.asciiz	"10th different number was: "

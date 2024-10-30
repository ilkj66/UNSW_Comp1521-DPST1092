# Reads 10 numbers into an array
# printing 0 if they are in non-decreasing order
# or 1 otherwise.
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  TODO: add your registers here

scan_loop__init:
	li	$t0, 0				# i = 0;
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#   
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	sw	$v0, ($t2)			#   scanf("%d", &numbers[i]);

	addi	$t0, $t0, 1			#   i++;
	j	scan_loop__cond			# }
scan_loop__end:

	# TODO: add your code here!
        li	$t0, 1
	li	$t4, 0				# flag = 0 (assume non-decreasing order)
	la	$t2, numbers		# load base address of numbers array
	lw	$t5, 0($t2)			# previous = numbers[0]

check_loop__cond:
	bge	$t0, ARRAY_LEN, check_loop__end	# while (i < ARRAY_LEN) {

check_loop__body:
	mul	$t1, $t0, 4			# calculate &numbers[i] == numbers + 4 * i
	add	$t1, $t2, $t1		# add offset to base address
	lw	$t3, 0($t1)			# current = numbers[i]

	blt	$t3, $t5, set_flag	# if (current < previous) flag = 1;
	move	$t5, $t3			# previous = current;

	addi	$t0, $t0, 1		# i++;
	j	check_loop__cond	# }

set_flag:
	li	$t4, 1				# flag = 1

check_loop__end:

	# Print the result
	move	$a0, $t4			# move flag to $a0 for printing
	li	$v0, 1				# syscall 1: print_int
	syscall					# printf("%d", flag);

	li	$v0, 11				# syscall for exit
        la      $a0, '\n'
	syscall
        jr      $ra
	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
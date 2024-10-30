# Reads 10 numbers into an array, bubblesorts them
# and then prints the 10 numbers
# Yiming HE   1/6/2024

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
        #  - $t3: swapped
        #  - $t4: word's address
        #  - $t5: numbers[i]
        #  - $t6: numbers[i - 1]
	#  TODO: add your registers here

scan_loop__init:
	li	$t0, 0				# i = 0
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
	b	scan_loop__cond			# }
scan_loop__end:

	# TODO: add your code here!
        li      $t3, 1                          #swapped == 1
swap_begin:
        bne     $t3, 1, print_loop__init
        li      $t3, 0                          #swapped == 0
        li      $t0, 1                          # i == 0
swap_in_loop1:
        bge     $t0, ARRAY_LEN, swap_in_loop1_end
        la      $t4, numbers
	mul	$v0, $t0, 4
	add 	$t4, $t4, $v0
	lw	$t5, ($t4)			#numbers[i]
	lw	$t6, -4($t4)			#numbers[i - 1]
	bge	$t5, $t6, no_swap
	sw	$t5, -4($t4)
	sw	$t6, ($t4)
	li	$t3, 1
no_swap:
	addi	$t0, $t0, 1
	j 	swap_in_loop1

swap_in_loop1_end:
	j	swap_begin


print_loop__init:
	li	$t0, 0				# i = 0
print_loop__cond:
	bge	$t0, ARRAY_LEN, print_loop__end	# while (i < ARRAY_LEN) {

print_loop__body:
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	lw	$a0, ($t2)			#
	li	$v0, 1				#   syscall 1: print_int
	syscall					#   printf("%d", numbers[i]);

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');

	addi	$t0, $t0, 1			#   i++
	b	print_loop__cond		# }
print_loop__end:
	
	li	$v0, 0
	jr	$ra				# return 0;


	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};





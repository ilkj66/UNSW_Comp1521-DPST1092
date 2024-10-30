# return the number of peaks in an array of integers
#
# A peak is a value that is both preceded and succeeded
# by a value smaller than itself
#
# ie:
# Both the value before and the value after the current value
# are smaller than the current value
#
# eg:
# [1, 3, 2, 5, 4, 4, 9, 0, 1, -9, -5, -7]
#     ^     ^        ^     ^       ^
# The value 3, 5, 9, 1, -5 are all peaks in this array
# So your function should return 5

.text
.globl final_q4

final_q4:
	# YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE


	# REPLACE THIS LINE WITH YOUR CODE
	move	$t0, $a0	# array
	move	$t1, $a1	# length
	li	$v0, 0			#total
	li  $t2, 1			#i

	addi $t3, $t1, -1	#length - 1

loop:
    bge     $t2, $t3, end_loop # if (i >= length - 1) break

    sll     $t4, $t2, 2   # t4 = i * 4 (byte offset for array indexing)
    sub     $t5, $t2, 1   # t5 = i - 1
    sll     $t5, $t5, 2   # t5 = (i - 1) * 4
    add     $t5, $t0, $t5 # t5 = &array[i - 1]
    lw      $t6, 0($t5)   # t6 = array[i - 1]
    add     $t4, $t0, $t4 # t4 = &array[i]
    lw      $t7, 0($t4)   # t7 = array[i]
    addi    $t8, $t2, 1   # t8 = i + 1
    sll     $t8, $t8, 2   # t8 = (i + 1) * 4
    add     $t8, $t0, $t8 # t8 = &array[i + 1]
    lw      $t9, 0($t8)   # t9 = array[i + 1]

    ble     $t7, $t6, next # if (array[i] <= array[i - 1]) continue
    ble     $t7, $t9, next # if (array[i] <= array[i + 1]) continue

    addi    $v0, $v0, 1   # total++

next:
    addi    $t2, $t2, 1   # i++

    j       loop

end_loop:



	jr	$ra


# ADD ANY EXTRA FUNCTIONS BELOW THIS LINE

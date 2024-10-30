# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# Yiming He 5/6/2024

# Constants
ARRAY_LEN = 1000

main:

    # Initialize registers and memory
    la $t2, prime             # Load address of prime array into $t2
    li $t0, 2                 # int i = 2
    li $t1, 1                 # Value to initialize prime array to 1

initialize_array:
    bge $t0, ARRAY_LEN, sieve_start
    sb $t1, 0($t2)            # prime[i] = 1
    addi $t2, $t2, 1          # Move to the next byte in prime array
    addi $t0, $t0, 1          # Increment i
    j initialize_array

sieve_start:
    li $t0, 2                 # int i = 2

outer_loop:
    bge $t0, ARRAY_LEN, end
    la $t2, prime             # Load address of prime array
    mul $t6, $t0, 1           # $t6 = i (byte offset)
    add $t2, $t2, $t6         # $t2 = &prime[i]
    lb $t3, 0($t2)            # Load prime[i]

    beq $t3, 0, outer_loop_end
    # Print the prime number
    move $a0, $t0
    li $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    # Mark multiples of the prime number as not prime
    mul $t4, $t0, 2           # int j = 2 * i

inner_loop:
    bge $t4, ARRAY_LEN, outer_loop_end
    la $t2, prime             # Load address of prime array
    mul $t6, $t4, 1           # $t6 = j (byte offset)
    add $t2, $t2, $t6         # $t2 = &prime[j]
    li $t5, 0                 # Value to mark as not prime
    sb $t5, 0($t2)            # prime[j] = 0
    add $t4, $t4, $t0         # j += i
    j inner_loop

outer_loop_end:
    addi $t0, $t0, 1          # i++
    j outer_loop

end:
    li $v0, 10                # Exit program
    syscall

    .data
prime:
    .space ARRAY_LEN          # uint8_t prime[ARRAY_LEN];
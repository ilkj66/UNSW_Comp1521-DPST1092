# Yicing HE 8/6/2024

########################################################################
# .DATA
# Here are some handy strings for use in your code.

 .data
prompt_str:
 .asciiz "Enter a random seed: "
result_str:
 .asciiz "The random result is: "


########################################################################
# .TEXT <main>
 .text
main:

 # Args: void
 # Returns: int
 #
 # Frame: [...]
 # Uses:  [...]
 # Clobbers: [...]
 #
 # Locals:
 #   - ...
 #
 # Structure:
 #   - main
 #     -> [prologue]
 #     -> [body]
 #     -> [epilogue]

main__prologue:
 begin
 # TODO: add code to set up your stack frame here 
 push $ra


main__body:
 # TODO: complete your function body here
 la $a0, prompt_str
 li $v0, 4
 syscall

 li $v0, 5
 syscall
 move $t0, $v0  #t0 -- random seed

#seed_rand(random_seed)
 move $a0, $t0
 jal seed_rand

#int value = rand(100)
 li $a0, 100
 jal rand
 move $a1, $v0  #a1(value) = rand(100)

#value = add_rand
 move $a0, $a1
 jal add_rand
 move $a1, $v0  #a1(value) = add_rand(value)

#value = sub_rand
 move $a0, $a1
 jal sub_rand
 move $a1, $v0  #a1(value) = sub_rand(value)

#value = seq_rand
 move $a0, $a1
 jal seq_rand
 move $a1, $v0  #a1(value) = seq_rand(value)

#printf
 li $v0, 4
 la $a0, result_str
 syscall

 li $v0, 1
 move $a0, $a1
 syscall

 li $v0, 11
 la $a0, '\n'
 syscall


main__epilogue:
 # TODO: add code to clean up stack frame here
 pop $ra
 end

 li $v0, 0
 jr $ra    # return 0;

########################################################################
# .TEXT <add_rand>
 .text
add_rand:
 # Args:
 #   - $a0: int value
 # Returns: int
 #
 # Frame: [...]
 # Uses:  [...]
 # Clobbers: [...]
 #
 # Locals:
 #   - ...
 #
 # Structure:
 #   - add_rand
 #     -> [prologue]
 #     -> [body]
 #     -> [epilogue]

add_rand__prologue:
 begin

 # TODO: add code to set up your stack frame here
    push $ra
    push $s0

add_rand__body:
# input value a0 
 # TODO: complete your function body here
    move $s0, $a0   #s0 == (input) value
    li $a0, 0xFFFF  #??????????????
    jal rand
    move $a2, $v0  #a2 -- rand (0xffff)
    add $v0, $s0, $a2  #v0(return) = s0(value) + a2[rand(0xffff)]

add_rand__epilogue:
 
 # TODO: add code to clean up stack frame here
    pop $s0
    pop $ra
    end

 jr $ra


########################################################################
# .TEXT <sub_rand>
 .text
sub_rand:
 # Args:
 #   - $a0: int value
 # Returns: int
 #
 # Frame: [...]
 # Uses:  [...]
 # Clobbers: [...]
 #
 # Locals:
 #   - ...
 #
 # Structure:
 #   - sub_rand
 #     -> [prologue]
 #     -> [body]
 #     -> [epilogue]

sub_rand__prologue:
 begin

 # TODO: add code to set up your stack frame here
 push $ra

sub_rand__body:

 # TODO: complete your function body here
    move $s1, $a0  #s1 = input value
    move $a0, $a1  #a0 = a1(value)
    jal rand
    move $a2, $v0 
    sub $v0, $s1, $a2

sub_rand__epilogue:
 
 # TODO: add code to clean up stack frame here
    pop $ra
    end

 jr $ra

########################################################################
# .TEXT <seq_rand>
 .text
seq_rand:
 # Args:
 #   - $a0: int value
 # Returns: int
 #
 # Frame: [...]
 # Uses:  [...]
 # Clobbers: [...]
 #
 # Locals:
 #   - ...
 #
 # Structure:
 #   - seq_rand
 #     -> [prologue]
 #     -> [body]
 #     -> [epilogue]

seq_rand__prologue:
 begin

 # TODO: add code to set up your stack frame here
 push $ra

seq_rand__body:

 # TODO: complete your function body here
    move $s2, $a0  #s2 = input value
    li $a0, 100
    jal rand
    move $a3, $v0  #a3(limit) = v0 [rand(100)]

    li $t2, 0
loop:
    bge $t2, $a3, return_value 

    move $a0, $s2
    jal add_rand
    
    move $s2, $v0

    addi $t2, $t2, 1
    j loop

return_value:

seq_rand__epilogue:
 
 # TODO: add code to clean up stack frame here
    pop $ra
    end
 
 jr $ra



##
## The following are two utility functions, provided for you.
##
## You don't need to modify any of the following,
## but you may find it useful to read through.
## You'll be calling these functions from your code.
##

OFFLINE_SEED = 0x7F10FB5B

########################################################################
# .DATA
 .data
 
# int random_seed;
 .align 2
random_seed:
 .space 4


########################################################################
# .TEXT <seed_rand>
 .text
seed_rand:
# DO NOT CHANGE THIS FUNCTION

 # Args:
 #   - $a0: unsigned int seed
 # Returns: void
 #
 # Frame: []
 # Uses:  [$a0, $t0]
 # Clobbers: [$t0]
 #
 # Locals:
 #   - $t0: offline_seed
 #
 # Structure:
 #   - seed_rand

 li $t0, OFFLINE_SEED  # const unsigned int offline_seed = OFFLINE_SEED;
 xor $t0, $a0   # random_seed = seed ^ offline_seed;
 sw $t0, random_seed

 jr $ra    # return;

########################################################################
# .TEXT <rand>
 .text
rand:
# DO NOT CHANGE THIS FUNCTION

 # Args:
 #   - $a0: unsigned int n
 # Returns:
 #   - $v0: int
 #
 # Frame:    []
 # Uses:     [$a0, $v0, $t0]
 # Clobbers: [$v0, $t0]
 #
 # Locals:
 #   - $t0: int rand
 #
 # Structure:
 #   - rand

 lw $t0, random_seed   # unsigned int rand = random_seed;
 multu $t0, 0x5bd1e995    # rand *= 0x5bd1e995;
 mflo $t0
 addiu $t0, 12345         # rand += 12345;
 sw $t0, random_seed   # random_seed = rand;

 remu $v0, $t0, $a0    
 jr $ra                # return rand % n;
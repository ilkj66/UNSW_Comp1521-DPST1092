# Reads a 4-byte value and reverses the byte order, then prints it

########################################################################
# .TEXT <main>
main:
	# Locals:
	#	- $t0: int computer_bytes
	#	- $t1: int byte_mask
	#   - $v0: network_bytes
	#	- Add your registers here!


	li	$v0, 5		# scanf("%d", &x); #network_bytes
	syscall

	#
	# Your code here!
	#
	li $t0, 0  #computer_bytes
	li $t1, 0xFF  #byte_mask

	and $t2, $t1, $v0 
	sll $t2, $t2, 24
	or $t0, $t0, $t2

	sll $t3, $t1, 8
	and $t2, $t3, $v0
	sll $t2, $t2, 8
	or $t0, $t0, $t2

	sll $t3, $t1, 16
	and $t2, $t3, $v0
	srl $t2, $t2, 8
	or $t0, $t0, $t2

	sll $t3, $t1, 24
	and $t2, $t3, $v0
	srl $t2, $t2, 24
	or $t0, $t0, $t2

	move	$a0, $t0	# printf("%d\n", x);
	li	$v0, 1
	syscall

	move $a0, $v0

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

main__end:
	li	$v0, 0		# return 0;
	jr	$ra

    #computer_bytes |= (network_bytes & byte_mask) << 24;
    #computer_bytes |= (network_bytes & (byte_mask << 8)) << 8;
    #computer_bytes |= (network_bytes & (byte_mask << 16)) >> 8;
    #computer_bytes |= (network_bytes & (byte_mask << 24)) >> 24;
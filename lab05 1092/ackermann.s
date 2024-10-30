########################################################################
# .DATA
# Here are some handy strings for use in your code.
	.data
prompt_m_str:	.asciiz	"Enter m: "
prompt_n_str:	.asciiz	"Enter n: "
result_str_1:	.asciiz	"Ackermann("
result_str_2:	.asciiz	", "
result_str_3:	.asciiz	") = "

########################################################################
# .TEXT <main>
	.text
main:

	# Args: void
	# Returns: int
	#
	# Frame:	[...]
	# Uses: 	[...]
	# Clobbers:	[...]
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

	# TODO: set up your stack frame

main__body:

	# TODO: add your function body here

main__epilogue:

	# TODO: clean up your stack frame

	li	$v0, 0
	jr	$ra			# return 0;

########################################################################
# .TEXT <ackermann>
	.text
ackermann:

	# Args:
	#   - $a0: int m
	#   - $a1: int n
	# Returns: int
	#
	# Frame:	[]
	# Uses: 	[]
	# Clobbers:	[]
	#
	# Locals:
	#   - .
	#
	# Structure:
	#   - ackermann
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

ackermann__prologue:

	# TODO: set up your stack frame

ackermann__body:

	# TODO: add your function body here

ackermann__epilogue:

	# TODO: clean up your stack frame

	jr	$ra

########################################################################
# .DATA
	.data
err_full_object_str:
	.asciiz "error: tried to add fn to full object\n"

err_find_fn_str:
	.asciiz "error: could not find function\n"

########################################################################
# .TEXT <make_object>
	.text
make_object:
	
	# Args:
	#   - $a0: void *data
	#   - $a1: size_t fn_capacity
	#
	# Returns: object
	#
	# Registers:
	#   - Frame:	[...]
	#   - Uses:	[...]
	#   - Clobbers:	[...]
	#
	# Locals:
	#   - ...
	#
	# Structure
	#   - make_object
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

make_object__prologue:
	

make_object__body:
	

make_object__epilogue:
	
	jr	$ra

########################################################################
# .TEXT <obj_define>
	.text
obj_define:	

	# Args:
	#   - $a0: void *data
	#   - $a1: char *fn_name
	#   - $a2: void *fn_ptr
	#
	# Returns: object
	#
	# Registers:
	#   - Frame:	[...]
	#   - Uses:	[...]
	#   - Clobbers:	[...]
	#
	# Locals:
	#   - ...
	#
	# Structure
	#   - obj_define
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

obj_define__prologue:
	

obj_define__body:
	

obj_define__else:
	

obj_define__epilogue:
	
	jr	$ra

########################################################################
# .TEXT <obj_call>
	.text
obj_call:

	# Args:
	#   - $a0: object obj
	#   - $a1: char *fn
	#
	# Returns: void *
	#
	# Registers:
	#   - Frame:	[$ra, $s0, $s1, $s2, $s3, $s4]
	#   - Uses:	[$v0, $a0, $a1, $s0, $s1, $s2, $s3, $s4]
	#   - Clobbers:	[$v0, $a0, $a1]
	#
	# Locals:
	#   - $s0: object obj
	#   - $s1: char *fn
	#   - $s2: size_t len
	#   - $s3: size_t i
	#   - $s4: void *fn_ptr(void *)
	#
	# Structure
	#   - obj_call
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

obj_call__prologue:
	
obj_call__body:
	

obj_call__epilogue:

	jr	$ra

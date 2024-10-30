################################################################################
# COMP1092 24T2 -- Assignment 1 -- Railroad Runners
#
#
# This program was written by Yiming HE (z5528914)
# on 17/6/2024
#
#
#
################################################################################

#![tabsize(4)]

# ------------------------------------------------------------------------------
#                                   Constants
# ------------------------------------------------------------------------------

# -------------------------------- C Constants ---------------------------------
TRUE = 1
FALSE = 0

JUMP_KEY = 'w'
LEFT_KEY = 'a'
CROUCH_KEY = 's'
RIGHT_KEY = 'd'
TICK_KEY = '\''       ###################################################
QUIT_KEY = 'q'

ACTION_DURATION = 3
CHUNK_DURATION = 10

SCROLL_SCORE_BONUS = 1
TRAIN_SCORE_BONUS = 1
BARRIER_SCORE_BONUS = 2
CASH_SCORE_BONUS = 3

MAP_HEIGHT = 20
MAP_WIDTH = 5
PLAYER_ROW = 1

PLAYER_RUNNING = 0
PLAYER_CROUCHING = 1
PLAYER_JUMPING = 2

STARTING_COLUMN = MAP_WIDTH / 2

TRAIN_CHAR = 't'
BARRIER_CHAR = 'b'
CASH_CHAR = 'c'
EMPTY_CHAR = ' '
WALL_CHAR = 'w'
RAIL_EDGE = '|'

SAFE_CHUNK_INDEX = 0
NUM_CHUNKS = 14

# --------------------- Useful Offset and Size Constants -----------------------

# struct BlockSpawner offsets
BLOCK_SPAWNER_NEXT_BLOCK_OFFSET = 0
BLOCK_SPAWNER_SAFE_COLUMN_OFFSET = 20
BLOCK_SPAWNER_SIZE = 24

# struct Player offsets
PLAYER_COLUMN_OFFSET = 0
PLAYER_STATE_OFFSET = 4
PLAYER_ACTION_TICKS_LEFT_OFFSET = 8
PLAYER_ON_TRAIN_OFFSET = 12
PLAYER_SCORE_OFFSET = 16
PLAYER_SIZE = 20

SIZEOF_PTR = 4


# ------------------------------------------------------------------------------
#                                 Data Segment
# ------------------------------------------------------------------------------
	.data

# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

# ----------------------------- String Constants -------------------------------

print_welcome__msg_1:
	.asciiz "Welcome to Railroad Runners!\n"
print_welcome__msg_2_1:
	.asciiz "Use the following keys to control your character: ("
print_welcome__msg_2_2:
	.asciiz "):\n"
print_welcome__msg_3:
	.asciiz ": Move left\n"
print_welcome__msg_4:
	.asciiz ": Move right\n"
print_welcome__msg_5_1:
	.asciiz ": Crouch ("
print_welcome__msg_5_2:
	.asciiz ")\n"
print_welcome__msg_6_1:
	.asciiz ": Jump ("
print_welcome__msg_6_2:
	.asciiz ")\n"
print_welcome__msg_7_1:
	.asciiz "or press "
print_welcome__msg_7_2:
	.asciiz " to continue moving forward.\n"
print_welcome__msg_8_1:
	.asciiz "You must crouch under barriers ("
print_welcome__msg_8_2:
	.asciiz ")\n"
print_welcome__msg_9_1:
	.asciiz "and jump over trains ("
print_welcome__msg_9_2:
	.asciiz ").\n"
print_welcome__msg_10_1:
	.asciiz "You should avoid walls ("
print_welcome__msg_10_2:
	.asciiz ") and collect cash ("
print_welcome__msg_10_3:
	.asciiz ").\n"
print_welcome__msg_11:
	.asciiz "On top of collecting cash, running on trains and going under barriers will get you extra points.\n"
print_welcome__msg_12_1:
	.asciiz "When you've had enough, press "
print_welcome__msg_12_2:
	.asciiz " to quit. Have fun!\n"

get_command__invalid_input_msg:
	.asciiz "Invalid input!\n"

main__game_over_msg:
	.asciiz "Game over, thanks for playing 😊!\n"

display_game__score_msg:
	.asciiz "Score: "

handle_collision__barrier_msg:
	.asciiz "💥 You ran into a barrier! 😵\n"
handle_collision__train_msg:
	.asciiz "💥 You ran into a train! 😵\n"
handle_collision__wall_msg:
	.asciiz "💥 You ran into a wall! 😵\n"

maybe_pick_new_chunk__column_msg_1:
	.asciiz "Column "
maybe_pick_new_chunk__column_msg_2:
	.asciiz ": "
maybe_pick_new_chunk__safe_msg:
	.asciiz "New safe column: "

get_seed__prompt_msg:
	.asciiz "Enter a non-zero number for the seed: "
get_seed__prompt_invalid_msg:
	.asciiz "Invalid seed!\n"
get_seed__set_msg:
	.asciiz "Seed set to "

TRAIN_SPRITE:
	.asciiz "🚆"
BARRIER_SPRITE:
	.asciiz "🚧"
CASH_SPRITE:
	.asciiz "💵"
EMPTY_SPRITE:
	.asciiz "  "
WALL_SPRITE:
	.asciiz "🧱"

PLAYER_RUNNING_SPRITE:
	.asciiz "🏃"
PLAYER_CROUCHING_SPRITE:
	.asciiz "🧎"
PLAYER_JUMPING_SPRITE:
	.asciiz "🤸"

# ------------------------------- Chunk Layouts --------------------------------

SAFE_CHUNK: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_1: # char[]
	.byte EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, WALL_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, BARRIER_CHAR, '\0',
CHUNK_2: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_3: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_4: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_5: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, TRAIN_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_6: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, CASH_CHAR, EMPTY_CHAR, BARRIER_CHAR, '\0'
CHUNK_7: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, '\0',
CHUNK_8: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, '\0',
CHUNK_9: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_10: # char[]
	.byte CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, '\0',
CHUNK_11: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_12: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_13: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, '\0',

CHUNKS:	# char*[]
	.word SAFE_CHUNK, CHUNK_1, CHUNK_2, CHUNK_3, CHUNK_4, CHUNK_5, CHUNK_6, CHUNK_7, CHUNK_8, CHUNK_9, CHUNK_10, CHUNK_11, CHUNK_12, CHUNK_13

# ----------------------------- Global Variables -------------------------------

g_block_spawner: # struct BlockSpawner
	# char *next_block[MAP_WIDTH], offset 0
	.word 0, 0, 0, 0, 0
	# int safe_column, offset 20
	.word STARTING_COLUMN

g_map: # char[MAP_HEIGHT][MAP_WIDTH]
	.space MAP_HEIGHT * MAP_WIDTH

g_player: # struct Player
	# int column, offset 0
	.word STARTING_COLUMN
	# int state, offset 4
	.word PLAYER_RUNNING
	# int action_ticks_left, offset 8
	.word 0
	# int on_train, offset 12
	.word FALSE
	# int score, offset 16
	.word 0

g_rng_state: # unsigned
	.word 1

# !!! Reminder to not not add to or modify any of the above !!!
# !!! strings or any other part of the data segment.        !!!

# ------------------------------------------------------------------------------
#                                 Text Segment
# ------------------------------------------------------------------------------
	.text

############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################

################################################################################
#
# Implement the following functions,
# and check these boxes as you finish implementing each function.
#
#  SUBSET 0
#  - [ ] print_welcome
#  SUBSET 1
#  - [ ] get_command
#  - [ ] main
#  - [ ] init_map
#  SUBSET 2
#  - [ ] run_game
#  - [ ] display_game
#  - [ ] maybe_print_player
#  - [ ] handle_command
#  SUBSET 3
#  - [ ] handle_collision
#  - [ ] maybe_pick_new_chunk
#  - [ ] do_tick
#  PROVIDED
#  - [X] get_seed
#  - [X] rng
#  - [X] read_char
################################################################################

################################################################################
# .TEXT <print_welcome>
print_welcome:
	# Subset:   0
	#
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   print_welcome
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

print_welcome__prologue:
print_welcome__body:
	# TODO: implement `print_welcome` here!
	la $a0, print_welcome__msg_1
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_2_1
	li $v0, 4
	syscall

	la $a0, PLAYER_RUNNING_SPRITE
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_2_2
	li $v0, 4
	syscall

	la $a0, LEFT_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_3
	li $v0, 4
	syscall

	la $a0, RIGHT_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_4
	li $v0, 4
	syscall

	la $a0, CROUCH_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_5_1
	li $v0, 4
	syscall

	la $a0, PLAYER_CROUCHING_SPRITE
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_5_2
	li $v0, 4
	syscall

	la $a0, JUMP_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_6_1
	li $v0, 4
	syscall

	la $a0, PLAYER_JUMPING_SPRITE
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_6_2
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_7_1
	li $v0, 4
	syscall

	la $a0, TICK_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_7_2
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_8_1
	li $v0, 4
	syscall

	la $a0, BARRIER_SPRITE
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_8_2
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_9_1
	li $v0, 4
	syscall

	la $a0, TRAIN_SPRITE
	la $v0, 4
	syscall

	la $a0, print_welcome__msg_9_2
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_10_1
	li $v0, 4
	syscall

	la $a0, WALL_SPRITE
	la $v0, 4
	syscall

	la $a0, print_welcome__msg_10_2
	li $v0, 4
	syscall

	la $a0, CASH_SPRITE
	la $v0, 4
	syscall

	la $a0, print_welcome__msg_10_3
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_11
	li $v0, 4
	syscall

	la $a0, print_welcome__msg_12_1
	li $v0, 4
	syscall

	la $a0, QUIT_KEY
	li $v0, 11
	syscall

	la $a0, print_welcome__msg_12_2
	li $v0, 4
	syscall

print_welcome__epilogue:
	jr	$ra


################################################################################
# .TEXT <get_command>
	.text
get_command:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: char
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   get_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

get_command__prologue:
	push $ra
get_command__body:										#while (TRUE) {

	jal read_char										#char input = read_char();
	
	li $t0, QUIT_KEY
    beq $v0, $t0, get_command__epilogue					#input == QUIT_KEY
    li $t0, JUMP_KEY
    beq $v0, $t0, get_command__epilogue					#input == JUMP_KEY
    li $t0, LEFT_KEY
    beq $v0, $t0, get_command__epilogue					#input == LEFT_KEY
    li $t0, CROUCH_KEY
    beq $v0, $t0, get_command__epilogue					#input == CROUCH_KEY 
    li $t0, RIGHT_KEY
    beq $v0, $t0, get_command__epilogue					#input == RIGHT_KEY 
    li $t0, TICK_KEY
    beq $v0, $t0, get_command__epilogue					#input == TICK_KEY

	la $a0, get_command__invalid_input_msg
	li $v0, 4											#printf("Invalid input!\n");
	syscall
	j get_command__body
get_command__epilogue:
	
	pop $ra
	jr	$ra


################################################################################
# .TEXT <main>
	.text
main:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - -$t0, g_map
	#	- -$t1, &g_player
	#   - -$t2, g_block_spawner
	#   - -$t4, output of the run_game function
	#
	# Structure:
	#   main
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

push $ra
 

main__body:

 jal print_welcome				#print_welcome();
 jal get_seed					#get_seed();

 la $a0, g_map
 jal init_map					#init_map(g_map);
								
 li $t0, g_map					#do {
 la $t1, g_player
 move $a0, $t0
 move $a1, $t1
 jal display_game 						#display_game(g_map, &g_player);

do_while_loop:

 jal get_command
 move $t3, $v0


 li $t0, g_map
 la $t1, g_player
 la $t2, g_block_spawner

 move $a0, $t0
 move $a1, $t1
 move $a2, $t2
 move $a3, $t3
 
 jal run_game				#} while (run_game(g_map, &g_player, &g_block_spawner, get_command())
 move $t4, $v0

 beq $t4, 0, print_game_over 
 
 li $t0, g_map
 la $t1, g_player
 
 move $a0, $t0
 move $a1, $t1
 jal display_game     #set all registers and go to diaplay function

 j do_while_loop

print_game_over:
 la $a0, main__game_over_msg
 li $v0, 4
 syscall

main__epilogue:
 pop $ra
 li $v0, 0
 jr $ra


################################################################################
# .TEXT <init_map>
	.text
init_map:
	# Subset:   1
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#     $t0: i
	#     $t1: j
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   -$t0: i
	#	-$t1: j
	#	-$t2: MAP_WIDTH
	#	-$t3: address of the map[i][j]
	#	-$t4: empty_char
	#	-$t5: address of special map place
	#
	# Structure:
	#   init_map
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

init_map__prologue:
init_map__body:
	li $t0, 0									#int i = 0
outer_loop:
	li $t1, MAP_HEIGHT
	bge $t0, $t1, outer_loop_end				#for ( ;i < MAP_HEIGHT; )
	li $t1, 0									#int j = 0
inner_loop:
	li $t2, MAP_WIDTH
	bge $t1, $t2, outer_loop_step				#for ( ;j < MAP_WIDTH; )
	mul $t2, $t0, MAP_WIDTH
	add $t2, $t2, $t1
	add $t3, $t2, $a0							#get the address

	li $t4, EMPTY_CHAR
	sb $t4, 0($t3)						#store byte

	addi $t1, $t1, 1					#++j
	j inner_loop
outer_loop_step:
	addi $t0, $t0, 1					#++i
	j outer_loop
outer_loop_end:

	addi $t5, $a0, 30
	li $t4, WALL_CHAR
	sb $t4, 0($t5)					#map[6][0] = WALL_CHAR;
	addi $t5, $t5, 1
	li $t4, TRAIN_CHAR
	sb $t4, 0($t5)					# map[6][1] = TRAIN_CHAR;
	addi $t5, $t5, 1
	li $t4, CASH_CHAR
	sb $t4, 0($t5)					#map[6][2] = CASH_CHAR;
	addi $t5, $t5, 10
	li $t4, BARRIER_CHAR
	sb $t4, 0($t5)					#map[8][2] = BARRIER_CHAR;
	

init_map__epilogue:
	move $v0, $a0					#set return value
	jr	$ra


################################################################################
# .TEXT <run_game>
	.text
run_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#   - $s0: save register
	#   - $s1: save register
	#   - $s2: save register
	#   - $s3: save register
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   run_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

run_game__prologue:
	addi $sp, $sp, -20   #push stack out of the memory
    sw $ra, 16($sp)       
    sw $s0, 12($sp)        
    sw $s1, 8($sp)         
    sw $s2, 4($sp)      
    sw $s3, 0($sp)

run_game__body:     
	move $s0, $a0
	move $s1, $a1
	move $s2, $a2
	move $s3, $a3			#store the register to $s ,make it unchange

	li $t0, QUIT_KEY
	bne $a3, $t0, not_return_false	#if (input == QUIT_KEY) {
	li $v0, FALSE
	j run_game__epilogue		#return FALSE;

not_return_false:
	
	jal handle_command			#handle_command(map, player, block_spawner, input);

	move $a0, $s0
	move $a1, $s1
	jal handle_collision		#return handle_collision(map, player);


run_game__epilogue:
	lw $s3, 0($sp) 
    lw $s2, 4($sp)         
    lw $s1, 8($sp)         
    lw $s0, 12($sp)        
    lw $ra, 16($sp)      
    addi $sp, $sp, 20    #push back into memory
    jr $ra        


################################################################################
# .TEXT <display_game>
	.text
display_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   -$t2: map_width
	#   -$t5: mapchar
	#   -$t6: compare char
	#
	# Structure:
	#   display_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

display_game__prologue:
	addi $sp, $sp, -20
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)

display_game__body:
	move $s2, $a0                 # map
    move $s3, $a1                # player
	
	li $s0, MAP_HEIGHT
	addi $s0, $s0, -1            # int i = MAP_HEIGHT - 1

display_game_outer_loop:
	blt $s0, 0, display_game__epilogue
	li $s1, 0                    # int j = 0

display_game_inner_loop:
	li $t2, MAP_WIDTH
	bge $s1, $t2, display_game_outer_loop_update
	li $a0, RAIL_EDGE
	li $v0, 11
	syscall                      # putchar(RAIL_EDGE)

	move $a0, $s3                # player
	move $a1, $s0                # i
	move $a2, $s1                # j
	jal maybe_print_player       # maybe_print_player(player, i, j)
	beq $v0, 1, put_rail_edge

	mul $t4, $s0, MAP_WIDTH
	add $t4, $t4, $s1
	la $t3, g_map
	add $t3, $t3, $t4
	lb $t5, 0($t3)               # char map_char = map[i][j]

check_empty_char:
	li $t6, EMPTY_CHAR
	bne $t5, $t6, check_barrier_char  # map_char == EMPTY_CHAR
	li $a0, EMPTY_SPRITE
	li $v0, 4
	syscall                      # printf(EMPTY_SPRITE)
	j put_rail_edge

check_barrier_char:
	li $t6, BARRIER_CHAR
	bne $t5, $t6, check_train_sprite  # map_char == BARRIER_CHAR
	li $a0, BARRIER_SPRITE
	li $v0, 4
	syscall                      # printf(BARRIER_SPRITE)
	j put_rail_edge

check_train_sprite:
	li $t6, TRAIN_CHAR
	bne $t5, $t6, check_cash_sprite   # map_char == TRAIN_CHAR
	li $a0, TRAIN_SPRITE
	li $v0, 4
	syscall                      # printf(TRAIN_SPRITE)
	j put_rail_edge

check_cash_sprite:
	li $t6, CASH_CHAR
	bne $t5, $t6, check_wall_sprite    # map_char == CASH_CHAR
	li $a0, CASH_SPRITE
	li $v0, 4
	syscall                      # printf(CASH_SPRITE)
	j put_rail_edge

check_wall_sprite:
	li $t6, WALL_CHAR
	bne $t5, $t6, put_rail_edge       # map_char == WALL_CHAR
	li $a0, WALL_SPRITE
	li $v0, 4
	syscall                      # printf(WALL_SPRITE)
	j put_rail_edge

put_rail_edge:
	li $a0, RAIL_EDGE
	li $v0, 11
	syscall                      # putchar(RAIL_EDGE)

	addi $s1, $s1, 1
	j display_game_inner_loop

display_game_outer_loop_update:
	addi $s0, $s0, -1
	li $a0, '\n'
	li $v0, 11
	syscall                      # putchar('\n')
	j display_game_outer_loop

display_game__epilogue:
	la $a0, display_game__score_msg
	li $v0, 4
	syscall                      # printf("Score: ")
	la $t5, g_player
	lw $a0, 16($t5)              # player->score (assuming score is at offset 16)
	li $v0, 1
	syscall                      # printf("%d", player->score)
	li $a0, '\n'
	li $v0, 11
	syscall                      # putchar('\n')
	lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
	lw $s3, 16($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 20
	jr $ra 

################################################################################
# .TEXT <maybe_print_player>
	.text
maybe_print_player:
	# Subset:   2
	#
	# Args:
	#   - $a0: struct Player *player
	#   - $a1: int row
	#   - $a2: int column
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   -$t4: player->column
	#   -$t5:  player->state
	#
	# Structure:
	#   maybe_print_player
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_print_player__prologue:
	addi $sp, $sp, -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
	sw $s2, 12($sp)

maybe_print_player__body:
	move $s0, $a0               # player
	move $s1, $a1               # row
	move $s2, $a2               # column

	li $t0, PLAYER_ROW
	bne $s1, $t0, return_false  		# if (row != PLAYER_ROW) return FALSE;
	lw $t4, 0($s0)              # player->column
	bne $s2, $t4, return_false  		# if (column != player->column) return FALSE;
	lw $t5, 4($s0)              # player->state

	li $v0, PLAYER_RUNNING
	bne $t5, $v0, check_player_crouching
	la $a0, PLAYER_RUNNING_SPRITE
	li $v0, 4
	syscall                     # printf(PLAYER_RUNNING_SPRITE)
	j return_true

check_player_crouching:
	li $v0, PLAYER_CROUCHING
	bne $t5, $v0, check_player_jumping
	la $a0, PLAYER_CROUCHING_SPRITE
	li $v0, 4
	syscall                     # printf(PLAYER_CROUCHING_SPRITE)
	j return_true

check_player_jumping:
	li $v0, PLAYER_JUMPING
	bne $t5, $v0, return_true
	la $a0, PLAYER_JUMPING_SPRITE
	li $v0, 4
	syscall                     # printf(PLAYER_JUMPING_SPRITE)

return_true:
	li $v0, TRUE
	j maybe_print_player__epilogue

return_false:
	li $v0, FALSE

maybe_print_player__epilogue:
	lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
	lw $s2, 12($sp)
	addi $sp, $sp, 16
	jr $ra

################################################################################
# .TEXT <handle_command>
	.text
handle_command:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   -$t0: address of char
	#   -$t1: left_key
	#   -$t2: map_width
	#   -$t3: player->state
	#   -$t4: action duration
	#
	# Structure:
	#   handle_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]
handle_command__prologue:
	addi $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)

handle_command__body:
	move $s0, $a0					# char map[MAP_HEIGHT][MAP_WIDTH]
	move $s1, $a1					# struct Player *player
	move $s2, $a2					# struct BlockSpawner *block_spawner
	move $s3, $a3					# char input

check_left_key:
	lw $t0, 0($s1)                 
	li $t1, LEFT_KEY
	bne $s3, $t1, check_right_key  # if (input != LEFT_KEY)
	ble $t0, 0, check_right_key    # if (player->column <= 0)
	addi $t0, $t0, -1              # player->column--
	sw $t0, 0($s1)
	j handle_command__epilogue

check_right_key:
	li $t1, RIGHT_KEY
	bne $s3, $t1, check_jump_key   # if (input != RIGHT_KEY)
	li $t2, MAP_WIDTH
	addi $t2, $t2, -1              # MAP_WIDTH - 1
	bge $t0, $t2, check_jump_key   # if (player->column >= MAP_WIDTH - 1)
	addi $t0, $t0, 1               # player->column++
	sw $t0, 0($s1)
	j handle_command__epilogue

check_jump_key:
	lw $t0, 4($s1)                 # load player->state
	li $t1, JUMP_KEY
	bne $s3, $t1, check_crouch_key # if (input != JUMP_KEY)
	li $t2, PLAYER_RUNNING
	bne $t0, $t2, check_crouch_key # if (player->state != PLAYER_RUNNING)
	li $t3, PLAYER_JUMPING
	sw $t3, 4($s1)                 # player->state = PLAYER_JUMPING
	li $t4, ACTION_DURATION
	sw $t4, 8($s1)                 # player->action_ticks_left = ACTION_DURATION
	j handle_command__epilogue

check_crouch_key:
	li $t1, CROUCH_KEY
	bne $s3, $t1, check_tick_key   # if (input != CROUCH_KEY)
	li $t2, PLAYER_RUNNING
	bne $t0, $t2, check_tick_key   # if (player->state != PLAYER_RUNNING)
	li $t3, PLAYER_CROUCHING
	sw $t3, 4($s1)                 # player->state = PLAYER_CROUCHING
	li $t4, ACTION_DURATION
	sw $t4, 8($s1)                 # player->action_ticks_left = ACTION_DURATION
	j handle_command__epilogue

check_tick_key:
	li $t1, TICK_KEY
	bne $s3, $t1, handle_command__epilogue  # if (input != TICK_KEY)
	move $a0, $s0                 # map
	move $a1, $s1                 # player
	move $a2, $s2                 # block_spawner
	jal do_tick

handle_command__epilogue:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	addi $sp, $sp, 20
	jr	$ra


################################################################################
# .TEXT <handle_collision>
	.text
handle_collision:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   -$t0: load different char
	#   -$t3: map_char
	#   -$t4: address
	#   -$t5:player->column
	#   -$t6: player->state
	#   -$t7: PLAYER_CROUCHING
	#   -$t8: player->score
	#
	# Structure:
	#   handle_collision
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_collision__prologue:
    addi $sp, $sp, -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)

handle_collision__body:
    move $s0, $a0                
    move $s1, $a1              
    li $t4, PLAYER_ROW
    mul $t4, $t4, MAP_WIDTH
    lw $t5, 0($s1)               # player->column
    add $t4, $t4, $t5
    add $t4, $t4, $s0            # &map[][]
    lb $t3, 0($t4)               # *map_char

    li $t0, BARRIER_CHAR
    bne $t3, $t0, check_train_char

    lw $t6, 4($s1)               # player->state
    li $t7, PLAYER_CROUCHING
    bne $t6, $t7, barrier_collision

    lw $t8, 16($s1)              # player->score
    addi $t8, $t8, BARRIER_SCORE_BONUS
    sw $t8, 16($s1)              # player->score += BARRIER_SCORE_BONUS
    j continue_execution

barrier_collision:
    la $a0, handle_collision__barrier_msg
    li $v0, 4
    syscall
    li $v0, FALSE
    j handle_collision__epilogue

check_train_char:
    li $t0, TRAIN_CHAR
    bne $t3, $t0, check_train_char_false

    lw $t6, 4($s1)               # player->state
    li $t7, PLAYER_JUMPING
    beq $t6, $t7, set_on_train

    lw $t9, 12($s1)              # player->on_train
    bne $t9, $zero, set_on_train

    la $a0, handle_collision__train_msg
    li $v0, 4
    syscall
    li $v0, FALSE
    j handle_collision__epilogue

set_on_train:
    li $t9, TRUE
    sw $t9, 12($s1)              # player->on_train = TRUE

    li $t7, PLAYER_JUMPING
    bne $t6, $t7, train_bonus

    j continue_execution

train_bonus:
    lw $t8, 16($s1)              # player->score
    addi $t8, $t8, TRAIN_SCORE_BONUS
    sw $t8, 16($s1)              # player->score += TRAIN_SCORE_BONUS
    j continue_execution

check_train_char_false:
	li $t9, FALSE
    sw $t9, 12($s1)
	
check_wall_char:
    li $t0, WALL_CHAR
    bne $t3, $t0, check_cash_char

    la $a0, handle_collision__wall_msg
    li $v0, 4
    syscall
    li $v0, FALSE
    j handle_collision__epilogue

check_cash_char:
    li $t0, CASH_CHAR
    bne $t3, $t0, continue_execution

    lw $t8, 16($s1)              # player->score
    addi $t8, $t8, CASH_SCORE_BONUS
    sw $t8, 16($s1)              # player->score += CASH_SCORE_BONUS
    li $t0, EMPTY_CHAR
    sb $t0, 0($t4)               # *map_char = EMPTY_CHAR

continue_execution:
    li $v0, TRUE

handle_collision__epilogue:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp, 16
    jr $ra



################################################################################
# .TEXT <maybe_pick_new_chunk>
	.text
maybe_pick_new_chunk:
	# Subset:   3
	#
	# Args:
	#   - $a0: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   maybe_pick_new_chunk
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_pick_new_chunk__prologue:
maybe_pick_new_chunk__body:
maybe_pick_new_chunk__epilogue:
	jr	$ra


################################################################################
# .TEXT <do_tick>
	.text
do_tick:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   do_tick
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

do_tick__prologue:
do_tick__body:
do_tick__epilogue:
	jr	$ra

################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
################################################################################

################################################################################
# .TEXT <get_seed>
get_seed:
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    []
	# Uses:     [$v0, $a0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:
	#   - $v0: seed
	#
	# Structure:
	#   get_seed
	#   -> [prologue]
	#     -> body
	#       -> invalid_seed
	#       -> seed_ok
	#   -> [epilogue]

get_seed__prologue:
get_seed__body:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, get_seed__prompt_msg
	syscall					# printf("Enter a non-zero number for the seed: ")

	li	$v0, 5				# syscall 5: read_int
	syscall					# scanf("%d", &seed);
	sw	$v0, g_rng_state		# g_rng_state = seed;

	bnez	$v0, get_seed__seed_ok		# if (seed == 0) {
get_seed__invalid_seed:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, get_seed__prompt_invalid_msg
	syscall					#   printf("Invalid seed!\n");

	li	$v0, 10				#   syscall 10: exit
	li	$a0, 1
	syscall					#   exit(1);

get_seed__seed_ok:				# }
	li	$v0, 4				# sycall 4: print_string
	la	$a0, get_seed__set_msg
	syscall					# printf("Seed set to ");

	li	$v0, 1				# syscall 1: print_int
	lw	$a0, g_rng_state
	syscall					# printf("%d", g_rng_state);

	li	$v0, 11				# syscall 11: print_char
	la	$a0, '\n'
	syscall					# putchar('\n');

get_seed__epilogue:
	jr	$ra				# return;


################################################################################
# .TEXT <rng>
rng:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0, $a0, $t0, $t1, $t2]
	# Clobbers: [$v0, $a0, $t0, $t1, $t2]
	#
	# Locals:
	#   - $t0 = copy of g_rng_state
	#   - $t1 = bit
	#   - $t2 = temporary register for bit operations
	#
	# Structure:
	#   rng
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

rng__prologue:
rng__body:
	lw	$t0, g_rng_state

	srl	$t1, $t0, 31		# g_rng_state >> 31
	srl	$t2, $t0, 30		# g_rng_state >> 30
	xor	$t1, $t2		# bit = (g_rng_state >> 31) ^ (g_rng_state >> 30)

	srl	$t2, $t0, 28		# g_rng_state >> 28
	xor	$t1, $t2		# bit ^= (g_rng_state >> 28)

	srl	$t2, $t0, 0		# g_rng_state >> 0
	xor	$t1, $t2		# bit ^= (g_rng_state >> 0)

	sll	$t1, 31			# bit << 31
	srl	$t0, 1			# g_rng_state >> 1
	or	$t0, $t1		# g_rng_state = (g_rng_state >> 1) | (bit << 31)

	sw	$t0, g_rng_state	# store g_rng_state

	move	$v0, $t0		# return g_rng_state

rng__epilogue:
	jr	$ra


################################################################################
# .TEXT <read_char>
read_char:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0]
	# Clobbers: [$v0]
	#
	# Locals:   None
	#
	# Structure:
	#   read_char
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

read_char__prologue:
read_char__body:
	li	$v0, 12			# syscall 12: read_char
	syscall				# return getchar();

read_char__epilogue:
	jr	$ra

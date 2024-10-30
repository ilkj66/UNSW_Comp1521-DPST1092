EXERCISES	  += space

SRC = space.c space_main.c space_hash.c space_6_bit.c
INCLUDES = space.h

# if you add extra .c files, add them here
SRC += 

# if you add extra .h files, add them here
INCLUDES +=

space:	$(SRC) $(INCLUDES)
	$(CC) $(SRC) -o $@

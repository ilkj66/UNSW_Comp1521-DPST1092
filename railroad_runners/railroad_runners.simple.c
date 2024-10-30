// railroad_runners.simple.c
//
// An adaptation of a popular mobile game involving subways and surfing.
//
// Prior to translating this program into MIPS assembly, you may wish
// to simplify the contents of this file. You can replace complex C
// constructs like loops with constructs which will be easier to translate
// into assembly. To help you check that you haven't altered the behaviour of
// the game, you can run some automated tests using the command
//     1521 autotest railroad_runners.simple
// The simplified C version of this code is not marked.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                                  Constants                                 */
/* -------------------------------------------------------------------------- */

#define TRUE 1
#define FALSE 0

#define PLAYER_RUNNING_SPRITE ("🏃")
#define PLAYER_CROUCHING_SPRITE ("🧎")
#define PLAYER_JUMPING_SPRITE ("🤸")

#define JUMP_KEY ('w')
#define LEFT_KEY ('a')
#define CROUCH_KEY ('s')
#define RIGHT_KEY ('d')
#define TICK_KEY ('\'')
#define QUIT_KEY ('q')

#define ACTION_DURATION (3)
#define CHUNK_DURATION (10)

#define SCROLL_SCORE_BONUS (1)
#define TRAIN_SCORE_BONUS (1)
#define BARRIER_SCORE_BONUS (2)
#define CASH_SCORE_BONUS (3)

#define MAP_HEIGHT (20)
#define MAP_WIDTH (5)
#define PLAYER_ROW (1)

#define PLAYER_RUNNING (0)
#define PLAYER_CROUCHING (1)
#define PLAYER_JUMPING (2)

#define STARTING_COLUMN (MAP_WIDTH / 2)

// Hint: You don't need this string in your MIPS translation.
#define EOF_MESSAGE                                                          \
    ("EOF received. You don't have to handle this case for your assignment " \
     "😊.\n")

#define TRAIN_SPRITE ("🚆")
#define TRAIN_CHAR ('t')
#define BARRIER_SPRITE ("🚧")
#define BARRIER_CHAR ('b')
#define CASH_SPRITE ("💵")
#define CASH_CHAR ('c')
#define EMPTY_SPRITE ("  ")
#define EMPTY_CHAR (' ')
#define WALL_SPRITE ("🧱")
#define WALL_CHAR ('w')
#define RAIL_EDGE ('|')

// Chunks are a sequence of blocks that can spawn in the game.
// A block is just a character, and a chunk is an array of characters with a
// terminating null (just like a normal C string).

// The safe chunk ensure the player always has a path to go through.
char const SAFE_CHUNK[] = {
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR,
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
};
char const CHUNK_1[] = {
    EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR,   WALL_CHAR, CASH_CHAR,
    CASH_CHAR,  CASH_CHAR, BARRIER_CHAR, '\0',
};
char const CHUNK_2[] = {
    CASH_CHAR,  EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, BARRIER_CHAR,
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR,  '\0',
};
char const CHUNK_3[] = {
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR,
    TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
};
char const CHUNK_4[] = {
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR,
    TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, CASH_CHAR,  '\0',
};
char const CHUNK_5[] = {
    EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR,  TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR,
    EMPTY_CHAR, TRAIN_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
};
char const CHUNK_6[] = {
    EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR,  BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR,
    CASH_CHAR,  CASH_CHAR,  EMPTY_CHAR, BARRIER_CHAR, '\0',
};
char const CHUNK_7[] = {
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR,
    WALL_CHAR,  WALL_CHAR,  WALL_CHAR,  WALL_CHAR, '\0',
};
char const CHUNK_8[] = {
    CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR,
    CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, '\0',
};
char const CHUNK_9[] = {
    CASH_CHAR,  EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR,  TRAIN_CHAR,
    TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
};
char const CHUNK_10[] = {
    CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR,
    CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, '\0',
};
char const CHUNK_11[] = {
    EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR,  WALL_CHAR, TRAIN_CHAR,
    TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
};
char const CHUNK_12[] = {
    EMPTY_CHAR,
    EMPTY_CHAR,
    CASH_CHAR,
    '\0',
};
char const CHUNK_13[] = {
    EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, '\0',
};

// Hint: You can ignore `const` for the purposes of MIPS translation.

// A list of all chunks that can spawn in the game.
// Chunk 0 should always be safe chunk.
char const *const CHUNKS[] = {
    SAFE_CHUNK, CHUNK_1, CHUNK_2, CHUNK_3,  CHUNK_4,  CHUNK_5,  CHUNK_6,
    CHUNK_7,    CHUNK_8, CHUNK_9, CHUNK_10, CHUNK_11, CHUNK_12, CHUNK_13,
};
#define SAFE_CHUNK_INDEX (0)
#define NUM_CHUNKS (14)

/* -------------------------------------------------------------------------- */
/*                                    Types                                   */
/* -------------------------------------------------------------------------- */

// A data structure for tracking which blocks to spawn next in each column.
// A block is a char, and a chunk is an array of chars with a terminating null
// character.
struct BlockSpawner {
    // An array of pointers pointing to the next block to spawn in each column.
    // E.g. next_block[0] points to the next block to spawn in the leftmost
    // column, and next_block[1] points to the next block to spawn in the second
    // leftmost column.
    char const *next_block[MAP_WIDTH];
    // Which index is the current safe column
    int safe_column;
};

// A data structure for tracking the state of the player.
struct Player {
    // Which column the player is in.
    int column;
    // The state of the player (running, crouching, jumping).
    int state;
    // How many ticks the player has left in their current action.
    int action_ticks_left;
    // Whether the player is currently on a train.
    int on_train;
    // The player's score.
    int score;
};

/* -------------------------------------------------------------------------- */
/*                              Global Variables                              */
/* -------------------------------------------------------------------------- */

// In a real C program, most of these would be stack variables instead of global
// variables. However, COMP1521 doesn't cover this, so we use global variables
// and pass them around as pointers.

// Global variables are prefixed with `g_`.

// The block spawner.
struct BlockSpawner g_block_spawner = {
    .next_block = {0},
    .safe_column = STARTING_COLUMN,
};

// The game map, (0, 0) is the bottom left corner.
char g_map[MAP_HEIGHT][MAP_WIDTH];

// The current state of the player.
struct Player g_player = {
    .column = STARTING_COLUMN,
    .state = PLAYER_RUNNING,
    .action_ticks_left = 0,
    .on_train = FALSE,
    .score = 0,
};

// Hint: `g_rng_state` is only used in the provided code. You shouldn't have to
// use it directly.

// The random number generator state.
unsigned g_rng_state = 1;

/* -------------------------------------------------------------------------- */
/*                             Function Prototypes                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------- Subset 0 -------------------------------- */
void print_welcome(void);

/* -------------------------------- Subset 1 -------------------------------- */
char get_command(void);
int main(void);
void init_map(char map[MAP_HEIGHT][MAP_WIDTH]);

/* -------------------------------- Subset 2 -------------------------------- */
int run_game(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
             struct BlockSpawner *block_spawner, char input);
void display_game(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player);
int maybe_print_player(struct Player *player, int row, int column);
void handle_command(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
                    struct BlockSpawner *block_spawner, char input);

/* -------------------------------- Subset 3 -------------------------------- */
int handle_collision(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player);
void maybe_pick_new_chunk(struct BlockSpawner *block_spawner);
void do_tick(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
             struct BlockSpawner *block_spawner);

/* -------------------------------- Provided -------------------------------- */
void get_seed(void);
unsigned rng(void);
char read_char(void);

/* -------------------------------------------------------------------------- */
/*                          Function Implementations                          */
/* -------------------------------------------------------------------------- */

// Subset 0
// Print the welcome message.
void print_welcome(void) {
    // Hint: All the strings you need to print have already been defined at the
    // top of the starter code, in the `.data` section.

    printf("Welcome to Railroad Runners!\n");
    printf("Use the following keys to control your character: (%s):\n",
           PLAYER_RUNNING_SPRITE);
    printf("%c: Move left\n", LEFT_KEY);
    printf("%c: Move right\n", RIGHT_KEY);
    printf("%c: Crouch (%s)\n", CROUCH_KEY, PLAYER_CROUCHING_SPRITE);
    printf("%c: Jump (%s)\n", JUMP_KEY, PLAYER_JUMPING_SPRITE);
    printf("or press %c to continue moving forward.\n", TICK_KEY);
    printf("You must crouch under barriers (%s)\n", BARRIER_SPRITE);
    printf("and jump over trains (%s).\n", TRAIN_SPRITE);
    printf("You should avoid walls (%s) and collect cash (%s).\n", WALL_SPRITE,
           CASH_SPRITE);
    printf(
        "On top of collecting cash, running on trains and going under barriers "
        "will get you extra points.\n");
    printf("When you've had enough, press %c to quit. Have fun!\n", QUIT_KEY);
}

// Subset 1
// Basic logic to ensure the user input is valid.
//
// Returns the command the user entered as a character.
char get_command(void) {
    // Loop until the user enters a valid command
    while (TRUE) {
        // Hint: You must translate the below line as a function call,
        //       *not* as a syscall.
        char input = read_char();

        if (input == QUIT_KEY || input == JUMP_KEY || input == LEFT_KEY ||
            input == CROUCH_KEY || input == RIGHT_KEY || input == TICK_KEY) {
            return input;
        }

        printf("Invalid input!\n");
    }
}

// Subset 1
// Entry point for the game, contains the main game loop.
int main(void) {
    // Hint: Any variable prefixed with `g_` is a global variable, and resides
    // in the `.data` section.

    print_welcome();
    get_seed();
    init_map(g_map);

    do {
        display_game(g_map, &g_player);
    } while (run_game(g_map, &g_player, &g_block_spawner, get_command()));

    printf("Game over, thanks for playing 😊!\n");
}

// Subset 1
// Initialise the map to be empty (plus some hard coded things for testing).
//
// Parameters:
// - map: The game map.
void init_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j] = EMPTY_CHAR;
        }
    }

    // Hard code some things onto the map for easier testing.
    map[6][0] = WALL_CHAR;
    map[6][1] = TRAIN_CHAR;
    map[6][2] = CASH_CHAR;
    map[8][2] = BARRIER_CHAR;
}

// Subset 2
// A single iteration of the user's input.
// Most of the work is delegated to handle_command and handle_collision.
//
// Parameters:
// - map: The game map.
// - player: A pointer to the player struct containing its state.
// - block_spawner: A pointer to the struct which tracks which blocks to spawn
//                  next.
// - input: The command the user entered.
//
// Returns FALSE if the user has quit or lost, TRUE otherwise.
int run_game(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
             struct BlockSpawner *block_spawner, char input) {
    if (input == QUIT_KEY) {
        return FALSE;
    }

    handle_command(map, player, block_spawner, input);
    return handle_collision(map, player);
}

// Subset 2
// Display the current state of the game.
//
// Parameters:
// - map: The game map.
// - player: A pointer to the player struct containing its state.
void display_game(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player) {
    for (int i = MAP_HEIGHT - 1; i >= 0; --i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            putchar(RAIL_EDGE);

            if (!maybe_print_player(player, i, j)) {
                char map_char = map[i][j];
                if (map_char == EMPTY_CHAR) {
                    printf(EMPTY_SPRITE);
                } else if (map_char == BARRIER_CHAR) {
                    printf(BARRIER_SPRITE);
                } else if (map_char == TRAIN_CHAR) {
                    printf(TRAIN_SPRITE);
                } else if (map_char == CASH_CHAR) {
                    printf(CASH_SPRITE);
                } else if (map_char == WALL_CHAR) {
                    printf(WALL_SPRITE);
                }
            }

            putchar(RAIL_EDGE);
        }
        putchar('\n');
    }

    // Hint: All struct member offsets have already been defined at the top of
    // the starter code.
    printf("Score: %d\n", player->score);
}

// Subset 2
// Print the player if they are in the given row and column.
//
// Parameters:
// - player: A pointer to the player struct containing its state.
// - row: The row the map printing is up to.
// - column: The column the map printing is up to.
//
// Returns TRUE if the player was printed, FALSE otherwise.
int maybe_print_player(struct Player *player, int row, int column) {
    if (row == PLAYER_ROW && column == player->column) {
        if (player->state == PLAYER_RUNNING) {
            printf(PLAYER_RUNNING_SPRITE);
        } else if (player->state == PLAYER_CROUCHING) {
            printf(PLAYER_CROUCHING_SPRITE);
        } else if (player->state == PLAYER_JUMPING) {
            printf(PLAYER_JUMPING_SPRITE);
        }
        return TRUE;
    }
    return FALSE;
}

// Subset 2
// Handle the user's input, moving and updating the player's state.
//
// Parameters:
// - map: The game map.
// - player: A pointer to the player struct containing its state.
// - block_spawner: A pointer to the struct which tracks which blocks to spawn
//                  next.
// - input: The command the user entered.
void handle_command(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
                    struct BlockSpawner *block_spawner, char input) {
    if (input == LEFT_KEY) {
        if (player->column > 0) {
            --player->column;
        }

    } else if (input == RIGHT_KEY) {
        if (player->column < MAP_WIDTH - 1) {
            ++player->column;
        }

    } else if (input == JUMP_KEY) {
        // Player must be in normal state (running) to jump
        if (player->state == PLAYER_RUNNING) {
            player->state = PLAYER_JUMPING;
            player->action_ticks_left = ACTION_DURATION;
        }

    } else if (input == CROUCH_KEY) {
        // Player must be in normal state (running) to crouch
        if (player->state == PLAYER_RUNNING) {
            player->state = PLAYER_CROUCHING;
            player->action_ticks_left = ACTION_DURATION;
        }

    } else if (input == TICK_KEY) {
        do_tick(map, player, block_spawner);
    }
}

// Subset 3
// Handle the player colliding with things on the map.
//
// Parameters:
// - map: The game map.
// - player: A pointer to the player struct containing its state.
//
// Returns FALSE if the player has lost, TRUE otherwise.
int handle_collision(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player) {
    char *map_char = &map[PLAYER_ROW][player->column];

    if (*map_char == BARRIER_CHAR) {
        // Player must be crouching to pass under a barrier
        if (player->state != PLAYER_CROUCHING) {
            printf("💥 You ran into a barrier! 😵\n");
            return FALSE;
        }

        player->score += BARRIER_SCORE_BONUS;
    }

    if (*map_char == TRAIN_CHAR) {
        // Player must be jumping (or already on a train) to pass over a train
        if (player->state != PLAYER_JUMPING && !player->on_train) {
            printf("💥 You ran into a train! 😵\n");
            return FALSE;
        }

        player->on_train = TRUE;

        // Player mustn't be jumping to get the train bonus
        if (player->state != PLAYER_JUMPING) {
            player->score += TRAIN_SCORE_BONUS;
        }

    } else {
        player->on_train = FALSE;
    }

    if (*map_char == WALL_CHAR) {
        printf("💥 You ran into a wall! 😵\n");
        return FALSE;
    }

    // Cash collection
    if (*map_char == CASH_CHAR) {
        player->score += CASH_SCORE_BONUS;
        *map_char = EMPTY_CHAR;
    }

    return TRUE;
}

// Subset 3
// Pick a new chunk for each column if required. If the safe column has been
// exhausted, randomly override a column to be the safe column.
//
// Parameters:
// - block_spawner: A pointer to the struct which tracks which blocks to spawn
//                  next.
void maybe_pick_new_chunk(struct BlockSpawner *block_spawner) {
    int new_safe_column_required = FALSE;

    // Iterate through each column, checking if we need to choose a new chunk
    for (int column = 0; column < MAP_WIDTH; ++column) {
        char const **next_block_ptr = &block_spawner->next_block[column];
        if (*next_block_ptr && **next_block_ptr) {
            // We still have blocks left to spawn in this chunk, no need to pick
            // a new one
            continue;
        }

        // We've exhausted all the blocks, time to pick a new chunk
        int chunk = rng() % NUM_CHUNKS;
        printf("Column %d: %d\n", column, chunk);
        *next_block_ptr = CHUNKS[chunk];

        if (column == block_spawner->safe_column) {
            // That was the safe column, we need to pick a new one to ensure the
            // game is still (somewhat) playable
            new_safe_column_required = TRUE;
        }
    }

    if (new_safe_column_required) {
        // Pick a new safe column
        int safe_column = rng() % MAP_WIDTH;
        printf("New safe column: %d\n", safe_column);
        block_spawner->safe_column = safe_column;

        block_spawner->next_block[safe_column] = CHUNKS[SAFE_CHUNK_INDEX];
    }
}

// Subset 3
// Move the game forward one tick, scrolling the map down and generating new
// chunks if required.
//
// Globals used:
// - map: The game map.
// - player: A pointer to the player struct containing its state.
// - block_spawner: A pointer to the struct which tracks which blocks to spawn
//                  next.
void do_tick(char map[MAP_HEIGHT][MAP_WIDTH], struct Player *player,
             struct BlockSpawner *block_spawner) {
    if (player->action_ticks_left > 0) {
        --player->action_ticks_left;
    } else {
        player->state = PLAYER_RUNNING;
    }

    player->score += SCROLL_SCORE_BONUS;

    maybe_pick_new_chunk(block_spawner);

    // Move everything down one row
    for (int i = 0; i < MAP_HEIGHT - 1; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            map[i][j] = map[i + 1][j];
        }
    }

    // Use the block spawner to generate the next row
    for (int column = 0; column < MAP_WIDTH; ++column) {
        char const **next_block = &block_spawner->next_block[column];

        // Hint: The next line is equivalent to the following 2 lines:
        // 1. map[MAP_HEIGHT - 1][column] = **next_block;
        // 2. ++*next_block;
        map[MAP_HEIGHT - 1][column] = *(*next_block)++;
    }
}

/* -------------------------------- Provided -------------------------------- */

// Hint: You don't have to understand the how the following functions work, only
// how to use them.

// Generate a random number using a 32 bit linear feedback shift register.
// More information here:
// https://en.wikipedia.org/wiki/Linear-feedback_shift_register.
//
// Mutates rng_state and returns it.
unsigned rng(void) {
    unsigned bit = (g_rng_state >> 31) ^ (g_rng_state >> 30) ^
                   (g_rng_state >> 28) ^ (g_rng_state >> 0);
    g_rng_state = (g_rng_state >> 1) | (bit << 31);
    return g_rng_state;
}

// The following 2 functions help mimic the way mipsy handles input. Their MIPS
// counterparts will look completely different.

// Try to mimic mipsy's read character syscall.
char read_char(void) {
    int c = '\0';
    while ((c = getchar()) != EOF) {
        if (!isspace(c)) {
            return c;
        }
    }

    printf(EOF_MESSAGE);
    exit(EXIT_FAILURE);
}

// Get a seed from the user to initialise the rng state.
void get_seed(void) {
    printf("Enter a non-zero number for the seed: ");
    int scanf_ret = scanf(" %d", &g_rng_state);
    // In MIPS, we can assume the user enters a valid number
    if (scanf_ret == EOF) {
        printf(EOF_MESSAGE);
        exit(EXIT_FAILURE);
    }
    if (g_rng_state == 0 || scanf_ret != 1) {
        printf("Invalid seed!\n");
        exit(EXIT_FAILURE);
    }

    printf("Seed set to %d\n", g_rng_state);

    // scanf leaves a newline in the buffer, so we need to consume it
    getchar();
}

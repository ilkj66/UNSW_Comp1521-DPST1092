// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source files>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        char *source_file = argv[i];
        char output_file[256];
        
        strncpy(output_file, source_file, sizeof(output_file) - 1);
        output_file[sizeof(output_file) - 1] = '\0';  
        char *dot = strrchr(output_file, '.');
        if (dot != NULL && strcmp(dot, ".c") == 0) {
            *dot = '\0';  
        } else {
            fprintf(stderr, "Invalid C source file: %s\n", source_file);
            continue;
        }

        char *spawn_args[] = {DCC_PATH, source_file, "-o", output_file, NULL};

        posix_spawn_file_actions_t actions;
        posix_spawn_file_actions_init(&actions);

        pid_t pid;
        int status;
        
        printf("running the command: \"%s %s -o %s\"\n", DCC_PATH, source_file, output_file);
        
        if (posix_spawn(&pid, DCC_PATH, &actions, NULL, spawn_args, environ) != 0) {
            perror("posix_spawn");
            posix_spawn_file_actions_destroy(&actions);
            continue;
        }

        posix_spawn_file_actions_destroy(&actions);

        if (waitpid(pid, &status, 0) != pid) {
            perror("waitpid");
        } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Command failed with exit code %d: %s %s -o %s\n", 
                    WEXITSTATUS(status), DCC_PATH, source_file, output_file);
        }
    }

    return EXIT_SUCCESS;
}

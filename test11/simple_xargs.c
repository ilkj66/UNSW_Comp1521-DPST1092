#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *command = argv[1];
    char line[1024];

    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline character from the end of the line
        char *newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }

        char *args[] = {command, line, NULL};
        pid_t pid;
        int status;

        if (posix_spawn(&pid, command, NULL, NULL, args, environ) != 0) {
            perror("posix_spawn");
            return EXIT_FAILURE;
        }

        // Wait for the spawned process to complete
        if (waitpid(pid, &status, 0) != pid) {
            perror("waitpid");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
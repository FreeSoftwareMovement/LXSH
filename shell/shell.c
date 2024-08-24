#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "unistd.h"

void read_command(char cmd[], char *par[]) {
    char line[1024];
    int count = 0;
    char *pch;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return;
    }

    line[strcspn(line, "\n")] = 0;  // Remove the newline character

    pch = strtok(line, " ");
    while (pch != NULL) {
        par[count++] = strdup(pch);
        pch = strtok(NULL, " ");
    }

    strcpy(cmd, par[0]);
    par[count] = NULL;
}

void type_prompt() {
    static int first_time = 1;
    if (first_time) {
        const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
        write(STDERR_FILENO, CLEAR_SCREEN_ANSI, strlen(CLEAR_SCREEN_ANSI));
        first_time = 0;
    }
    printf("# ");
}

int main() {
    char cmd[100], command[100], *parameters[20];

    while(1) {
        type_prompt();
        read_command(command, parameters);

        if (strcmp(command, "exit") == 0) {
            break;
        }

        if (fork() != 0) {
            wait(NULL);
        } else {
            // Build the full path to the command in ./bin
            char path[150] = "./bin/";
            strcat(path, command);

            // Execute the command in ./bin
            execv(path, parameters);

            // If execv fails, print an error and exit the child process
            perror("Command execution failed");
            exit(1);
        }
    }

    return 0;
}

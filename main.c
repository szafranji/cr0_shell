#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "cmds/ls.h"

// different colors for different types of files
#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int words_counter(const char *str) {
    int space_count = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == ' ')
            space_count++;
    }
    space_count++;

    return space_count;
}

void cmd_parser(const char *line) {
    char *cmd_name;
    char *arg1;

    cmd_name = strtok(line, " ");
    arg1 = strtok(NULL, " ");
}

void wrong_cmd_error(const char *cmd) {
    printf("cr0_shell:");
    printf( RED " %s " RESET, cmd);
    printf("is not found \n");
    printf("cr0$ > ");
}

void run_cmd_without_args(const char *cmd)  {
    if(strcmp("l", cmd) == 0 || strcmp("ls", cmd) == 0) {
        l();
        printf("cr0$ > ");
    }
    else if(strcmp("ll", cmd) == 0) {
        ll();
        printf("cr0$ > ");
    }
    else {
        wrong_cmd_error(cmd);
    }
}

void parse_input(const char *input_line) {
    if(strlen(input_line) == 0) {
        printf("cr0$ > ");
    }
    else if(strlen(input_line) > 0 && words_counter(input_line) == 1) {
        run_cmd_without_args(input_line);
    }
    else if(strlen(input_line) > 0 && words_counter(input_line) > 1) {
        cmd_parser(input_line);
    }
}

int main(int argc, char **argv) {
    system("clear");
    char line[256];
    do {
        line[strcspn(line, "\n")] = 0;
        parse_input(line);
    } while(fgets(line, sizeof(line), stdin));
}

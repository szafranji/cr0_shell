#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "cmds/built-in/ls.h"
#include "cmds/built-in/cd.h"
#include "cmds/built-in/touch.h"
#include "cmds/built-in/echo.h"

// different colors for different types of files
#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

char *get_current_dir() {
    char whole_current_dir[100];
    char *root_dir = "/";
    getcwd(whole_current_dir, sizeof(whole_current_dir));

    if(strcmp("/", whole_current_dir) == 0)
        return root_dir;

    char *short_dir = strrchr(whole_current_dir, '/');
    return short_dir+1;
}

void print_cr0() {
    char *current_dir = get_current_dir();
    printf("%s 🪄 ", current_dir);
}

void pwd() {
    char current_dir[100];
    getcwd(current_dir, sizeof(current_dir));
    printf("%s \n", current_dir);
}

void wrong_cmd_error(const char *cmd) {
    printf("cr0_shell:");
    printf( RED " %s " RESET, cmd);
    printf("is not found \n");
    print_cr0();
}

int words_counter(const char *str) {
    int space_count = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == ' ')
            space_count++;
    }
    space_count++;
    return space_count;
}

void run_cmd(const char *cmd, char *arg)  {
    if(strcmp("l", cmd) == 0 || strcmp("ls", cmd) == 0) {
        ls(arg);
        print_cr0();
    }
    else if(strcmp("ll", cmd) == 0) {
        ll(arg);
        print_cr0();
    }
    else if(strcmp("cd", cmd) == 0) {
        cd(arg);
        print_cr0();
    }
    else if(strcmp("touch", cmd) == 0) {
        touch(arg);
        print_cr0();
    }
    else if(strcmp("pwd", cmd) == 0) {
        pwd();
        print_cr0();
    }
    else if(strcmp("echo", cmd) == 0) {
        echo(arg);
        print_cr0();
    }
    else {
        wrong_cmd_error(cmd);
    }
}

void line_parser(char *line) {
    char *cmd_name;
    char *arg1;

    cmd_name = strtok(line, " ");
    arg1 = strtok(NULL, " ");

    run_cmd(cmd_name, arg1);
}

void parse_input(char *input_line) {
    if(strlen(input_line) == 0) {
        print_cr0();
    }
    else if(strlen(input_line) > 0 && words_counter(input_line) == 1) {
        run_cmd(input_line, NULL);
    }
    else if(strlen(input_line) > 0 && words_counter(input_line) > 1) {
        line_parser(input_line);
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

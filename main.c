#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int is_file_hidden(const char *str) {
    return str[0]=='.';
}

void cmd_parser(const char *line) {
    
}

void ls() {
    DIR *current_directory;
    struct dirent *dir_entry;

    current_directory = opendir(".");
    
    if(current_directory != NULL) {
        while((dir_entry = readdir(current_directory)) != NULL) {
            if(is_file_hidden(dir_entry->d_name))
                continue;
            else
                printf("  %s  ", dir_entry->d_name);
        }
        printf("\n");
    }
    else {
        puts("Lmao folder is not exists!");
    }

    closedir(current_directory);
}

void run_cmd(char *cmd)  {
    if(strcmp("ls", cmd) == 0) {
        ls();
    }
}

int main(int argc, char **argv) {
    system("clear");
    char line[256];
    printf("cr0$ > ");
    while(fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        run_cmd(line);
        printf("cr0$ > ");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void ls() {
    DIR *current_directory;
    struct dirent *dir_entry;

    current_directory = opendir(".");
    
    if(!current_directory) {
        puts("Lmao folder is not exists!");
    }
    else {
        //system("ls");
        while((dir_entry = readdir(current_directory)) != NULL) {
            printf("%s  |%d|\n", dir_entry->d_name, dir_entry->d_type);
        }
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

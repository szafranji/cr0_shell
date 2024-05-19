#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

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
    for(int i = 0; line[i] != ' '; i++) {
        printf("%c", line[i]);
    }
    printf("\n");
}

int is_file_hidden(const char *str) {
    return str[0]=='.';
}

void ll() {
    DIR *current_directory;
    struct dirent *dir_entry;

    current_directory = opendir(".");
    if(current_directory != NULL) {
        int first_dir = 0;
        int files_counter = 0;

        while((dir_entry = readdir(current_directory)) != NULL) {
            if(strcmp(".", dir_entry->d_name) == 0) {
                printf("      %s \n", dir_entry->d_name);
                break;
            }
            else
                continue;
        }
        while((dir_entry = readdir(current_directory)) != NULL) {
            if(strcmp("..", dir_entry->d_name) == 0) {
                printf("      %s \n", dir_entry->d_name);
                break;
            }
            else
                continue;
        }

      rewinddir(current_directory);

        while((dir_entry = readdir(current_directory)) != NULL) {
            files_counter++;
            if((strcmp(".", dir_entry->d_name) == 0) || (strcmp("..", dir_entry->d_name) == 0))
                continue;
            else
                if(dir_entry->d_type == DT_DIR)
                {
                    printf("   %d) ", files_counter);
                    printf( CYAN "%s \n" RESET, dir_entry->d_name);
                }
                else
                    printf("   %d) %s \n", files_counter, dir_entry->d_name);
        }
    }

    closedir(current_directory);
}

void l() {
    DIR *current_directory;
    struct dirent *dir_entry;

    current_directory = opendir(".");
    if(current_directory != NULL) {
        while((dir_entry = readdir(current_directory)) != NULL) {
            if(is_file_hidden(dir_entry->d_name))
                continue;
            else
                if(dir_entry->d_type == DT_DIR)
                    printf( CYAN "%s  " RESET, dir_entry->d_name);
                else
                    printf("%s  ", dir_entry->d_name);
        }
        printf("\n");
    }
    else {
        puts("Lmao folder is not exists!");
    }

    closedir(current_directory);
}
void wrong_cmd_error(const char *cmd) {
    printf("cr0_shell:");
    printf( RED " %s " RESET, cmd);
    printf("is not found \n");
    printf("cr0$ > ");
}

void run_cmd(const char *cmd)  {
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
        run_cmd(input_line);
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

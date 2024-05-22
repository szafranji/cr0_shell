#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int is_file_hidden(const char *str) {
    return str[0]=='.';
}
void ll() {
    DIR *current_directory;
    struct dirent *dir_entry;
    struct stat *file_stat;

    current_directory = opendir(".");
    if(current_directory != NULL) {
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
                    printf( CYAN "%s -- %d \n" RESET, dir_entry->d_name, file_stat->st_size);
                }
                else
                    printf("   %d) %s -- %lld \n", files_counter, dir_entry->d_name, (long long)file_stat->st_size);
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

int ls_checks_the_args(const char *line) {
    char *args[] = {"-la", "-lt", "-lF", "-lc", "-ld"};

    for(int i = 0; i < 5; i++) {
        if(strcmp(args[i], line) == 0) {
            return 1;
        }
    }
    printf("cr0_shell: invalid argument for ls!\n");
    printf("cr0$ > ");
}

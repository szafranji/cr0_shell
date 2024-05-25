#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int is_file_hidden(const char *str) {
    return str[0]=='.';
}

void ls_another_dir(const char *arg) {
    DIR *another_directory;
    struct dirent *dir_entry;

    another_directory = opendir(arg);

    if(another_directory != NULL) {
        while((dir_entry = readdir(another_directory)) != NULL) {
            if(is_file_hidden(dir_entry->d_name))
                continue;
            else {
                if(dir_entry->d_type == DT_DIR)
                    printf( CYAN "%s  " RESET, dir_entry->d_name);
                else
                    printf("%s  ", dir_entry->d_name);
            }
        }
        printf("\n");
    }
    closedir(another_directory);
}

int check_if_arg_file(const char *arg) {
    struct stat stat_path;
    stat(arg, &stat_path);

    return S_ISREG(stat_path.st_mode);
}

int check_if_arg_dir(const char *arg) {
    struct stat stat_path;
    stat(arg, &stat_path);

    return S_ISDIR(stat_path.st_mode);
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

void ls(const char *arg) {
    DIR *current_directory;
    struct dirent *dir_entry;

    if(arg == NULL) {
        current_directory = opendir(".");
        if(current_directory != NULL) {
            while((dir_entry = readdir(current_directory)) != NULL) {
                if(is_file_hidden(dir_entry->d_name))
                    continue;
                else {
                    if(dir_entry->d_type == DT_DIR)
                        printf( CYAN "%s  " RESET, dir_entry->d_name);
                    else
                        printf("%s  ", dir_entry->d_name);
                }
            }
            printf("\n");
        }
    }

    else if (check_if_arg_dir(arg) == 1){
        ls_another_dir(arg);
    }

    else if (check_if_arg_file(arg) == 1){
        puts("cr0_shell: can't ls a file!");
    }
    else {
        puts("cr0_shell: file is not found!");
    }
}


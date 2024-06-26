#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CYAN "\x1b[36m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void check_file_chmod(const char *arg, char *chmod_buffer) {
    struct stat sb;
    stat(arg, &sb);

    char *chmod = malloc(9*sizeof(char));

    if(sb.st_mode & S_IRUSR) strcat(chmod, "r");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IWUSR) strcat(chmod, "w");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IXUSR) strcat(chmod, "x");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IRGRP) strcat(chmod, "r");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IWGRP) strcat(chmod, "w");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IXGRP) strcat(chmod, "x");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IROTH) strcat(chmod, "r");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IWOTH) strcat(chmod, "w");
    else strcat(chmod, "-");

    if(sb.st_mode & S_IXOTH) strcat(chmod, "x");
    else strcat(chmod, "-");

    strncpy(chmod_buffer, chmod, 8);
    chmod_buffer[8] = '\0';
}


int is_file_hidden(const char *str) {
    return str[0]=='.';
}

int check_flag(const char *arg) {
    return arg[0]=='-';
}

void ls_main(const char *arg) {
    DIR *dir_to_list;
    struct dirent *dir_entry;

    dir_to_list = opendir(arg);
    if(dir_to_list != NULL) {
        while((dir_entry = readdir(dir_to_list)) != NULL) {
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

    closedir(dir_to_list);
}

int check_if_arg_file(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return S_ISREG(sb.st_mode);
}



long check_file_size(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return sb.st_size;
}

int check_if_arg_dir(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return S_ISDIR(sb.st_mode);
}

int get_file_size(const char *arg, char *tag) {
    long f_size = check_file_size(arg);

    if(f_size > 1000000) {
        f_size = f_size / (1024*1024);
        strncpy(tag, "MB", 3);
    }
    else if((f_size > 1000 && f_size < 1000000)) {
        f_size = f_size / 1024;
        strncpy(tag, "KB", 3);
    }
    else
        strncpy(tag, "B", 2);

    return f_size;
}


void ll() {
    DIR *current_directory;
    struct dirent *dir_entry;
    char file_size_tag[120];

    current_directory = opendir(".");
    if(current_directory != NULL) {

        while((dir_entry = readdir(current_directory)) != NULL) {
            int f_size = 0;
            char chmod_str[9];

            if((strcmp(".", dir_entry->d_name) == 0) || (strcmp("..", dir_entry->d_name) == 0))
                continue;

            else {
                check_file_chmod(dir_entry->d_name, chmod_str);
                if(dir_entry->d_type == DT_DIR)
                {
                    printf( CYAN "%s 4096B \t%s\n" RESET, chmod_str, dir_entry->d_name);
                }
                else {
                    f_size = get_file_size(dir_entry->d_name, file_size_tag);
                    printf("%s %d%s \t%s\n", chmod_str, f_size, file_size_tag, dir_entry->d_name);
                }
            }
            f_size = 0;
        }
    }

    closedir(current_directory);
}

void ls(const char *arg) {
    if(arg == NULL)
        ls_main(".");
    else if(check_flag(arg) == 1)
        puts("cr0_shell: ls doesn't have flags! Use ll instead!");

    else if (check_if_arg_dir(arg) == 1)
        ls_main(arg);

    else if (check_if_arg_file(arg) == 1)
        puts("cr0_shell: can't ls a file!");

    else
        puts("cr0_shell: dir is not found!");
}

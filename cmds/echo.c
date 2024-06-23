#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int check_gt_symbol(const char *arg) {
    for(int i = 0; arg[i] != '\0'; i++) {
        if(arg[i] == '>')
            return 0;
    }
    return 1;
}

void echo_main(const char *arg) {
    printf("%s \n", arg);
}

int check_if_arg_gile(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return S_ISREG(sb.st_mode);
}

void echo_parse(const char *arg) {
    if(check_gt_symbol(arg) != 0 && check_if_arg_gile(arg) != 1) // if arg is random text without > symbol or if arg is not a file or dir
        echo_main(arg);
    else if(check_gt_symbol(arg) == 0 && check_if_arg_gile(arg) != 1) {  // if line contains gt symbol
            // TO DO
    }
    else if(check_gt_symbol(arg) != 0 && check_if_arg_gile(arg) == 1) { // if arg is a file
            // cat(arg);
    }
}

void echo(const char *line) {
    echo_parse(line);
}

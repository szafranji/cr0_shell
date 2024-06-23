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

void echo_main(const char *line) {
    printf("%s \n", line);
}

int check_if_arg_gile(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return S_ISREG(sb.st_mode);
}

void echo_parse(const char *line) {
    if(check_gt_symbol(line) != 0 && check_if_arg_gile(line) != 1)
        echo_main(line);
}

void echo(const char *line) {
    echo_parse(line);
}

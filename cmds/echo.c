#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void echo_main(const char *line) {
    printf("%s \n", line);
}

void echo_parse(const char *line) {

}

void echo(const char *line) {
    echo_main(line);
}

int check_if_arg_gile(const char *arg) {
    struct stat sb;
    stat(arg, &sb);

    return S_ISREG(sb.st_mode);
}

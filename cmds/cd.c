#include <stdio.h>
#include <unistd.h>

void cd(const char *arg) {
    int ret;
    if((ret = chdir(arg)) != 0) {
        perror("cd");
    }
}

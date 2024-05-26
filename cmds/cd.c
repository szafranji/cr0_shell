#include <stdio.h>
#include <unistd.h>

void cd(const char *arg) {
    chdir(arg);
}

#include <stdio.h>

void touch(const char *arg) {
    FILE *fp = fopen(arg, "a");

    if(fp == NULL)
        perror("touch");
}


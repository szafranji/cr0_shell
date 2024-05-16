#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// at this moment cr0_sh will contain 3 commands: ls, cat, cp //

void run_cmd(char *cmd)  {
    if(strcmp("ls", cmd) == 0) {
        system("ls"); // it is not permanent solution
    }
}

int main(int argc, char **argv) {
    system("clear");
    char line[256];
    printf("cr0$ > ");
    while(fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = 0;
        run_cmd(line);
        printf("cr0$ > ");
    }
}

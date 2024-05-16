#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run_cmd(char *cmd) {
    
}

void recognize_cmd(char *cmd)  {

}

int main(int argc, char **argv) {
    system("clear");
    char line[256];
    printf("cr0$ > ");
    while(fgets(line, sizeof(line), stdin)) {
        printf("cr0$ > ");
    }
}

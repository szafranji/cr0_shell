#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

char prev_dir[120];

void cd_main(const char *arg) {
    int ret;
    if((ret = chdir(arg)) != 0)
        perror("cd");
}

void cd_HOME() {
    struct passwd *pw = getpwuid(getuid());
    const char *home_addr = pw->pw_dir;
    
    cd_main(home_addr);
}

void cd(char *arg) {
    if(arg == NULL) {
        getcwd(prev_dir, sizeof(prev_dir));
        cd_HOME();
    }
    else if(strcmp("-", arg) == 0) {
        strncpy(arg, prev_dir, sizeof(prev_dir));
        getcwd(prev_dir, sizeof(prev_dir));
        cd_main(arg);
    }
    else {
        getcwd(prev_dir, sizeof(prev_dir));
        cd_main(arg);
    }
}

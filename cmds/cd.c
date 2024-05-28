#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

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


void cd(const char *arg) {
    if(arg == NULL)
        cd_HOME();
    else
        cd_main(arg);
}

void cd_to_oldpwd() {

}

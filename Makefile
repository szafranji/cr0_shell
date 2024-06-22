all:
	gcc main.c cmds/ls.c cmds/cd.c cmds/touch.c cmds/echo.c -Wall -o cr0_shell
clean:
	rm cr0_shell

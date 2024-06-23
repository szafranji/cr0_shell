all:
	gcc main.c cmds/built-in/ls.c cmds/built-in/cd.c cmds/built-in/touch.c cmds/built-in/echo.c -Wall -o cr0_shell
clean:
	rm cr0_shell

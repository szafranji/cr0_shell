OBJ = ls.o cd.o touch.o echo.o
BUILTIN = cmds/built-in/

all: cr0_shell

cr0_shell: $(OBJ)
	gcc main.c $(OBJ) -o cr0_shell

ls.o: $(BUILTIN)ls.c $(BUILTIN)ls.h
	gcc -c cmds/built-in/ls.c
cd.o: $(BUILTIN)cd.o $(BUILTIN)cd.h
	gcc -c cmds/built-in/cd.c
touch.o: $(BUILTIN)touch.c $(BUILTIN)touch.h
	gcc -c cmds/built-in/touch.c
echo.o: $(BUILTIN)echo.c $(BUILTIN)echo.h
	gcc -c cmds/built-in/echo.c

clean:
	rm cr0_shell $(OBJ)

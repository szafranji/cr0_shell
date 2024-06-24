OBJ = ls.o cd.o touch.o echo.o main.o
BUILTIN = cmds/built-in/
CC = gcc
CC_FLAGS = -Wall

all: cr0_shell

cr0_shell: $(OBJ)
	$(CC) $(OBJ) -o cr0_shell

main.o: main.c
	$(CC) -c main.c
ls.o: $(BUILTIN)ls.c $(BUILTIN)ls.h
	$(CC) -c $(BUILTIN)ls.c
cd.o: $(BUILTIN)cd.o $(BUILTIN)cd.h
	$(CC) -c $(BUILTIN)cd.c
touch.o: $(BUILTIN)touch.c $(BUILTIN)touch.h
	$(CC) -c $(BUILTIN)touch.c
echo.o: $(BUILTIN)echo.c $(BUILTIN)echo.h
	$(CC) -c $(BUILTIN)echo.c

clean:
	rm cr0_shell $(OBJ) cmds/built-in/cd.o

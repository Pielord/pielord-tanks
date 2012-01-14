all: main_tank.c
	gcc -Wall main_tank.c -o tanki -ggdb -lncurses

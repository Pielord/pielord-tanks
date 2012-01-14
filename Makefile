all: map.c
	gcc -Wall main.c map.c -o tanki -ggdb -lncurses

all: map.c
	gcc -Wall main.c map.c -o tank -ggdb -lncurses

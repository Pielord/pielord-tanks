all: map.c
	gcc -Wall map.c -o map_test -ggdb -lncurses

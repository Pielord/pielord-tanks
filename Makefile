all:
	gcc -Wall main.c players.c -o bin/tank-game -ggdb -lncurses

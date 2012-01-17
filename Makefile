all:

	gcc -Wall main.c player.c map.c -o bin/tank-game -ggdb -lncurses

test:
	gcc -Wall main_test.c player.c map.c -o bin/tanki_test -ggdb -lncurses

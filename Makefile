all:
	gcc -Wall main.c -o tanki -ggdb -lncurses

test:
	gcc -Wall main_test.c -o tanki_test -ggdb -lncurses
all:
<<<<<<< HEAD
	gcc -Wall main.c players.c -o bin/tank-game -ggdb -lncurses
=======
	gcc -Wall main.c -o tanki -ggdb -lncurses

test:
	gcc -Wall main_test.c -o tanki_test -ggdb -lncurses
>>>>>>> 82f164d205bb9abddb8cd38124bc518860f53da6

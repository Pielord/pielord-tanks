all:
	cc -Wall main.c client.c game.c -o bin/tank-serv -ggdb -levent

all:
	cc -Wall main.c client.c -o bin/tank-serv -ggdb -levent

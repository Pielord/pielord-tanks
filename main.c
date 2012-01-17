#include <stdlib.h>
//#include <stdio.h>


#include <unistd.h>

#include <curses.h>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>




#include "map.h"
#include "player.h"
#include "../tanki-serv/packet.h"

#define BUFFSIZE 32
#define PORT 3033

void Die(char *mess) { perror(mess); exit(1); }
           



int main(void) {
	
	 int sock;
     struct sockaddr_in serv;
     char buffer[BUFFSIZE];
     unsigned int servlen;
     int received = 0;
	/*
    if (argc != 1) {
      fprintf(stderr, "USAGE: tanki <server_ip>\n");
      exit(1);
    }*/
            /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      Die("Failed to create socket");
    }
	
	
	
	  memset(&serv, 0, sizeof(serv));       
      serv.sin_family = AF_INET;                  
      //serv.sin_addr.s_addr = inet_addr(argv[1]); 
      serv.sin_addr.s_addr = htonl(0x7f000001); // 127.0.0.1

      serv.sin_port = htons(PORT);       
    // Establish connection 
    
    if (connect(sock,
                (struct sockaddr *) &serv,
                sizeof(serv)) < 0) {
      Die("Failed to connect with server");
    }

	servlen = sizeof(serv);
	  
	if (bind(sock, (struct sockaddr *) &serv, servlen) < 0) {
		Die("Failed to bind server socket");
	}

    int ch = 0;
    initscr(); // Start curses mode

    cbreak(); // Line buffering disabled
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    start_color();          // turn on color function
    assume_default_colors(COLOR_WHITE, COLOR_BLACK); // default colors

    //Nezinu kadaa martinsh shito kompileeja :/


    // creates map
    MAP * game_map;
    game_map = malloc(sizeof (MAP));
    init_map_params(game_map);

    // draws map border
    create_map(game_map, 1);

    // creates demo player
    int player1 = player_add(game_map);

    // draws map with this player
    player_draw(game_map);
    getchar();



    while (ch != 81) {


        ch = getch();


        switch (ch) {
            case KEY_LEFT:
                //call function 
                player_move(player1, '<', game_map);
                break;
            case KEY_RIGHT:
                //call function 
                player_move(player1, '>', game_map);
                break;
            case KEY_DOWN:
                //call function 
                player_move(player1, 'v', game_map);
                break;
            case KEY_UP:
                //call function 
                player_move(player1, '^', game_map);
                break;
            case 32:
                //space key  
                player_shoot(player1, game_map);
                break;
        }

        // animate all bullets.
        player_animate_bullets(game_map);

        
        // draw map for the player
        player_draw(game_map);


    }


    refresh(); /* Print it on to the real screen */

    endwin(); /* End curses mode		  */

    return 0;

}

#include <stdlib.h>
#include <stdio.h>

//#include <conio.h>

#include <unistd.h>

#include <ncurses.h>

#include "player.h"
#include "map.h"
//#include "funkcijasKarlim.c"



int main(void) {
	
		int ch = 0;
		initscr();    // Start curses mode
	
		cbreak();		        // Line buffering disabled
		keypad(stdscr, TRUE);
		nodelay(stdscr,TRUE);
		noecho();
		
		//Nezinu kadaa martinsh shito kompileeja :/
		 
	/*
        // creates map
        MAP * game_map;
        game_map = malloc(sizeof(MAP));
        init_map_params(game_map);
        
        // draws map border
        create_map(game_map,1);
        
        // creates demo player
        int player1 = player_add();
        
        // draws map with this player
        player_draw(game_map);
        getchar();
    	*/    
	
			
			while(ch != 113)
			{
			
				
					ch = getch();
				
					
					switch(ch)
					{	
						case KEY_LEFT:
							//call function 
								mvaddch(20, 20,'2');
							break;
						case KEY_RIGHT:
							//call function 
								mvaddch(20, 20,'2');
							break;
						case KEY_DOWN:
							//call function 
								//player_move(player1, '>');
       							//player_draw(game_map);
							break;
						case KEY_UP:
							//call function 
								mvaddch(20, 20,'2');
							break;
					}
				
				
			}
	
	
	refresh();			/* Print it on to the real screen */
	
	endwin();			/* End curses mode		  */

	return 0;

}

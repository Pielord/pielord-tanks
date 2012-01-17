#include <stdlib.h>
#include <stdio.h>

//#include <conio.h>

#include <unistd.h>

#include <curses.h>


#include "funkcijasKarlim.c"
#include "player.h"
#include "player.c"
//

int main(void) {

    int ch = 0;
    initscr(); // Start curses mode

    cbreak(); // Line buffering disabled
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();

    //Nezinu kadaa martinsh shito kompileeja :/


    // creates map
    MAP * game_map;
    game_map = malloc(sizeof (MAP));
    init_map_params(game_map);

    // draws map border
    create_map(game_map, 1);

    // creates demo player
    int player1 = player_add();

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

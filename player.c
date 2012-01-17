#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "map.h"
#include "player.h"

/*
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
 */
// player container
static player * all_players;
static int player_count = 0;

// bullet container
static struct player_bullet * player_all_bullets;
static int player_bullet_count = 0;

int player_get_player_count() {
    return player_count;
}

/**
 * Create new player.
 * @param x
 * @param y
 * @return int
 */
int player_add() {
    
    // @TODO put on a random location
    int pos_x = rand() % MAP_WIDTH;
    int pos_y = rand() % MAP_HEIGHT;
    
    
    player_count++;

    // add place for player in memory
    all_players = realloc(all_players, sizeof (player) * player_count);


    // players id.
    int player_id = player_count - 1;

    // set player x,y coords
    all_players[player_id].x = (float) pos_x;
    all_players[player_id].y = (float) pos_y;
    all_players[player_id].direction = '>';
    all_players[player_id].last_time_moved = 0.0;
    all_players[player_id].alive = 1;
    

    return player_id;

}

/**
 * Initialize for randomness
 * @param player_count
 */
void player_init_players(int player_count) {

    all_players = malloc(sizeof (player) * player_count);

    // initialize random genearator
    srand(time(NULL));
}


/**
 * Redraw all players on the map
 * @param map_p
 */
void player_draw(MAP *map_p) {
    
    // clear map before drawing
    clear_map(map_p);
    
    int i;

    // draw players
    for (i = 0; i < player_count; i++) {

        int player_position = all_players[i].y * map_p->width + all_players[i].x;

        map_p->map_canvas.map_grid[player_position] = all_players[i].direction;
    }

    // draw bullets
    for (i = 0; i < player_bullet_count; i++) {

        int bullet_position = player_all_bullets[i].y * map_p->width + player_all_bullets[i].x;

        map_p->map_canvas.map_grid[bullet_position] = PLAYER_BULLET;
    }

    // draw map
    draw_map(map_p);

}

/**
 * Player moves somewhere
 * @param player_id
 * @param direction
 */
void player_move(int player_id, char direction, MAP *map_p) {

    // only move player if time has come
    double now = get_time();

    double player_movement = 1.0 / PLAYER_MOVEMENT_FPS;
    if (all_players[player_id].last_time_moved + player_movement > now) {
        return;
    } else {
        all_players[player_id].last_time_moved = now;
    }
    
    int old_x = all_players[player_id].x;
    int old_y = all_players[player_id].y;

    // move player
    switch (direction) {

        case '>':
            if (map_p->width > all_players[player_id].x + 1 
                    && direction==all_players[player_id].direction) {
                all_players[player_id].x++;
            }
            break;
        case '<':
            if (all_players[player_id].x - 1 >= 0
                    && direction==all_players[player_id].direction) {
                all_players[player_id].x--;
            }
            break;
        case '^':
            if (all_players[player_id].y - 1 >= 0
                    && direction==all_players[player_id].direction) {
                all_players[player_id].y--;
            }
            break;
        case 'v':
            if (map_p->height > all_players[player_id].y + 1
                    && direction==all_players[player_id].direction) {
                all_players[player_id].y++;
            }

            break;
    }
    
    // check whether player can move here
    if(get_map_element(map_p, all_players[player_id].x, all_players[player_id].y) !=' ') {
        all_players[player_id].x = old_x;
        all_players[player_id].y = old_y;
    }
    
    // set player direction
    all_players[player_id].direction = direction;
}

void player_redraw_location_on_map(int player_id) {

}

/**
 * Remove player from player array by his id
 * @param player_id
 */
void player_remove(int player_id) {

    int i;

    // copy players one place up
    for (i = 0; i < player_count; i++) {
        if (i > player_id) {
            memcpy(&all_players[i - 1], &all_players[i], sizeof(player));
            //all_players[i - 1] = all_players[i];
        }
    }

    player_count--;

    //all_players = realloc(all_players, sizeof (player) * player_count);

}

/**
 * Returns whether a player is alive
 * @param player_id
 * @return 
 */
int player_is_alive(int player_id) {
    
    return all_players[player_id].alive;
    
}


/**
 * create new bullet
 * @param player_id
 */
void player_shoot(int player_id, MAP *map_p) {

    // limit bullet shooting
    double now = get_time();

    double player_movement = 1.0 / PLAYER_BULLET_SHOOT_FPS;
    if (all_players[player_id].last_time_shot + player_movement > now) {
        return;
    } else {
        all_players[player_id].last_time_shot = now;
    }
    
    player_bullet_count++;

    // add place for player in memory
    player_all_bullets = realloc(player_all_bullets, sizeof (struct player_bullet) * player_bullet_count);


    // players id.
    int bullet_id = player_bullet_count - 1;

    
    // set bullet coords, direction
    player_all_bullets[bullet_id].direction = all_players[player_id].direction;
    
    player_all_bullets[bullet_id].last_time_moved = get_time();
    
    
    // @TODO put bullet 1 field ahed player
    switch (player_all_bullets[bullet_id].direction) {

        case '>':
            player_all_bullets[bullet_id].x = all_players[player_id].x+1;
            player_all_bullets[bullet_id].y = all_players[player_id].y;
            break;
        case '<':
            player_all_bullets[bullet_id].x = all_players[player_id].x-1;
            player_all_bullets[bullet_id].y = all_players[player_id].y;
            break;
        case '^':
            player_all_bullets[bullet_id].x = all_players[player_id].x;
            player_all_bullets[bullet_id].y = all_players[player_id].y-1;
            break;
        case 'v':
            player_all_bullets[bullet_id].x = all_players[player_id].x;
            player_all_bullets[bullet_id].y = all_players[player_id].y+1;
            break;
    }
    
    // check if bullet isn't out of bounds
    if (player_all_bullets[bullet_id].y < 0 
            || player_all_bullets[bullet_id].x < 0 
            || player_all_bullets[bullet_id].x > map_p->width-1 
            || player_all_bullets[bullet_id].y > map_p->height-1
       ) {
        player_bullet_remove(bullet_id);
    }
    
}

/**
 * Animate one bullet
 * @param bullet_id
 * @param map_p
 */
void player_bullet_move(int bullet_id, MAP *map_p) {

    // only move bullet if time has come
    double now = get_time();

    double bullet_movement = 1.0 / PLAYER_BULLET_FPS;
    if (player_all_bullets[bullet_id].last_time_moved + bullet_movement > now) {
        return;
    } else {
        player_all_bullets[bullet_id].last_time_moved = now;
    }



    // move player
    switch (player_all_bullets[bullet_id].direction) {

        case '>':
            if (map_p->width > player_all_bullets[bullet_id].x + 1) {
                player_all_bullets[bullet_id].x++;
            }
            else {
                player_bullet_remove(bullet_id);
            }
            break;
        case '<':
            if (player_all_bullets[bullet_id].x - 1 >= 0) {
                player_all_bullets[bullet_id].x--;
            }
            else {
                player_bullet_remove(bullet_id);
            }
            break;
        case '^':
            if (player_all_bullets[bullet_id].y - 1 >= 0) {
                player_all_bullets[bullet_id].y--;
            }
            else {
                player_bullet_remove(bullet_id);
            }
            break;
        case 'v':
            if (map_p->height > player_all_bullets[bullet_id].y + 1) {
                player_all_bullets[bullet_id].y++;
            }
            else {
                player_bullet_remove(bullet_id);
            }

            break;
    }
    
    // check whether some player died
    check_bullet_colisions(bullet_id);

}

/**
 * Remove bullet from the map
 * @param billet_id
 */
void player_bullet_remove(int bullet_id) {
    
    int i;

    // copy players one place up
    for (i = 0; i < player_bullet_count; i++) {
        if (i > bullet_id) {
            memcpy(&player_all_bullets[i - 1], &player_all_bullets[i], sizeof(struct player_bullet));
            //all_players[i - 1] = all_players[i];
        }
    }

    player_bullet_count--;

    //player_all_bullets = realloc(player_all_bullets, sizeof (struct player_bullet) * player_bullet_count);
}

/**
 * Check whether a bullet has killed a player
 * @param bullet_id
 */
void check_bullet_colisions(int bullet_id) {
    
    // @TODO check collisions after player movement
    
    int i;
    
    for (i = 0; i < player_count; i++) {

        if(all_players[i].x == player_all_bullets[bullet_id].x 
                && all_players[i].y == player_all_bullets[bullet_id].y) {
            all_players[i].alive = 0;
            
            // remove this bullet
            player_bullet_remove(i);
        }
    }
}

/**
 * Animate all bullets
 * @return 
 */
void player_animate_bullets(MAP *map_p) {
    
    int i;
    for (i = 0; i < player_bullet_count; i++) {

        player_bullet_move(i, map_p);

    }
}

/**
 * Returns system time
 * @return double
 */
double get_time(void) {

    struct timeval tv;
    gettimeofday(&tv, NULL);

    double now;
    now = tv.tv_sec;
    now += (double) tv.tv_usec / 1000000.0;

    return now;
}

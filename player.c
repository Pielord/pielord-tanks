#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <time.h>

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
static int player_bullet_count;

/**
 * Create new player.
 * @param x
 * @param y
 * @return int
 */
int player_add() {

    player_count++;

    // add place for player in memory
    all_players = realloc(all_players, sizeof (player) * player_count);


    // players id.
    int player_id = player_count - 1;

    // set player x,y coords
    all_players[player_id].x = (float) 1;
    all_players[player_id].y = (float) 1;
    all_players[player_id].direction = '>';
    all_players[player_id].last_time_moved = 0.0;
    all_players[player_id].alive = 1;
    

    return player_id;

}

/*
void player_init_players(int player_count) {
    all_players = malloc(sizeof (player) * player_count);

    //Some init code here.

}
 */

/**
 * Redraw all players on the map
 * @param map_p
 */
void player_draw(MAP *map_p) {

    int i;

    // draw players
    for (i = 0; i < player_count; i++) {

        int player_position = all_players[i].y * map_p->width + all_players[i].x;

        map_p->map_canvas->map_grid[player_position] = all_players[i].direction;
    }

    // draw bullets
    for (i = 0; i < player_bullet_count; i++) {

        int bullet_position = player_all_bullets[i].y * map_p->width + player_all_bullets[i].x;

        map_p->map_canvas->map_grid[bullet_position] = PLAYER_BULLET;
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


    // set player direction
    all_players[player_id].direction = direction;

    // move player
    switch (direction) {

        case '>':
            if (map_p->width > all_players[player_id].x + 1) {
                all_players[player_id].x++;
            }
            break;
        case '<':
            if (all_players[player_id].x - 1 > 0) {
                all_players[player_id].x--;
            }
            break;
        case '^':
            if (all_players[player_id].y - 1 > 0) {
                all_players[player_id].y--;
            }
            break;
        case 'v':
            if (map_p->height > all_players[player_id].y + 1) {
                all_players[player_id].y++;
            }

            break;
    }
}

void player_redraw_location_on_map(int player_id) {

}

/**
 * Remove player from player array by his id
 * @param player_id
 */
/*
void player_remove(int player_id) {

    int i;

    // copy players one place up
    for (i = 0; i < player_count; i++) {
        if (i > player_id) {
            memcpy(all_players[i - 1], all_players[i], sizeof(player));
            //all_players[i - 1] = all_players[i];
        }
    }

    player_count--;

    all_players = realloc(all_players, sizeof (player) * player_count);

}*/

/**
 * create new bullet
 * @param player_id
 */
void player_shoot(int player_id, MAP *map_p) {

    player_bullet_count++;

    // add place for player in memory
    player_all_bullets = realloc(player_all_bullets, sizeof (struct player_bullet) * player_bullet_count);


    // players id.
    int bullet_id = player_bullet_count - 1;

    // @TODO put bullet 1 field ahed player
    // set bullet coords, direction
    player_all_bullets[bullet_id].direction = all_players[player_id].direction;
    player_all_bullets[bullet_id].x = all_players[player_id].x;
    player_all_bullets[bullet_id].y = all_players[player_id].y;
    player_all_bullets[bullet_id].last_time_moved = get_time();

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
            break;
        case '<':
            if (player_all_bullets[bullet_id].x - 1 > 0) {
                player_all_bullets[bullet_id].x--;
            }
            break;
        case '^':
            if (player_all_bullets[bullet_id].y - 1 > 0) {
                player_all_bullets[bullet_id].y--;
            }
            break;
        case 'v':
            if (map_p->height > player_all_bullets[bullet_id].y + 1) {
                player_all_bullets[bullet_id].y++;
            }

            break;
    }
    
    // check whether some player died
    check_bullet_colisions(bullet_id);

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
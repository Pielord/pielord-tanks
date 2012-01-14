#include <string.h>

static struct player * all_players;
static int player_count = 0;

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
    all_players = realloc(all_players, sizeof (struct player) * player_count);


    // players id.
    int player_id = all_players - 1;

    // set player x,y coords
    //all_players[player_id]->x = (float) x;
    //all_players[player_id]->y = (float) y;

    return player_id;

}

void player_init_players(int player_count) {
    all_players = malloc(sizeof (struct player) * player_count);

    //Some init code here.

}

void player_draw() {

}

/**
 * Player moves somewhere
 * @param player_id
 * @param direction
 */
void player_move(int player_id, char direction) {
    
}

/**
 * Remove player from player array by his id
 * @param player_id
 */
void player_remove(int player_id) {

    int i;

    // copy players one place up
    for (i = 0; i < all_players; i++) {
        if (i > player_id) {
            memcpy(all_players[i - 1], all_players[i], sizeof(struct player));
            //all_players[i - 1] = all_players[i];
        }
    }

    player_count--;

    all_players = realloc(all_players, sizeof (struct player) * player_count);

}

/**
 * create new bullet
 * @param player_id
 */
void player_shoot(int player_id) {
    
    player_bullet_count++;

    // add place for player in memory
    player_all_bullets = realloc(player_all_bullets, sizeof (struct player_bullet) * player_bullet_count);


    // players id.
    int bullet_id = player_bullet_count - 1;

    // set bullet coords, direction
    player_all_bullets[bullet_id]->direction = all_players[player_id]->direction;
    player_all_bullets[bullet_id]->x = all_players[player_id]->x;
    player_all_bullets[bullet_id]->y = all_players[player_id]->y;
}

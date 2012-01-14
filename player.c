static struct player * all_players;
static int player_count = 0;

/**
 * Create new player.
 * @param x
 * @param y
 * @return int
 */
int add_player(int x, int y) {

    all_players++;

    // add place for player in memory
    all_players = realloc(all_players, sizeof (struct player) * player_count);


    // players id.
    int player_id = all_players - 1;

    // set player x,y coords
    all_players[player_id]->x = (float) x;
    all_players[player_id]->y = (float) y;

    return player_id;

}

void player_init_players(int player_count) {
    all_players = malloc(sizeof (struct player) * player_count);

    //Some init code here.

}

void player_draw(something * map, struct player * p) {

}

/**
 * Remove player from player array by his id
 * @param player_id
 */
void remove_player(int player_id) {

    int i;
    
    // copy players one place up
    for (i = 0; i < all_players; i++) {
        if(i>player_id) {
            all_players[i-1] = all_players[i];
        }
    }
    
    all_players--;
    
    all_players = realloc(all_players, sizeof (struct player) * player_count);
    
}

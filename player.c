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
    all_players = realloc (all_players, sizeof(struct player) * player_count);
    
    
    // players id.
    int player_id = all_players-1;
    
    // set player x,y coords
    all_players[player_id]->x = (float) x;
    all_players[player_id]->y = (float) y;
    
    return player_id;
    
}


void player_init_players(int player_count)
{
    all_players = malloc(sizeof(struct player) * player_count);
    
    //Some init code here.
    
}

void player_draw(something * map, struct player * p)
{
    
}

void player_free(struct player * p) {
    free(p);
}

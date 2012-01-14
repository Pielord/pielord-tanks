static struct player * all_players;
static int player_count = 0;

/**
 * Create new player.
 * @param id
 * @param x
 * @param y
 */
void add_player(int id, int x, int y) {
    
    all_players++;
    
    // add place for player in memory
    all_players = realloc (all_players, sizeof(struct player) * player_count);
    
    
    // set player x,y coords
    all_players[all_players-1]->x = (float) x;
    all_players[all_players-1]->y = (float) y;
    
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

struct player * all_players;

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

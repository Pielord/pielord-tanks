struct player {
    int tank_id;
    //Coordinates.
    float x;
    float y;
    
    char direction;
};


struct player_bullet {
    
    int tank_id;
    float x;
    float y;
    char direction;
    
};

int add_player(int x, int y);
void remove_player(int player_id);
void player_shoot(int player_id);
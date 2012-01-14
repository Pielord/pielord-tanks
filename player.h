struct player {
    int tank_id;
    //Coordinates.
    float x;
    float y;
    
    char dir;
};

int add_player(int x, int y);
void remove_player(int player_id);
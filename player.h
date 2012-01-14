typedef struct {
    //Coordinates.
    float x;
    float y;
    
    char direction;
} player;


struct player_bullet {
    
    int tank_id;
    float x;
    float y;
    char direction;
    
};

int player_add();
void remove_player(int player_id);
void player_shoot(int player_id);
void player_move(int player_id, char direction);
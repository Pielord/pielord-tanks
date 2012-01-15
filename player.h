typedef struct {
    //Coordinates.
    float x;
    float y;
    
    char direction;
    
    double last_time_moved;
    
    // player is alive
    int alive;
    
} player;


struct player_bullet {
    
    int tank_id;
    float x;
    float y;
    char direction;
    double last_time_moved;
    
};

#define PLAYER_BULLET '*'

// define how fast bullet will move
#define PLAYER_BULLET_FPS 32
#define PLAYER_MOVEMENT_FPS 16

int player_add();
void remove_player(int player_id);
void player_shoot(int player_id, MAP *map_p);
void player_move(int player_id, char direction, MAP *map_p);
void player_bullet_move(int bullet_id, MAP *map_p);

double get_time(void);
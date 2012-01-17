#ifndef GAME_H
#define GAME_H
 
#define MAP_HEIGHT 22;
#define MAP_WIDTH 78;

struct game_map {
    //Map size.
    int map_size_x;
    int map_size_y;
    char * map_data;
    char * map_data_empty;
};

struct player {
    //Coordinates.
    float x;
    float y;
    
    char direction;
    
    double last_time_moved;
    double last_time_shot;
    
    int player_id;
    
    //Health.
    int alive;
};

void player_init(struct player * p, struct game_map * m);
char map_get_element(struct game_map * m, int x, int y);
void map_init(struct game_map * m, char * file);


#endif

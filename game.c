#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "game.h"
#include "client.h"

void 
player_init(struct player * p, struct game_map * m)
{
    int pos_x,pos_y;
    char wall;
    
    do {
        // put on a random location
        pos_x = rand() % m->map_size_x;
        pos_y = rand() % m->map_size_x;

        wall = map_get_element(m, pos_x, pos_y);
    } while(wall != ' ');
    
   
    p->player_id = client_client_count - 1;
    
    p->x = (float) (rand() % m->map_size_x);
    p->y = (float) (rand() % m->map_size_y);
    p->direction = '>';
    p->last_time_moved = 0.0;
    p->alive = 1;
}

int
map_init(struct game_map * m, char * filename)
{
    int map_size = 0;
    FILE *fp;
    
    //TO-DO: Not finishes.
    
    m->map_size_y = MAP_HEIGHT;
    m->map_size_x = MAP_WIDTH;
    
    map_size = sizeof(char) * m->map_size_x * m->map_size_y + 1;
    
    if ((fp = fopen(filename, "r")) != NULL) {
        fgets(m->map_data, map_size, fp);
    } else {
        return 1;
    }
    
    m->map_data = malloc(map_size);
    m->map_data_empty = malloc(map_size);
    memcpy(m->map_data_empty, m->map_data, map_size);
    
    return 0;       
}

char
map_get_element(struct game_map * m, int x, int y)
{
    return m->map_data[y * m->map_size_x + x];
}

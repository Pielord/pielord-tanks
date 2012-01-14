#include "map.h"

struct map * game_map;

void map_init(int map_size_x, int map_size_y)
{
    game_map = malloc(sizeof(struct map));
}

void map_draw(struct map * m)
{
    int i;
    for (i=0; i < m->size_x * m->size_y; i++) {
        switch(m[i]) {
            case MAP_WALL:
                map_draw_wall();
                //write_to_screen(x,y,MAP_WALL);
                break;
            case TANK_UP:
                break;
        }
    }
}

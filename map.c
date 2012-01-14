#include "map.h"
#include <curses.h>
#include <stdlib.h>

struct map * game_map;

void map_init(int map_size_x, int map_size_y)
{
    game_map = malloc(sizeof(struct map));
}

void map_draw(struct map * m)
{
    int i, j;
    for (i=0; i < m->size_x; i++) {
        for (j=0; j < m->size_y; j++) {
            printf(MAP_WALL);
            /*
            switch(m[i]) {
                case MAP_WALL:
                    map_draw_wall();
                    //write_to_screen(x,y,MAP_WALL);
                    break;
                case TANK_UP:
                    break;
            }
            */
        }
    }
}

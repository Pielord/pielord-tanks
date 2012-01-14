#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"

struct tank_map * game_map;

void map_init(int map_size_x, int map_size_y)
{
    game_map = malloc(sizeof(struct tank_map));
    strcpy(game_map->data, "First Map");
    game_map->mapId = 1;
    game_map->maxPlayers = 2;
    game_map->size_x = 10;
    game_map->size_y = 10;
    game_map->next = NULL;
    game_map->prev = NULL;
}

void map_draw(struct tank_map * m){
    int i, j;
    for (i=0; i < game_map->size_x; i++) {
        for (j=0; j < game_map->size_y; j++) {
            if(i == 0){
                printf("+"); // izdrukā vienu sienas simbolu
            }else if(j == 0 || j == game_map->size_y-1){
                printf("+");
            }
        }
    }
}

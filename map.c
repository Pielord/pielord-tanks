#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

tank_map * game_map;

void map_init(int map_size_x, int map_size_y)
{
    game_map = malloc(sizeof(tank_map));
    strcpy(game_map->data, "First Map");
    game_map->mapId = 1;
    game_map->maxPlayers = 2;
    game_map->size_x = map_size_x;
    game_map->size_y = map_size_y;
    game_map->next = NULL;
    game_map->prev = NULL;

}
void create_map(tank_map * m){
	int x, y, w, h;

	x = 0;
	y = 0;
	w = game_map->size_x;
	h = game_map->size_x;

		mvhline(y, x, '+', w); // augša
		mvhline(y + h, x, '+', w); // apakša
		mvvline(y, x, '+', h); // kreisā puse
		mvvline(y, x + w, '+', h); // labā puse

	refresh();

}

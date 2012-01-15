#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "map.h"

void init_map_params(MAP *p_map);
void print_map_params(MAP *p_map);
void create_map(MAP *map, int flag);


void init_map_params(MAP *p_map)
{
	p_map->height = MAP_HEIGHT;
	p_map->width = MAP_WIDTH;
	p_map->starty = 0;
	p_map->startx = 0;

	p_map->border.top = '-';
	p_map->border.side = '|';
}
void print_map_params(MAP *p_map)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_map->startx, p_map->starty, 
				p_map->width, p_map->height);
	refresh();
#endif
}
void create_map(MAP *p_map, int flag)
{	int i, j;
	int x, y, w, h;

	x = p_map->startx;
	y = p_map->starty;
	w = p_map->width;
	h = p_map->height;

	if(flag == 1){
		mvhline(y, x, p_map->border.top, w-1); // augša
		mvhline(y + h, x, p_map->border.top, w-1); // apakša
		mvvline(y+1, x, p_map->border.side, h-1); // kreisā puse
		mvvline(y+1, x + w, p_map->border.side, h-1); // labā puse

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

void fill_map(int x, int y, int size, char mas[]){
    int i, j=0;
    int xx = x-1, yy = 1;
    for (i = 1; i < size; i++){
        j++;
        if(j < xx){
            mvaddch(yy, j, mas[i]);
        }else{
            j = 1;
            if(yy < y){
                yy++;
                mvaddch(yy, j, mas[i]);
            }
        }
    }
}

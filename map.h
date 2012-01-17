#include <curses.h>
#include <stdbool.h>
/*
x - kartes platums 80 (-2)
y - kartes augstums 24 (-2)
size - masīva lielums
data[] - masīvs ar simboliem
 */

#define MAP_HEIGHT 22
#define MAP_WIDTH 78

// kartes laukuma rāmis

typedef struct _map_border_struct {
    chtype top, side;
} MAP_BORDER;

typedef struct {
    char * map_grid;
} map_canvas;

typedef struct _map_struct {
    int startx, starty;
    int height, width;
    MAP_BORDER border;
    map_canvas map_canvas;
    map_canvas original_map;
} MAP;

void init_map_params(MAP *p_map);
void print_map_params(MAP *p_map);
void create_map(MAP *map, bool flag);
void clear_map(MAP *p_map);
void draw_map(MAP *p_map);
char get_map_element(MAP *map_p, int x, int y);


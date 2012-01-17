#include <string.h>
/*
x - kartes platums 80 (-2)
y - kartes augstums 24 (-2)
size - masīva lielums
data[] - masīvs ar simboliem
 */

#define MAP_HEIGHT 23
#define MAP_WIDTH 79

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

void init_map_params(MAP *p_map) {
    p_map->height = MAP_HEIGHT;
    p_map->width = MAP_WIDTH;
    p_map->starty = 0;
    p_map->startx = 0;

    p_map->border.top = '-';
    p_map->border.side = '|';

    // create and fill map
    int map_size = sizeof (char) * p_map->height * p_map->width;
    p_map->map_canvas.map_grid = malloc(sizeof (char) *map_size + 1);
    memset(p_map->map_canvas.map_grid, ' ', map_size);
    
    // clone map
    p_map->original_map.map_grid = malloc(sizeof (char) *map_size + 1);
    memcpy(p_map->original_map.map_grid, p_map->map_canvas.map_grid, map_size);
}

/**
 * Clear map so you can draw on it
 */
void clear_map(MAP *p_map) {
    
    int map_size = sizeof (char) * p_map->height * p_map->width;
    memcpy(p_map->map_canvas.map_grid, p_map->original_map.map_grid, map_size);
}

void print_map_params(MAP *p_map) {
#ifdef _DEBUG
    mvprintw(25, 0, "%d %d %d %d", p_map->startx, p_map->starty,
            p_map->width, p_map->height);
    refresh();
#endif
}

void create_map(MAP *p_map, bool flag) {
    int i, j;
    int x, y, w, h;

    x = p_map->startx;
    y = p_map->starty;
    w = p_map->width;
    h = p_map->height;

    if (flag == TRUE) {
        mvhline(y, x, p_map->border.top, w+1); // augša
        mvhline(y + h, x, p_map->border.top, w+1); // apakša
        mvvline(y + 1, x, p_map->border.side, h - 1); // kreisā puse
        mvvline(y + 1, x + w, p_map->border.side, h - 1); // labā puse

    } else
        for (j = y; j <= y + h; ++j)
            for (i = x; i <= x + w; ++i)
                mvaddch(j, i, 'X');

    refresh();

}

void draw_map(MAP *p_map) {

    int x, y;

    for (x = 1; x < p_map->width; x++) {
        for (y = 1; y < p_map->height; y++) {
            mvaddch(y, x, p_map->map_canvas.map_grid[y * p_map->width + x]);
        }
    }
    refresh();
}

void fill_map(int x, int y, int size, char mas[]) {
    int i, j = 0;
    int xx = x - 1, yy = 1;
    for (i = 1; i < size; i++) {
        j++;
        if (j < xx) {
            mvaddch(yy, j, mas[i]);
        } else {
            j = 1;
            if (yy < y) {
                yy++;
                mvaddch(yy, j, mas[i]);
            }
        }
    }
}

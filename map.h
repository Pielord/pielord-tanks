#define MAP_WALL 124	// +
#define TANK_SHOT 421	// *
#define TANK_UP 944		// ^
#define TANK_DOWN 118	// v
#define TANK_LEFT 608	// <
#define TANK_RIGHT 628	// >


#define MAP_HEIGHT 23
#define MAP_WIDTH 79

/*
typedef struct {
    char * data;
    int mapId;
    int maxPlayers; // citur?
    int size_x;
    int size_y;
    struct tank_map *next;
    struct tank_map *prev;
} tank_map;
*/
// kartes laukuma rāmis
typedef struct _map_border_struct {
	chtype 	top, side;
} MAP_BORDER;

typedef struct _map_struct {

	int startx, starty;
	int height, width;
	MAP_BORDER border;
} MAP;

void init_map_params(MAP *p_map);
void create_map(MAP *p_map, int flag);
void fill_map(int x, int y, int size, char mas[]);
void print_map_params(MAP *p_map);
//void map_init(int map_size_x, int map_size_y);
//void create_map(tank_map *p_map);
//void map_set(int x, int y, enum map_tile);
//void map_draw(MAP * m);
//void map_free(void);

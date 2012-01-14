#define MAP_WALL 124	// +
#define TANK_SHOT 421	// *
#define TANK_UP 944		// ^
#define TANK_DOWN 118	// v
#define TANK_LEFT 608	// <
#define TANK_RIGHT 628	// >

typedef struct {
    char * data;
    int mapId;
    int maxPlayers; // citur?
    int size_x;
    int size_y;
    struct tank_map *next;
    struct tank_map *prev;
} tank_map;

//enum map_tile {
//    WALL,
//    TANK_UP,
//    TANK_DOWN,
//    TANK_LEFT,
//    TANK_RIGHT
//};


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
	chtype 	top, side;
} MAP_BORDER;

typedef struct _map_struct {

	int startx, starty;
	int height, width;
	MAP_BORDER border;
} MAP;

void map_init(int map_size_x, int map_size_y);
void create_map(tank_map *p_map);
//void map_set(int x, int y, enum map_tile);
void fill_map(int x, int y, int size, char mas[]);
void map_draw(MAP * m);
void map_free(void);

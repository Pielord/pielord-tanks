#define MAP_WALL 124	// +
#define TANK_SHOT 421	// *
#define TANK_UP 944		// ^
#define TANK_DOWN 118	// v
#define TANK_LEFT 608	// <
#define TANK_RIGHT 628	// >

struct tank_map {
    char * data;
    int mapId;
    int maxPlayers; // citur?
    int size_x;
    int size_y;
    struct tank_map *next;
    struct tank_map *prev;
} typedef tank_map;

enum map_tile {
    WALL,
    TANK_UP,
    TANK_DOWN,
    TANK_LEFT,
    TANK_RIGHT
};

void map_init(int map_size_x, int map_size_y);
void map_set(int x, int y, enum map_tile);
void map_draw(struct map * m);
void map_free(void);

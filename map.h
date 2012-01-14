#define MAP_WALL 124	// +
#define TANK_SHOT 421	// *
#define TANK_UP 944		// ^
#define TANK_DOWN 118	// v
#define TANK_LEFT 608	// <
#define TANK_RIGHT 628	// >

struct tank_map {
    char * data;
    int mapId;
    int maxPlayers;
    int size_x;
    int size_y;
    struct tank_map *next;
    struct tank_map *prev;
}typedef tank_map;

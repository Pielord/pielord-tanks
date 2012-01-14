#define MAP_WALL 124	// |
#define TANK_SHOT 421	// *
#define TANK_UP 944		// ^
#define TANK_DOWN 118	// v
#define TANK_LEFT 608	// <
#define TANK_RIGHT 628	// >

struct map {
    char * data;
    int size_x;
    int size_y;
}

#include <curses.h>
#include <stdlib.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 40

// tanka struktūra
typedef struct _tank_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br, gb, gm, gt, gtr;
}TANK_BORDER;

// kartes laukuma rāmis
typedef struct _map_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}MAP_BORDER;

typedef struct _map_struct {

	int startx, starty;
	int height, width;
	MAP_BORDER border;
}MAP;

typedef struct _tank_struct {

	int startx, starty;
	int height, width;
	TANK_BORDER border;
}TANK;

void init_map_params(MAP *p_map);
void print_map_params(MAP *p_map);
void create_map(MAP *map, bool flag);

void init_tank_params(TANK *p_tank);
void print_tank_params(TANK *p_tank);
void create_tank(TANK *tank, bool flag);

void create_tank_left(TANK *p_tank, bool flag);
void create_tank_right(TANK *p_tank, bool flag);
void create_tank_down(TANK *p_tank, bool flag);

int main()
{
    TANK tank;
    MAP map;
    int ch;
    
	initscr();              // Start curses mode
		
	if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();          // ieslēdz krāsu funkciju
	
	assume_default_colors(COLOR_WHITE, COLOR_BLACK); // pieņem default krāsas (background)
	
	cbreak();		        // Line buffering disabled
	keypad(stdscr, TRUE);
	noecho();               // neraksta uz ekrāna to ko nospied
	
	// Initialize color parameters
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	
    // Initialize the window parameters
    init_map_params(&map);
	print_map_params(&map);
	init_tank_params(&tank);
	print_tank_params(&tank);
	
	create_map(&map, TRUE); // izveido karti
	
	create_tank(&tank, TRUE);
		        
	while((ch = getch()) != KEY_F(1)) //lasa nospiestās pogas
	{	switch(ch)
		{	case KEY_LEFT:
		        //clear();
				create_tank_left(&tank, FALSE);
				--tank.startx;
				if(tank.startx <= map.startx){
				    ++tank.startx;
				    create_map(&map, TRUE);
				    create_tank_left(&tank, TRUE);
				}else{
				    create_tank_left(&tank, TRUE);
				    create_map(&map, TRUE);
				}
				break;
			case KEY_RIGHT:
		        //clear();
				create_tank_right(&tank, FALSE);
				++tank.startx;
				if(tank.startx + tank.width >= map.startx + MAP_WIDTH){
				    --tank.startx;
				    create_map(&map, TRUE);
				    create_tank_right(&tank, TRUE);
				}else{
				    create_tank_right(&tank, TRUE);
				    create_map(&map, TRUE);
				}
				break;
			case KEY_DOWN:
		        //clear();
				create_tank_down(&tank, FALSE);
				++tank.starty;
				if(tank.starty + tank.height >= map.starty + MAP_HEIGHT){
				    --tank.starty;
				    create_map(&map, TRUE);
				    create_tank_down(&tank, TRUE);
				}else{
				    create_tank_down(&tank, TRUE);
				    create_map(&map, TRUE);
				}
				break;
			case KEY_UP:
		        //clear();
				create_tank(&tank, FALSE);
				--tank.starty;
				if(tank.starty <= map.starty){
				    ++tank.starty;
				    create_map(&map, TRUE); 
				    create_tank(&tank, TRUE);
				}else{
				    create_tank(&tank, TRUE);
				    create_map(&map, TRUE);
				}
				break;
		}
	}
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
void init_map_params(MAP *p_map)
{
	p_map->height = MAP_HEIGHT;
	p_map->width = MAP_WIDTH;
	p_map->starty = (LINES - MAP_HEIGHT)-1;
	p_map->startx = (COLS - MAP_WIDTH)/2;

	p_map->border.ls = 'N';
	p_map->border.rs = 'N';
	p_map->border.ts = 'N';
	p_map->border.bs = 'N';
	p_map->border.tl = 'N';
	p_map->border.tr = 'N';
	p_map->border.bl = 'N';
	p_map->border.br = 'N';
}
void print_map_params(MAP *p_map)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_map->startx, p_map->starty, 
				p_map->width, p_map->height);
	refresh();
#endif
}
void create_map(MAP *p_map, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_map->startx;
	y = p_map->starty;
	w = p_map->width;
	h = p_map->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_map->border.tl); // augša kreisā
		mvaddch(y, x + w, p_map->border.tr); // augša labā
		mvaddch(y + h, x, p_map->border.bl); // kreisā apakša
		mvaddch(y + h, x + w, p_map->border.br); // labā apakša
		mvhline(y, x + 1, p_map->border.ts, w - 1); // augša
		mvhline(y + h, x + 1, p_map->border.bs, w - 1); // apakša
		mvvline(y + 1, x, p_map->border.ls, h - 1); // kreisā puse
		mvvline(y + 1, x + w, p_map->border.rs, h - 1); // labā puse

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}
void init_tank_params(TANK *p_tank)
{
	p_tank->height = 4;
	p_tank->width = 8;
	p_tank->starty = (LINES - p_tank->height)-2;	
	p_tank->startx = (COLS - p_tank->width)/2;

	p_tank->border.ls = '[';
	p_tank->border.rs = ']';
	p_tank->border.ts = '=';
	p_tank->border.bs = '=';
	p_tank->border.tl = '[';
	p_tank->border.tr = ']';
	p_tank->border.bl = '[';
	p_tank->border.br = ']';
	p_tank->border.gb = '+';
	p_tank->border.gm = 'o';
	p_tank->border.gt = 'x';
}
void print_tank_params(TANK *p_tank)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_tank->startx, p_tank->starty, 
				p_tank->width, p_tank->height);
	refresh();
#endif
}
void create_tank(TANK *p_tank, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_tank->startx;
	y = p_tank->starty;
	w = p_tank->width;
	h = p_tank->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_tank->border.tl); // augša kreisā
		mvaddch(y, x + w, p_tank->border.tr); // augša labā
		mvaddch(y + h, x, p_tank->border.bl); // kreisā apakša
		mvaddch(y + h, x + w, p_tank->border.br); // labā apakša
		mvhline(y, x + 1, p_tank->border.ts, w - 1); // augša
		mvhline(y + h, x + 1, p_tank->border.bs, w - 1); // apakša
		mvvline(y + 1, x, p_tank->border.ls, h - 1); // kreisā puse
		mvvline(y + 1, x + w, p_tank->border.rs, h - 1); // labā puse
		
		mvaddch(y, x + w/2, p_tank->border.gt); //stobra gals
		mvaddch(y+1, x + w/2, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2, p_tank->border.gb); // stobra apakša

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}
void create_tank_left(TANK *p_tank, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_tank->startx;
	y = p_tank->starty;
	w = p_tank->width;
	h = p_tank->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_tank->border.tl); // augša kreisā
		mvaddch(y, x + w, p_tank->border.tr); // augša labā
		mvaddch(y + h, x, p_tank->border.bl); // kreisā apakša
		mvaddch(y + h, x + w, p_tank->border.br); // labā apakša
		mvhline(y, x + 1, p_tank->border.ts, w - 1); // augša
		mvhline(y + h, x + 1, p_tank->border.bs, w - 1); // apakša
		mvvline(y + 1, x, p_tank->border.ls, h - 1); // kreisā puse
		mvvline(y + 1, x + w, p_tank->border.rs, h - 1); // labā puse

		mvaddch(y+2, x, p_tank->border.gt); //stobra gals
		mvaddch(y+2, x + w/2-1, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2-2, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2-3, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2, p_tank->border.gb); // stobra apakša
	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}
void create_tank_right(TANK *p_tank, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_tank->startx;
	y = p_tank->starty;
	w = p_tank->width;
	h = p_tank->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_tank->border.tl); // augša kreisā
		mvaddch(y, x + w, p_tank->border.tr); // augša labā
		mvaddch(y + h, x, p_tank->border.bl); // kreisā apakša
		mvaddch(y + h, x + w, p_tank->border.br); // labā apakša
		mvhline(y, x + 1, p_tank->border.ts, w - 1); // augša
		mvhline(y + h, x + 1, p_tank->border.bs, w - 1); // apakša
		mvvline(y + 1, x, p_tank->border.ls, h - 1); // kreisā puse
		mvvline(y + 1, x + w, p_tank->border.rs, h - 1); // labā puse

		mvaddch(y+2, x + w, p_tank->border.gt); //stobra gals
		mvaddch(y+2, x + w/2+1, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2+2, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2+3, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2, p_tank->border.gb); // stobra apakša
	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}
void create_tank_down(TANK *p_tank, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_tank->startx;
	y = p_tank->starty;
	w = p_tank->width;
	h = p_tank->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_tank->border.tl); // augša kreisā
		mvaddch(y, x + w, p_tank->border.tr); // augša labā
		mvaddch(y + h, x, p_tank->border.bl); // kreisā apakša
		mvaddch(y + h, x + w, p_tank->border.br); // labā apakša
		mvhline(y, x + 1, p_tank->border.ts, w - 1); // augša
		mvhline(y + h, x + 1, p_tank->border.bs, w - 1); // apakša
		mvvline(y + 1, x, p_tank->border.ls, h - 1); // kreisā puse
		mvvline(y + 1, x + w, p_tank->border.rs, h - 1); // labā puse

		mvaddch(y+h, x + w/2, p_tank->border.gt); //stobra gals
		mvaddch(y+h-1, x + w/2, p_tank->border.gm); // stobra vidus
		mvaddch(y+2, x + w/2, p_tank->border.gb); // stobra apakša
	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

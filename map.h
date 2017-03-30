#ifndef MAP_INCLUDED
#define MAP_INCLUDED
#include "map.h"
#include "tile.h"
#include "curses.h"
#include "globals.h"

/// globals

#define LEVEL_SIZE 1000
#define LEVEL_CENTER (LEVEL_SIZE / 2)

tile level[LEVEL_SIZE][LEVEL_SIZE];

/// structures

// screen structure used to hold the data about the screen to be rendered
typedef struct {
    // x offset of the level from 0
    // used for rendering
    int x;
    // y offset of the level from 0
    // used for rendering
    int y;
    // width of the screen
    int width;
    // height of the screen
    int height;
} screen;

/// function prototypes

void render_tile(int x, int y, tile *t, WINDOW* win);
void add_filled_room(int x_level, int y_level, int height, int width, tile *wall);
void add_room(int x_level, int y_level, int height, int width, tile *wall);
void add_hallway(int x_level, int y_level, int height, int width, int path_x_offset, int path_y_offset, int paths, tile *wall);
screen* create_screen();
void add_tile_to_level(int x, int y, tile *t);
int check_collision(int x, int y, int direction, tile *col_tile);
int check_collision_edge(int x, int y, int direction);

#endif // MAP_INCLUDED

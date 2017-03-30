#include "map.h"
#include <stdlib.h>
#include "player.h"

/// initialize a screen structure
screen* create_screen() {
    screen *s = malloc(sizeof(screen));
    s->x = LEVEL_CENTER;
    s->y = LEVEL_CENTER;
    s->width = (WIDTH / TILE_SIZE);
    s->height = (HEIGHT / TILE_SIZE);
}

void set_screen_pos(int x, int y, screen* s) {
    s->x = x;
    s->y = y;
}

/// initialize all the tiles in a level
// t the tile each tile to be initialize to
void initialize_level(tile *t) {
    int i, j;

    for(i = 0; i < LEVEL_SIZE; i++) {
        for(j = 0; j < LEVEL_SIZE; j++) {
            // set the dereferenced tile to be tile in the level
            level[i][j] = *t;
        }
    }
}

/// print the level using the current screen position
// s is the screen to be used
// win is the screen to be rendered too
void render_level(screen *s, WINDOW *win) {
    int i, j;
    // render the section of the level based on where the screen is
    for(i = 0; i < s->height; i++) {
        for(j = 0; j < s->width; j++) {
            // add the tile of were the screen is currently located
            render_tile(i * TILE_SIZE, j * TILE_SIZE, &level[s->x + i][s->y + j], win);
        }
    }
}

/// render tile at x and y coordinate
// uses the upper left hand corner as the starting point for rendering the tile
// x is the x cord of the screen
// y is the y cord of the screen
// t is the tile to be rendered
// win is the screen to be rendered too
void render_tile(int x, int y, tile *t, WINDOW *win) {
    int i, j;
    // iterate through all of the characters in the tile
    for(i = 0; i < TILE_SIZE; i++) {
        for(j = 0; j < TILE_SIZE; j++) {
            // put character in tile at proper location
            mvwaddch(win, y + i, x + j, t->data[i][j]);
        }
    }
}

/// add tile to the level
// x is the x cord of the level
// y is the x cord of the level
// t is the tile to be added
void add_tile_to_level(int x, int y, tile *t) {
    level[x][y] = *t;
}

/// check to see if collision has been detected
// 0 is there is no collision
// 1 is there was a collision
// x is the x cord of the collision to be checked against
// y is the y cord of the collision to be checked against
// direction is the direction of the collision
// col_tile is the tile to be checked against
int check_collision(int x, int y, int direction, tile *col_tile) {
    int collision = 0;

    // select direction for checking collision
    switch(direction) {
        // up
        case 1:
            // check if at the boundary
            if(y > 0) {
                // check tile above if it equals the tile to collide with
                if(compare_tile_data(&level[x][y-1], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // left
        case 2:
            // check if at the boundary
            if(x > 0) {
                // check tile left of if it equals the tile to collide with
                if(compare_tile_data(&level[x-1][y], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // down
        case 3:
            // check if at the boundary
            if(y < LEVEL_SIZE) {
                // check tile below it equals the tile to collide with
                if(compare_tile_data(&level[x][y+1], col_tile)) {
                    collision = 1;
                }
            }
            break;
        // right
        case 4:
            // check if at the boundary
            if(x < LEVEL_SIZE) {
                // check tile right of it equals the tile to collide with
                if(compare_tile_data(&level[x+1][y], col_tile)) {
                    collision = 1;
                }
            }
            break;
    }
    // return if it collided or not
    return collision;
}

/// check to see if collided with the edge has been detected
// 0 is there is no collision
// 1 is there was a collision
// x is the x cord of the collision to be checked against
// y is the y cord of the collision to be checked against
// direction is the direction of the collision
int check_collision_edge(int x, int y, int direction) {
    int collision = 0;

    // select direction for checking collision
    switch(direction) {
        // up
        case 1:
            // check if at the boundary
            if(y > 0) {
                collision = 1;
            }
            break;
        // left
        case 2:
            // check if at the boundary
            if(x > 0) {
                collision = 1;
            }
            break;
        // down
        case 3:
            // check if at the boundary
            if(y < LEVEL_SIZE) {
                collision = 1;
            }
            break;
        // right
        case 4:
            // check if at the boundary
            if(x < LEVEL_SIZE) {
                collision = 1;
            }
            break;
    }
    // return if it collided or not
    return collision;
}

void make_square(int x, int y, tile* wall)
{
    int width = rand()%5+1;
    int height = rand()%10+1;
    add_filled_room(x, y, width, height, wall);
}

void make_seven(int x, int y, tile* wall, player** p)
{
    int height = 14, width = 24;
    //add_room(x, y, height, width, wall);

    int direction = -1;

    int side = rand()%2;

    if (!(side%2))
        direction *= -1;

    int start_x = (direction*x < 0) ? x+width-1 : x;

    int start_y = rand()%10+1;
    int s_width = rand()%20+1;
    int s_height = y + start_y;
    int remainder = (rand()%(width - s_width)+1)+1;
    int dist = (width - s_width);


    for (int i = 0; i < s_width; i++) {
        add_tile_to_level(start_x + i*direction,  s_height, wall);
    }

    for (int i = 0; i < s_width + remainder; i++) {
        add_tile_to_level(start_x+i*direction, s_height + 2, wall);
    }

    for (int i = 0; i < start_y; i++) {
        add_tile_to_level(start_x + s_width*direction, s_height - i, wall);
    }

    for (int i = 0; i < start_y + 2; i++) {
        add_tile_to_level(start_x + (s_width + remainder)*direction, s_height + 2 - i, wall);
    }

    move_player(x+1, s_height+1, *p);
}

/// add a filled in room to the level
// uses the upper left hand corner as the starting point for rendering the room
// x_level is the x cord in the level
// y_level is the y cord in the level
// height is the height of the room
// width is the width of the room
// wall is the tile to be used for the wall of the room
void add_filled_room(int x_level, int y_level, int height, int width, tile *wall) {
    int i, j;

    // iterate through each position
    for(i = x_level; i < x_level + width; i++) {
        for(j = y_level; j < y_level + height; j++) {
            // add the tile
            add_tile_to_level(i, j, wall);
        }
    }
}

/// add a normal room
// uses the upper left hand corner as the starting point for rendering the room
// x_level is the x cord in the level
// y_level is the y cord in the level
// height is the height of the room
// width is the width of the room
// wall is the tile to be used for the wall of the room
void add_room(int x_level, int y_level, int height, int width, tile *wall) {
    int i, x = x_level, y = y_level;

    // add top wall
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level + (height - 1);
    // add bottom wall
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level;
    // add left wall
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }

    // set variables to proper values
    x = x_level + (width - 1);
    y = y_level;
    // add right wall
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x, y, wall);
        // update y position
        y++;
    }
}

void add_hallway(int x_level, int y_level, int height, int width, int path_x_offset, int path_y_offset, int paths, tile *wall) {
    int i, x = x_level, y = y_level;

    // add top part of hall along y axis
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y + path_y_offset, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level;
    // add top part of hall along y axis
    for(i = 0; i < width; i++) {
        // add the tile
        add_tile_to_level(x, y + 2 + path_y_offset, wall);
        // update x position
        x++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level;
    // add left part of hall along x axis
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x + path_x_offset, y, wall);
        // update y position
        y++;
    }

    // set variables to proper values
    x = x_level;
    y = y_level;
    // add right part of hall along x axis
    for(i = 0; i < height; i++) {
        // add the tile
        add_tile_to_level(x + 2 + path_x_offset, y, wall);
        // update y position
        y++;
    }
}

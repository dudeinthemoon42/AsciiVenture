#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <stdlib.h>
#include "globals.h"
#include "tile.h"
#include "curses.h"

/// structures

// player structure used to hold the data about the player
typedef struct {
    // x position of the player
    int x;
    // y position of the player
    int y;
    // direction of the player
    int direction;
    // player graphics
    tile *player_tile;
} player;

/// function prototypes

player* create_player(int x, int y, tile* t);
void move_player(int x, int y, player* p);
void render_player(player *p, tile* t, WINDOW *win);

#endif // PLAYER_H_INCLUDED

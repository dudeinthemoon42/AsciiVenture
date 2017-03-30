#include "player.h"

/// creates a new player
// x is x cord starting position of the player
// y is y cord starting position of the player
// t is the players graphics
player* create_player(int x, int y, tile* t) {
    player *p = malloc(sizeof(player));
    p->x = x;
    p->y = y;
    p->player_tile = t;
    p->direction = 0;
    return p;
}

/// move the player
// x is the new x position of the player
// y is the new y position of the player
void move_player(int x, int y, player* p) {
    p->x = x;
    p->y = y;
}

/// render the player
// p is the player to be rendered
// win is the screen to be rendered too
void render_player(player *p, tile* t, WINDOW *win) {
    // render the player
    add_tile_to_level(p->x, p->y, p->player_tile, win);

    // select direction for rendering
    // remove the old player text
    switch(p->direction) {
        // do nothing if no direction is set
        case 0:
            return;
        // up
        case 1:
            add_tile_to_level(p->x, p->y + 1, t, win);
            break;
        // left
        case 2:
            add_tile_to_level(p->x + 1, p->y, t, win);
            break;
        // down
        case 3:
            add_tile_to_level(p->x, p->y - 1, t, win);
            break;
        // right
        case 4:
            add_tile_to_level(p->x - 1, p->y, t, win);
            break;
    }
}

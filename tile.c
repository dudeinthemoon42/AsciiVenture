#include <stdlib.h>
#include <string.h>
#include "tile.h"

// create a tile
// bgcolor is the background color of the tile
// fgcolor is the forground color of the tile
// data is the character array of tile
// name is the name of the tile
tile* create_tile(int bgcolor, int fgcolor, char data[TILE_SIZE][TILE_SIZE], char *name) {
    tile *cur_tile = malloc(sizeof(tile));
    cur_tile->bgcolor = bgcolor;
    cur_tile->fgcolor = fgcolor;
    memcpy(cur_tile->data, data, TILE_SIZE * TILE_SIZE);
    cur_tile->name = name;
    return cur_tile;
}

/// compare a tiles foreground color
// first is the first tile to be compared
// second is the first tile to be compared
// 1 is they are equal
// 0 is they are not equal
int compare_tile_foreground(tile *first, tile* second) {
    if(first->fgcolor == second->fgcolor)
        return 1;
    return 0;
}

/// compare a tiles background color
// first is the first tile to be compared
// second is the first tile to be compared
// 1 is they are equal
// 0 is they are not equal
int compare_tile_background(tile *first, tile* second) {
    if(first->bgcolor == second->bgcolor)
        return 1;
    return 0;
}

/// compare a tiles character data
// first is the first tile to be compared
// second is the first tile to be compared
// 1 is they are equal
// 0 is they are not equal
int compare_tile_data(tile *first, tile* second) {
    int i, j, num_equal_chars = 0;

    for(i = 0; i < TILE_SIZE; i++) {
        for(j = 0; j < TILE_SIZE; j++) {
            // check if any character equals another
            if(first->data[i][j] == second->data[i][j])
                num_equal_chars++;
        }
    }
    // check if the num_equal_chars equals the total number of characters
    // in the character data set
    if(num_equal_chars == (TILE_SIZE * TILE_SIZE))
        return 0;
    return 1;
}

/// compare a tiles names
// first is the first tile to be compared
// second is the first tile to be compared
// 1 is they are equal
// 0 is they are not equal
int compare_tile_name(tile *first, tile* second) {
    if(strcmp(first->name, second->name))
        return 0;
    return 1;
}

#include <stdio.h>
#include "curses.h"
#include <SDL/SDL.h>
#include "tile.h"
#include "player.h"
#include "map.h"
#include "globals.h"
#include "read_tile.h"
#include <time.h>
#include <stdlib.h>

PDCEX SDL_Surface *pdc_screen;
int quit = 0, direction;
char input_char;

int main(int argc, char* args[])
{
    // make SDL not write stdout.txt and stderr.txt to the filesystem
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    // initialize SDL and quit if it failed
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        exit(1);

    // setup SDL window
    pdc_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_SWSURFACE | SDL_ANYFORMAT);

    // init PDCurses with proper settings
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));
    nodelay(stdscr, TRUE);
    noecho();

    // blank tile
    char blank_data[4][4] = {
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ',' ' },
        { ' ', ' ', ' ', ' ' }
    };

    // create blank tile
    tile *blank_tile = create_tile(COLOR_WHITE, COLOR_BLUE, blank_data, "blank");

    // test tile
    char tile_data[4][4] = {
        { '-', '-', '-', '-' },
        { '|', ' ', ' ', '|' },
        { '|', ' ', ' ','|' },
        { '-', '-', '-', '-' }
    };

    // create testing tile
    tile *test_tile = create_tile(COLOR_WHITE, COLOR_BLUE, tile_data, "test tile");

    // create player tile
    char player_data[4][4] = {
        { ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ' },
        { '?', '_', '_','O' },
        { '/', '\\', '/', '\\' }
    };

    // create player tile
    tile *player_tile = create_tile(COLOR_WHITE, COLOR_BLUE, player_data, "player");
    // create player
    player *player = create_player(LEVEL_CENTER + 1, LEVEL_CENTER + 1, player_tile);

    // create screen
    screen *current_screen = create_screen();
    // set all the tiles to be blank
    initialize_level(blank_tile);

    tile_list_t* tList = NULL;
    //tList = init_tiles();

    srand(time(NULL));

    set_screen_pos(LEVEL_CENTER, LEVEL_CENTER - 20, current_screen);
    make_seven(LEVEL_CENTER, LEVEL_CENTER - 20, test_tile, &player);

    // create a normal room
    add_room(LEVEL_CENTER, LEVEL_CENTER, 10, 30, test_tile);


    // main game loop
    while(!quit) {
        // get input character
        input_char = getch();
        switch(input_char) {
            // quit
            case 'q':
                quit = 1;
                break;
            // player up
            case 'w':
                player->direction = 1;
                // check if the players tile to be moved into is equal to the wall tile
                // if it is not, move the player
                // else do not move the player
                if(check_collision(player->x, player->y, player->direction, test_tile)) {
                    move_player(player->x, player->y - 1, player);
                } else {
                    player->direction = 0;
                }
                break;
            // player left
            case 'a':
                player->direction = 2;
                // check if the players tile to be moved into is equal to the wall tile
                // if it is not, move the player
                // else do not move the player
                if(check_collision(player->x, player->y, player->direction, test_tile)) {
                    move_player(player->x - 1, player->y, player);
                } else {
                    player->direction = 0;
                }
                break;
            // player down
            case 's':
                // check if the players tile to be moved into is equal to the wall tile
                // if it is not, move the player
                // else do not move the player
                player->direction = 3;
                if(check_collision(player->x, player->y, player->direction, test_tile)) {
                    move_player(player->x, player->y + 1, player);
                } else {
                    player->direction = 0;
                }
                break;
            // player right
            case 'd':
                player->direction = 4;
                // check if the players tile to be moved into is equal to the wall tile
                // if it is not, move the player
                // else do not move the player
                if(check_collision(player->x, player->y, player->direction, test_tile)) {
                    move_player(player->x + 1, player->y, player);
                } else {
                    player->direction = 0;
                }
                break;
            // camera up
            case 'i':
                // check if at the edge of the screen
                if(check_collision_edge(current_screen->x, current_screen->y, 1))
                    current_screen->y -= 1;
                break;
            // camera left
            case 'j':
                // check if at the edge of the screen
                if(check_collision_edge(current_screen->x, current_screen->y, 2))
                    current_screen->x -= 1;
                break;
            // camera down
            case 'k':
                // check if at the edge of the screen
                if(check_collision_edge(current_screen->x, current_screen->y, 3))
                    current_screen->y += 1;
                break;
            // camera right
            case 'l':
                // check if at the edge of the screen
                if(check_collision_edge(current_screen->x, current_screen->y, 4))
                    current_screen->x += 1;
                break;
        }

        // create a normal room
        //add_room(LEVEL_CENTER, LEVEL_CENTER, 10, 30, test_tile);

        //add_filled_room(LEVEL_CENTER - 10, LEVEL_CENTER - 10, 10, 30, test_tile);

        // render the player
        render_player(player, blank_tile, stdscr);
        // render the level
        render_level(current_screen, stdscr);
    }

    // cleanup
    endwin();
    SDL_Quit();
    return 0;
}

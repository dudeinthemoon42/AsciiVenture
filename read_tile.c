#include "read_tile.h"
#include "tile.h"
#include "curses.h"
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define BUFF_MAX 256

tile_list_t* init_tiles()
{
    tile_list_t* tList = malloc(sizeof(tile_list_t));
    FILE* fp;
    if (!(fp = fopen("shapes.txt", "r"))) {
        //printf("ERROR ACCESSING SHAPES FILE. EXITING.");
        mvaddstr(0, 0, "ERROR ACCESSING SHAPES FILE. EXITING.");
        char c = getch();
        SDL_Delay(1000);
        exit(4);
    }

    char fileData[TILE_SIZE][TILE_SIZE];

    int numShapes = 0, typeLen = 0;
    char name[BUFF_MAX], ch;
    char** types = malloc(BUFF_MAX * sizeof(char*));
    int i, j = 0;

    while(j < 3)
    {
        i = 0;
        // read in type of block (char) and the actual 4x4 block data
        while( (ch = fgetc(fp)) != '\n') {
            typeLen++;
        }
        //fseek(fp, 0, SEEK_SET);

        types[numShapes] = malloc(typeLen * sizeof(char));
        //fgets(type, typeLen * sizeof(char) + 1, fp);
        typeLen = 0;
        //ch = fgetc(fp);
        /*if ((ch = fgetc(fp)) != '\n') {
            printf("ERROR: CHARACTER FOUND PROCEEDING THE TYPE HEADER. PLEASE FORMAT SHAPES.TXT ACCORDING TO STANDARD. EXITING.")
            exit(5);
        }*/
        while (i < TILE_SIZE)
        {
            fgets(fileData[i], TILE_SIZE * sizeof(char) + 1, fp);
            ch = fgetc(fp); // get the fucking newline
            i++;
        }
        numShapes++;
        tile* t = create_tile(COLOR_WHITE, COLOR_BLUE, fileData, types[numShapes-1]);
        init_list(&tList, t, j);
        //render_tile(20, 10 + j*TILE_SIZE, t, stdscr);
        add_tile_to_level(LEVEL_CENTER + 5, LEVEL_CENTER + 5 + j, t);
        //ch = fgetc(fp);
        //init_list(tlist, fileData, type);
        j++;
    }
    return tList;
}

void init_list(tile_list_t** tList, tile** t, int j)
{
    if (j == 0)
    {
        //tList = malloc(sizeof(tile_list_t*));
        tile_node_t* tNode = malloc(sizeof(tile_node_t));
        tNode->data = *t;
        tNode->next = NULL;
        tNode->prev = NULL;
        (*tList)->head = malloc(sizeof(tile_node_t*));
        (*tList)->head = &tNode;
        (*tList)->last = malloc(sizeof(tile_node_t*));
        *((*tList)->last) = tNode;
        //(*tList)->last = (*tList)->head;
    }
    else
    {
        tile_node_t* tNode = malloc(sizeof(tile_node_t));
        tNode->data = *t;
        tNode->prev = (*tList)->last;
        tNode->next = NULL;
        //(*tList)->last->next = tNode;
        (*(*tList)->last)->next = tNode;
        (*tList)->last = &tNode;
        int i = 0;
    }
}

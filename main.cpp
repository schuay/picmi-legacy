/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Game.h"
#include <unistd.h>

SDL_Surface *Screen;

int main(int argc, char **argv) {

    int c,
        puzType = PUZ_RAND,
        puzDifficulty = 55;
    char *cvalue = NULL;

    while ((c = getopt(argc, argv, "shkr:")) != -1) {
        switch (c) {
        case 'r':
            puzType = PUZ_RAND;
            cvalue = optarg;
            puzDifficulty = atoi(cvalue);
            break;
        case 's':
            puzType = PUZ_STAT;
            break;
        case 'h':
        case '?':
            printf("\n"
                   "tuxpicross usage\n\n"
                   "mouse controls:\n"
                   "    left click: expose a tile\n"
                   "    right click: mark/unmark a tile\n\n"
                   "keyboard controls:\n"
                   "    arrow keys: move\n"
                   "    right ctrl: expose a tile\n"
                   "    right shift: mark/unmark a tile\n\n"
                   "arguments:\n"
                   "    -r num: generate random puzzle with percentage num of board filled \n"
                   "            for example, 'tuxpicross -r 60' will generate a random board with 60%% of all tiles filled\n"
                   "    -s: generate static puzzle (for debug purposes)\n"
                   "    -h: show this message\n");
            return -1;
            break;
        default:
            return -1;
        }
    }

    try {
        Game game;

        game.Initialize();  /* initialize video/audio subsystems, load sprites, etc... */
        game.NewPuzzle(puzType, puzDifficulty);

        while(!game.GetQuit()) {
                game.DoMainLoop();
                SDL_Flip(Screen);
        }

        SDL_Quit();

        return 0;
    }
    catch (PicrossException e) {
        printf("Error: %s", e.what());
    }
}


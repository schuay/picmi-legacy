/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_sdlfrontend.h"
#include <unistd.h>

SDL_Surface *Screen;

struct Settings {
    int puzType;
    int puzDifficulty;

    bool noHintsMode;

    unsigned int x;
    unsigned int y;

    Settings() {
        puzType = PUZ_RAND;
        puzDifficulty = 55;

        noHintsMode = false;

        x = 15;
        y = 15;
    }
};

bool HandleArguments(Settings& s, int argc, char **argv) {
    int c;
    char *cvalue = NULL;

    while ((c = getopt(argc, argv, "nshkr:x:y:")) != -1) {
        switch (c) {
        case 'r':
            s.puzType = PUZ_RAND;
            cvalue = optarg;
            s.puzDifficulty = atoi(cvalue);
            if (s.puzDifficulty == 0) {
                printf("Argument %c must be followed by an integer argument.", c);
                return false;
            }
            break;
        case 'x':
            cvalue = optarg;
            s.x = atoi(cvalue);
            if (s.x == 0) {
                printf("Argument %c must be followed by an integer argument.", c);
                return false;
            }
            break;
        case 'y':
            cvalue = optarg;
            s.y = atoi(cvalue);
            if (s.y == 0) {
                printf("Argument %c must be followed by an integer argument.", c);
                return false;
            }
            break;
        case 's':
            s.puzType = PUZ_STAT;
            break;
        case 'n':
            s.noHintsMode = true;
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
                   "    -x num: x dimension of generated puzzle (defaults to 15)\n"
                   "    -y num: y dimension of generated puzzle (defaults to 15)\n"
                   "    -n: enable no hints mode. incorrect tile marks are not prevented (default is disabled)\n"
                   "    -r num: generate random puzzle with percentage num of board filled \n"
                   "            for example, 'tuxpicross -r 60' will generate a random board with 60%% of all tiles filled\n"
                   "            (defaults to 55)\n"
                   "    -s: generate static puzzle (for debug purposes)\n"
                   "    -h: show this message\n");
            return false;
            break;
        default:
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv) {

    Settings s;
    if (!HandleArguments(s, argc, argv))
        return -1;

    try {
        SDLFrontend game;

        game.Initialize();  /* initialize video/audio subsystems, load sprites, etc... */
        game.NewPuzzle(s.puzType, s.puzDifficulty, s.noHintsMode, s.x, s.y);

        while(!game.GetQuit())
                game.DoMainLoop();

        return 0;
    }
    catch (PicException e) {
        printf("Error: %s", e.what());
        return 1;
    }
}


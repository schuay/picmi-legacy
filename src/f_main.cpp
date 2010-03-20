/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#define QTENABLED

#include <unistd.h>

#ifdef QTENABLED
#include <QtGui/QApplication>

#include "f_qtmainwindow.h"
#include "f_qtpicthread.h"
#else
#include "f_sdlfrontend.h"
#endif

SDL_Surface *Screen;

bool HandleArguments(PicSettings &s, bool &disableQt, int argc, char **argv);

int main(int argc, char **argv) {

    PicSettings s;
    bool disableQt = false;

    try {
        if (!HandleArguments(s, disableQt, argc, argv))
            return -1;

#ifdef QTENABLED
        if (disableQt) {
#endif
            SDLFrontend game(s);
            game.DoMainLoop();
#ifdef QTENABLED
        }
        else {
            QApplication a(argc, argv);
            QTMainWindow w(s);

            w.show();

            return a.exec();
        }
#endif
    }
    catch (PicException e) {
        printf("Error: %s\n\n", e.what());
        return 1;
    }
}

void ConvertPath(char *path) {
    std::string s = path;
    PicPngLoader loader;
    loader.ConvertPath(s, 30000);
}
bool HandleArguments(PicSettings &s, bool &disableQt, int argc, char **argv) {
    int c;
    char *cvalue = NULL;

    disableQt = false;

    while ((c = getopt(argc, argv, "qnhkr:x:y:s:t:c:")) != -1) {
        switch (c) {
        case 'r':
            s.Type = PUZ_RAND;
            cvalue = optarg;
            s.Difficulty = atoi(cvalue);
            if (s.Difficulty == 0) {
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
        case 'q':
            disableQt = true;
            break;
        case 'y':
            cvalue = optarg;
            s.y = atoi(cvalue);
            if (s.y == 0) {
                printf("Argument %c must be followed by an integer argument.", c);
                return false;
            }
            break;
        case 'c':
            cvalue = optarg;
            if (strlen(cvalue) == 0) {
                printf("Argument %c must be followed by an integer argument.", c);
                return false;
            }
            ConvertPath(cvalue);
            printf("Path converted successfully.");
            return false;
        case 's':
            cvalue = optarg;
            s.Type = PUZ_STAT;
            s.PuzzlePath = cvalue;
            break;
        case 't':
            cvalue = optarg;
            s.Type = PUZ_STAT;
            s.PuzzlePath = cvalue;
            s.LoadRandomFromPath = true;
            break;
        case 'n':
            s.NoHintsMode = true;
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
                   "    ctrl: expose a tile\n"
                   "    shift: mark/unmark a tile\n\n"
                   "arguments:\n"
                   "    -x num: x dimension of generated puzzle (defaults to 15)\n"
                   "    -y num: y dimension of generated puzzle (defaults to 15)\n"
                   "    -n: enable no hints mode. incorrect tile marks are not prevented (default is disabled)\n"
                   "    -r num: generate random puzzle with percentage num of board filled\n"
                   "            for example, 'tuxpicross -r 60' will generate a random board with 60%% of all tiles filled\n"
                   "            (defaults to 55)\n"
                   "    -s file: load puzzle from file (input file should be black and white .png)\n"
                   "    -t dir: load puzzle from a random file in dir\n"
                   "    -c dir: convert images from dir to a format suitable for puzzle input\n"
                   "            files are stored in $HOME/.config/tuxpicross/puzzles by default\n"
                   "    -q: disable QT frontend\n"
                   "    -h: show this message\n");
            return false;
            break;
        default:
            return false;
        }
    }

    return true;
}

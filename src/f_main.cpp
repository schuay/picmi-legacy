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

using namespace BoardGame;

bool HandleArguments(BoardSettings &s, bool &disableQt, int argc, char **argv);

int main(int argc, char **argv) {

    BoardSettings s(BoardSettings::Picross);
    bool disableQt = false;

    try {
        if (!HandleArguments(s, disableQt, argc, argv))
            return -1;

#ifdef QTENABLED
        if (disableQt) {
#endif
            GameManager game;
            game.Initialize(s);
            game.MainLoop();
#ifdef QTENABLED
        }
        else {
            QApplication a(argc, argv);
            QTMainWindow w;

            w.show();

            return a.exec();
        }
#endif
    }
    catch (Exception e) {
        printf("Error: %s\n\n", e.what());
        return 1;
    }
}

bool HandleArguments(BoardSettings &s, bool &disableQt, int argc, char **argv) {
    int c;
    char *cvalue = NULL;

    disableQt = false;

    while ((c = getopt(argc, argv, "qnhkr:x:y:s:t:c:")) != -1) {
        switch (c) {
        case 'r':
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
        case 'n':
            s.NoHintsMode = true;
            break;
        case 'h':
        case '?':
            printf("\n"
                   "picmi usage\n\n"
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
                   "            for example, 'picmi -r 60' will generate a random board with 60%% of all tiles filled\n"
                   "            (defaults to 55)\n"
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


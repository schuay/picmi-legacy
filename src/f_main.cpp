/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include <unistd.h>

#include <QtGui/QApplication>

#include "f_qtmainwindow.h"
#include "f_qtpicthread.h"

using namespace BoardGame;

bool HandleArguments(int argc, char **argv);

int main(int argc, char **argv) {

    try {
        if (!HandleArguments(argc, argv))
            return -1;

        QApplication a(argc, argv);
        QTMainWindow w;

        w.show();

        return a.exec();
    }
    catch (Exception e) {
        printf("Error: %s\n\n", e.what());
        return 1;
    }
}

bool HandleArguments(int argc, char **argv) {
    int c;

    while ((c = getopt(argc, argv, "h")) != -1) {
        switch (c) {
        case 'h':
        case '?':
            printf("\n"
                   "picmi usage\n\n"
                   "global\n\n"
                   "    p: (un)pause game\n"
                   "    esc: quit game\n\n"
                   "picross\n\n"
                   "mouse controls:\n"
                   "    left click: expose a tile\n"
                   "    right click: mark/unmark a tile\n\n"
                   "keyboard controls:\n"
                   "    arrow keys: move\n"
                   "    ctrl: (un)mark a tile\n"
                   "    space: expose a tile\n\n"
                   "minesweeper\n\n"
                   "mouse controls:\n"
                   "    left click (on an unexposed tile): expose a tile\n"
                   "    left click (on an exposed tile): expose all neighboring tiles\n"
                   "    right click: (un)mark a tile\n"
                   "    middle click: tentatively (un)mark a tile\n\n"
                   "keyboard controls:\n"
                   "    arrow keys: move\n"
                   "    ctrl: (un)mark a tile\n"
                   "    space (on an unexposed tile): expose a tile\n"
                   "    space (on an exposed tile): expose all neighboring tiles\n\n"
                   "arguments:\n"
                   "    -h: show this message\n\n");
            return false;
            break;
        default:
            return false;
        }
    }

    return true;
}


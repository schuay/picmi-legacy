/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

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
                   "usage\n"
                   "    please check ingame help for more information\n\n"
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


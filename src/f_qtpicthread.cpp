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

#include "f_qtpicthread.h"

namespace BoardGame {
QTPicThread::QTPicThread()
{
    settings = NULL;
}
QTPicThread::~QTPicThread() {
    if (settings)
        delete settings;
}

void QTPicThread::PassSettings(BoardSettings *s) {
    if (settings) {
        delete settings;
        settings = NULL;
    }

    settings = s;
}
void QTPicThread::run() {
    GameManager game;
    try {
        do {
            game.Initialize(*settings);
            game.MainLoop();
        }
        while (game.Retry());
    }
    catch (Exception e) {
        emit ExceptionThrown(QString(e.what()));
    }
}
}

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_qtpicthread.h"

QTPicThread::QTPicThread()
{
    settings = NULL;
}
QTPicThread::~QTPicThread() {
    if (settings)
        delete settings;
}

void QTPicThread::PassSettings(PicSettings *s) {
    if (settings) {
        delete settings;
        settings = NULL;
    }

    settings = s;
}
void QTPicThread::run() {
    GameManager game(*settings);
    game.MainLoop();
}

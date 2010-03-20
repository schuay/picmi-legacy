/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <sstream>
#include <iomanip>

#include "b_picinputhandler.h"
#include "b_picross.h"
#include "b_picpngloader.h"
#include "b_picpainter.h"

#define WINDOWCAPTION "Tux Picross"

class SDLFrontend {
public:

    SDLFrontend(PicSettings &s);
    ~SDLFrontend();

    void DoMainLoop();

private:

    void Initialize();

    void GameWon();

    BoardGame *game;
    Painter *painter;
    InputHandler *inputhandler;
};

#endif // GAME_H

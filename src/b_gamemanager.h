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

#include "b_sweeper.h"
#include "b_sweeppainter.h"
#include "b_sweepinputhandler.h"
#include "b_picinputhandler.h"
#include "b_picross.h"
#include "b_picpainter.h"

#define WINDOWCAPTION "Tux Picross"
namespace BoardGame {
class GameManager {
public:

    GameManager(BoardSettings &s);
    ~GameManager();

    void MainLoop();

private:

    void InitSystems();

    void GameOver();

    BoardGame *game;
    Painter *painter;
    InputHandler *inputhandler;
};
}
#endif // GAME_H

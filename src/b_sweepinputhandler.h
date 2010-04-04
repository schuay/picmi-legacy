/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPINPUTHANDLER_H
#define B_SWEEPINPUTHANDLER_H

#include <SDL/SDL.h>

#include "b_sweeper.h"
#include "b_inputhandler.h"

namespace BoardGame {
    class SweepInputHandler : public InputHandler
    {
    public:
        SweepInputHandler(BoardGame *p);

        void HandleInput();

    private:

        void InitSystems();

        int HandleMouseEvent(const int x, const int y, const int btn);

        Sweeper* game;
    };
}
#endif // B_SWEEPINPUTHANDLER_H

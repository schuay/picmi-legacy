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

#ifndef B_SWEEPINPUTHANDLER_H
#define B_SWEEPINPUTHANDLER_H

#include "b_sweeper.h"
#include "b_inputhandler.h"
#include "b_draghelper.h"

namespace BoardGame {
    class SweepInputHandler : public InputHandler
    {
    public:
        SweepInputHandler(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p);

        void HandleInput();

    private:

        int HandleMouseEvent(int x, int y, sf::Mouse::Button btn, sf::Event::EventType event);

        Sweeper* game;

        DragHelper dragHelper;
    };
}
#endif // B_SWEEPINPUTHANDLER_H

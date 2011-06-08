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

#ifndef B_PICINPUTHANDLER_H
#define B_PICINPUTHANDLER_H

#include "b_picross.h"
#include "b_inputhandler.h"

#define DRAG_UNDEF -1           // defines for drag locking
#define DRAG_HOR 0
#define DRAG_VER 1

namespace BoardGame {
class PicInputHandler : public InputHandler
{
public:
    PicInputHandler(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p);

    void HandleInput();

private:

    int HandleMouseEvent(const int x, const int y, const sf::Mouse::Button btn, const sf::Event::EventType event);

    sf::Vector2i
        lastClickLocation,
        lastDragLocation;

    int dragDirection,
        dragOperation;

    Picross* game;

    bool
            lmbPressed,
            rmbPressed;
};
}
#endif // B_PICINPUTHANDLER_H

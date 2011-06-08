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

#ifndef B_DRAGHELPER_H
#define B_DRAGHELPER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib>

enum DragDirection {
    DRAG_UNDEF,
    DRAG_HORIZONTAL,
    DRAG_VERTICAL
};

namespace BoardGame {
class DragHelper
{
public:

    DragHelper();

    void begin(sf::Vector2i pos, sf::Mouse::Button button, int op);
    void reset();
    sf::Vector2i update(sf::Vector2i pos);

    sf::Mouse::Button getButton() const { return button; }
    int getOperation() const { return dragOp; }
    sf::Vector2i getPosition() const { return last; }
    bool nothingTobeDone() const { return !posChanged; }

    void setLockToLine(bool b) { lockToLine = b; }

private:
    sf::Vector2i lastClick, last;
    DragDirection direction;
    sf::Mouse::Button button;
    int dragOp;
    bool posChanged;

    bool lockToLine;
};
}
#endif // B_DRAGHELPER_H

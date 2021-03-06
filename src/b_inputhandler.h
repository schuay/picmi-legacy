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

#ifndef B_INPUTHANDLER_H
#define B_INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

using boost::shared_ptr;

namespace BoardGame {
class InputHandler
{
public:

    InputHandler(shared_ptr<sf::RenderWindow> &application) : app(application) { }

    virtual void HandleInput() = 0;

    shared_ptr<sf::RenderWindow> app;
};
}
#endif // B_INPUTHANDLER_H

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

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>

#include "b_sweeper.h"
#include "b_sweeppainter.h"
#include "b_sweepinputhandler.h"
#include "b_picinputhandler.h"
#include "b_picross.h"
#include "b_picpainter.h"
#include "b_statsmanager.h"

using boost::shared_ptr;

namespace BoardGame {
class GameManager {
public:

    void MainLoop();
    void Initialize(BoardSettings &s);

    bool Retry() { return retry; }

private:

    void InitSystems();

    void GameOver();

    bool retry;

    shared_ptr<BoardGame> game;
    shared_ptr<Painter> painter;
    shared_ptr<InputHandler> inputhandler;

    shared_ptr<sf::RenderWindow> app;
};
}
#endif // GAME_H

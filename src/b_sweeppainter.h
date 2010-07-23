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

#ifndef B_SWEEPPAINTER_H
#define B_SWEEPPAINTER_H

#include <sstream>
#include <iomanip>

#include "b_painter.h"
#include "b_sweeper.h"
#include "b_sdlsprite.h"
#include "b_sdltext.h"

namespace BoardGame {

class SweepPainter : public Painter
{
public:
    SweepPainter(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> p, BoardSettings &s);

    void Paint();

protected:

    void PaintBoardArea();
    void PaintInfoArea();

    virtual std::string GetGameOverText(StatsCollection c);

    void LoadSprites();
    void InitSystems();

    /* all sprites used in the game */
    SDLSprite
            sprCellFrame,
            sprActiveTile,
            sprClearTile,
            sprMarkedTile,
            sprTentativeTile,
            sprBomb,
            sprExposedTile,
            sprNumbers[7],
            sprIcon;

    Sweeper *game;
};

}

#endif // B_SWEEPPAINTER_H

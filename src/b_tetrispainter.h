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

#ifndef B_TETRISPAINTER_H
#define B_TETRISPAINTER_H

#include "b_painter.h"
#include "b_tetris.h"

namespace BoardGame {

class TetrisPainter : public Painter
{
public:
    TetrisPainter(BoardGame *p, BoardSettings &s);

    void Paint();

protected:

    std::string GetGameOverText(StatsCollection c);

    void PaintBoardArea();
    void PaintInfoArea();

    void InitSystems();
    void LoadSprites();

    Tetris *game;

    SDLSprite
            sprIcon,
            sprBackgroundTile,
            sprITile,
            sprJTile,
            sprLTile,
            sprOTile,
            sprSTile,
            sprTTile,
            sprZTile;
};

}

#endif // B_TETRISPAINTER_H

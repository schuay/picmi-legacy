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

#ifndef B_PICPAINTER_H
#define B_PICPAINTER_H

#include "b_painter.h"
#include "b_picross.h"

namespace BoardGame {
class PicPainter : public Painter
{
public:
    PicPainter(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p, BoardSettings &s);

    void Paint();

    void ResetGame(shared_ptr<BoardGame> &p);

private:

    void PaintInfoArea();
    void PaintStreakArea();
    void PaintBoardArea();

    virtual std::string GetGameOverText(StatsCollection c);

    void LoadSprites();

    /* all sprites used in the game */
    Sprite
            sprCellFrame,
            sprBoxTile,
            sprMarkTile,
            sprDividerR,
            sprDividerD,
            sprDividerL,
            sprDividerU,
            sprActiveTile,
            sprStreakAreaHorA,
            sprStreakAreaHorB,
            sprStreakAreaVerA,
            sprStreakAreaVerB,
            sprIcon;

    /* the game instance - painter reads state from here and paints accordingly */
    Picross *game;
};
}
#endif // B_PICPAINTER_H

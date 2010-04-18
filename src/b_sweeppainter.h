/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPPAINTER_H
#define B_SWEEPPAINTER_H

#include <SDL/SDL.h>
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
    SweepPainter(BoardGame *p, BoardSettings &s);

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

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SDLPAINTER_H
#define B_SDLPAINTER_H

#include "b_painter.h"
#include "b_picross.h"

namespace BoardGame {
class PicPainter : public Painter
{
public:
    PicPainter(BoardGame *p, BoardSettings &s);

    void Paint();

private:

    void PaintInfoArea();
    void PaintStreakArea();
    void PaintBoardArea();

    /* (initialize sdl video systems */
    void InitSystems();

    void LoadSprites();

    /* all sprites used in the game */
    SDLSprite
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
#endif // B_SDLPAINTER_H

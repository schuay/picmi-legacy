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

#include <SDL/SDL.h>
#include <sstream>
#include <iomanip>

#include "b_painter.h"
#include "b_picross.h"
#include "b_sdlsprite.h"
#include "b_sdltext.h"

#define FILEPREFIX ""               /* set the location of gfx and fonts */
namespace BoardGame {
class PicPainter : public Painter
{
public:
    PicPainter(BoardGame *p, std::string customBackground);
    ~PicPainter();

    void LoadCustomBackground(std::string path);

    void Paint();

private:

    void PaintBackground();
    void PaintInfoArea();
    void PaintStreakArea();
    void PaintBoardArea();

    /* (de)initialize sdl systems (including global sdl + key repeat settings) */
    void InitSystems();


    virtual void LoadSprites();


    /* the screen surface - everything is blitted to this */
    SDL_Surface *screen;


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
            sprBackground,
            sprIcon;

    /* text object  */
    SDLText txt;

    /* the game instance - painter reads state from here and paints accordingly */
    Picross *game;
};
}
#endif // B_SDLPAINTER_H

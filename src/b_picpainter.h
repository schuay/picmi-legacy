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
#include "f_sdlsprite.h"
#include "f_sdltext.h"

#define FILEPREFIX ""               /* set the location of gfx and fonts */
#define GAMETITLE  "Tux Picross"    /* window caption */

class PicPainter : public Painter
{
public:
    PicPainter(Picross *p);
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
    void DeinitSystems();


    /* all sprites are (un)loaded here */
    virtual void LoadSprites();
    void UnloadSprites();


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

    /* size of tiles in pixels */
    static const unsigned int celllength = 24;

    /* upper left corner of board */
    static const unsigned int boardX = 200;
    static const unsigned int boardY = 200;

    /* zoom */
    static const unsigned int zoom = 1;
};

#endif // B_SDLPAINTER_H

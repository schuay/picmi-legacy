/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_PAINTER_H
#define B_PAINTER_H

#include <SDL/SDL.h>
#include <sstream>
#include <iomanip>

#include "SDL/SDL.h"
#include "b_sdlsprite.h"
#include "b_sdltext.h"

#define FILEPREFIX ""               /* set the location of gfx and fonts */

namespace BoardGame {
class Painter
{
public:
    Painter();
    virtual ~Painter();

    virtual void Paint() = 0;

protected:

    void PaintBackground();
    void PaintGameOverScreen();

    void LoadCustomBackground(std::string path);

    virtual void LoadSprites() = 0;

    /* the screen surface - everything is blitted to this */
    SDL_Surface *screen;

    /* text object  */
    SDLText txt;

    SDLSprite sprBackground;
};
}
#endif // B_PAINTER_H

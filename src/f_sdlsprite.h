/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>

#include "f_sdlglobals.h"
#include "b_picpoint.h"
#include "b_picexception.h"

#define JUSTIFY_LT   0
#define JUSTIFY_LB   1
#define JUSTIFY_RT   2
#define JUSTIFY_RB   3

class SDLSprite
{
public:
    SDLSprite();
    ~SDLSprite();

    void SetAsIcon();
    void Load(std::string Filename, unsigned int Zoom, unsigned int Rotation);
    void Blit(SDL_Surface *target, PicPoint p, int justify = JUSTIFY_LT);

private:

    void Zoom(unsigned int Zoom);
    void Rotate(unsigned int Rotation); /* customized for my needs, 90/180/270 degrees and square sprites only */

    SDL_Surface *Surface;
};

#endif // SPRITE_H

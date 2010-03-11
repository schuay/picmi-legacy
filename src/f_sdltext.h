/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "b_picpoint.h"
#include "b_picexception.h"
#include "f_sdlglobals.h"

#define JUSTIFY_C   0
#define JUSTIFY_L   1
#define JUSTIFY_R   2

class SDLText
{
public:
    SDLText();
    ~SDLText();

    void Load(std::string Filename);
    void Blit(std::string txt, PicPoint p, unsigned int justify = JUSTIFY_L);
    void Blit(std::string txt, PicPoint p, SDL_Color c, unsigned int justify = JUSTIFY_L);

    int WidthOf(std::string txt);
    int HeightOf(std::string txt);

    static const unsigned int Size = 18;

private:
    TTF_Font *font;
};

#endif // TEXT_H

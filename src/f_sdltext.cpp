/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_sdltext.h"

SDLText::SDLText()
{
    font = NULL;
}

SDLText::~SDLText() {
    if (font)
        TTF_CloseFont(font);

}

void SDLText::Load(std::string Filename) {
    if (font)
        throw PicException("Font already loaded, Text::Load cannot be called twice.");

    font = TTF_OpenFont(Filename.c_str(), Size);

    if (!font)
        throw PicException(TTF_GetError());
}

int SDLText::WidthOf(std::string txt) {
    int w;

    TTF_SizeText(font, txt.c_str(), &w, NULL);

    return w;
}
int SDLText::HeightOf(std::string txt) {
    int h;

    TTF_SizeText(font, txt.c_str(), NULL, &h);

    return h;
}

void SDLText::Blit(std::string txt, PicPoint p, unsigned int justify) {
    SDL_Color c = {0,0,0};
    Blit(txt, p, c, justify);
}
void SDLText::Blit(std::string txt, PicPoint p, SDL_Color c, unsigned int justify) {
    if (!font)
        throw PicException("Text::Blit failed, no font loaded.");

    SDL_Rect to;
    SDL_Surface *s = NULL;

    s = TTF_RenderText_Solid(
            font,
            txt.c_str(),
            c);

    to.w = to.h = 1000; //should be enough to draw all strings
    to.y = p.y;
    if (justify == JUSTIFY_R)
        to.x = p.x - s->w;
    else if (justify == JUSTIFY_C)
        to.x = p.x - s->w / 2;
    else
        to.x = p.x;

    if (!s)
        throw PicException("Text::Blit failed, TTF_RenderText failed");

    SDL_BlitSurface(s, NULL, Screen, &to);
    SDL_FreeSurface(s);
}

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sdltext.h"
namespace BoardGame {
SDLText::SDLText()
{
    Size = 17;
}

void SDLText::Load(std::string fnNormal, std::string fnBold, std::string fnItalic, unsigned int size) {
    if (fontNormal)
        throw Exception("Font already loaded, Text::Load cannot be called twice.");

    Size = size;

    fontNormal.reset(TTF_OpenFont(fnNormal.c_str(), Size), TTF_CloseFont);
    fontBold.reset(TTF_OpenFont(fnBold.c_str(), Size), TTF_CloseFont);
    fontItalic.reset(TTF_OpenFont(fnItalic.c_str(), Size), TTF_CloseFont);

    if (!fontNormal || !fontBold || !fontItalic)
        throw Exception(TTF_GetError());
}

int SDLText::WidthOf(std::string txt, unsigned int fontType) {
    int w;

    TTF_SizeText(GetFontForType(fontType).get(), txt.c_str(), &w, NULL);

    return w;
}
int SDLText::HeightOf(std::string txt, unsigned int fontType) {
    int h;

    TTF_SizeText(GetFontForType(fontType).get(), txt.c_str(), NULL, &h);

    return h;
}

void SDLText::Blit(boost::shared_ptr<SDL_Surface> target, std::string txt, Point p, unsigned int fontType, unsigned int justify) {
    SDL_Color c;

    c.r = c.g = c.b = 0;
    Blit(target, txt, p, c, fontType, justify);
}
void SDLText::Blit(boost::shared_ptr<SDL_Surface> target, std::string txt, Point p, SDL_Color c, unsigned int fontType, unsigned int justify) {
    if (!fontNormal || !fontBold || !fontItalic)
        throw Exception("Text::Blit failed, no font loaded.");

    if (txt.length() == 0)
        return;

    SDL_Rect to;
    boost::shared_ptr<SDL_Surface> s(
            TTF_RenderText_Solid(GetFontForType(fontType).get(), txt.c_str(), c),
            SDL_FreeSurface);

    to.w = to.h = 1000; //should be enough to draw all strings
    to.y = p.y;
    if (justify == JUSTIFY_R)
        to.x = p.x - s->w;
    else if (justify == JUSTIFY_C)
        to.x = p.x - s->w / 2;
    else
        to.x = p.x;

    if (!s)
        throw Exception("Text::Blit failed, TTF_RenderText failed");

    SDL_BlitSurface(s.get(), NULL, target.get(), &to);
}

boost::shared_ptr<TTF_Font> SDLText::GetFontForType(unsigned int fontType) {
    if (fontType != FONT_NORMAL && fontType != FONT_BOLD && fontType != FONT_ITALIC)
        throw Exception("Invalid font type passed.");

    switch (fontType) {
    case FONT_NORMAL:
        return fontNormal;
    case FONT_BOLD:
        return fontBold;
    case FONT_ITALIC:
    default:
        return fontItalic;
    }
}
}

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

int SDLText::WidthOf(std::string txt, FontTypeEnum fontType) {
    int w;

    TTF_SizeText(GetFontForType(fontType).get(), txt.c_str(), &w, NULL);

    return w;
}
int SDLText::HeightOf(std::string txt, FontTypeEnum fontType) {
    int h;

    TTF_SizeText(GetFontForType(fontType).get(), txt.c_str(), NULL, &h);

    return h;
}

void SDLText::BlitLine(shared_ptr<SDL_Surface> target, std::string txt, Point p, SDL_Color c, FontTypeEnum fontType, TextJustifyEnum justify) {
    if (!fontNormal || !fontBold || !fontItalic)
        throw Exception("Text::Blit failed, no font loaded.");

    if (txt.length() == 0)
        return;

    SDL_Rect to;
    shared_ptr<SDL_Surface> s(
            TTF_RenderText_Solid(GetFontForType(fontType).get(), txt.c_str(), c),
            SDL_FreeSurface);

    if (!s)
        throw Exception("Text::Blit failed, TTF_RenderText failed");

    to.w = to.h = 1000; //should be enough to draw all strings
    to.y = p.y;
    if (justify == TJ_RIGHT)
        to.x = p.x - s->w;
    else if (justify == TJ_CENTER)
        to.x = p.x - s->w / 2;
    else
        to.x = p.x;

    SDL_BlitSurface(s.get(), NULL, target.get(), &to);
}

shared_ptr<TTF_Font> SDLText::GetFontForType(unsigned int fontType) {
    switch (fontType) {
    case FT_NORMAL:
        return fontNormal;
    case FT_BOLD:
        return fontBold;
    case FT_ITALIC:
    default:
        return fontItalic;
    }
}

void SDLText::Blit(shared_ptr<SDL_Surface> dst, std::string text, Point &p, SDL_Color &c, FontTypeEnum fontType, TextJustifyEnum justify) {

    QString qtext(text.c_str());
    QStringList qsplittext = qtext.split('\n');
    unsigned int textHeight = HeightOf(text, fontType);

    for (int i = 0; i < qsplittext.count(); i++) {
        BlitLine(dst, qsplittext.at(i).toStdString(), p, c, fontType, justify);
        p.y += textHeight;
    }
}
}

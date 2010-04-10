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
#include <boost/shared_ptr.hpp>

#include "b_point.h"
#include "b_exception.h"

#define JUSTIFY_C   0
#define JUSTIFY_L   1
#define JUSTIFY_R   2

#define FONT_NORMAL 0
#define FONT_BOLD   1
#define FONT_ITALIC 2

namespace BoardGame {
class SDLText
{
public:
    SDLText();

    void Load(std::string fnNormal, std::string fnBold, std::string fnItalic, unsigned int size = 17);
    void Blit(boost::shared_ptr<SDL_Surface> target, std::string txt, Point p, unsigned int fontType, unsigned int justify = JUSTIFY_L);
    void Blit(boost::shared_ptr<SDL_Surface> target, std::string txt, Point p, SDL_Color c, unsigned int fontType, unsigned int justify = JUSTIFY_L);

    int WidthOf(std::string txt, unsigned int fontType = FONT_NORMAL);
    int HeightOf(std::string txt, unsigned int fontType = FONT_NORMAL);

private:
    unsigned int Size;

    boost::shared_ptr<TTF_Font> GetFontForType(unsigned int fontType);

    boost::shared_ptr<TTF_Font>
            fontNormal,
            fontBold,
            fontItalic;
};
}
#endif // TEXT_H

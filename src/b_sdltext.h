/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <QString>
#include <QStringList>

#include "b_enums.h"
#include "b_point.h"
#include "b_exception.h"

using boost::shared_ptr;

namespace BoardGame {
class SDLText
{
public:
    SDLText();

    void Load(std::string fnNormal, std::string fnBold, std::string fnItalic, unsigned int size = 17);

    /* multiline text writing */
    void Blit(shared_ptr<SDL_Surface> dst, std::string text, Point &p, SDL_Color &c, FontTypeEnum fontType, TextJustifyEnum justify = TJ_LEFT);

    int WidthOf(std::string txt, FontTypeEnum fontType = FT_NORMAL);
    int HeightOf(std::string txt, FontTypeEnum fontType = FT_NORMAL);

private:
    unsigned int Size;

    void BlitLine(shared_ptr<SDL_Surface> target, std::string txt, Point p, SDL_Color c, FontTypeEnum fontType, TextJustifyEnum justify);

    shared_ptr<TTF_Font> GetFontForType(unsigned int fontType);

    shared_ptr<TTF_Font>
            fontNormal,
            fontBold,
            fontItalic;
};
}
#endif // TEXT_H

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

#include "b_text.h"

namespace BoardGame {

void Text::Load(std::string fnNormal, std::string fnBold, std::string fnItalic, unsigned int pt) {

    size = pt;

    if (!fontNormal.loadFromFile(fnNormal) ||
        !fontBold.loadFromFile(fnBold) ||
        !fontItalic.loadFromFile(fnItalic))
        throw Exception("Loading fonts failed.");

    string.setFont(fontNormal);
    string.setCharacterSize(size);
}

unsigned int Text::WidthOf(std::string txt, FontTypeEnum fontType) {

    SetFontType(fontType);
    string.setString(txt);

    return string.getLocalBounds().width;
}

unsigned int Text::HeightOf(std::string txt, FontTypeEnum fontType) {

    SetFontType(fontType);
    string.setString(txt);

    return string.getLocalBounds().height;
}

void Text::SetFontType(FontTypeEnum fontType) {

    if (fontType == FT_NORMAL)
        string.setFont(fontNormal);
    else if (fontType == FT_BOLD)
        string.setFont(fontBold);
    else if (fontType == FT_ITALIC)
        string.setFont(fontItalic);

}

void Text::Blit(shared_ptr<sf::RenderWindow> dest, std::string txt, sf::Vector2i &p, const sf::Color &c,
                   FontTypeEnum fontType, TextJustifyEnum justify) {

    SetFontType(fontType);
    string.setColor(c);

    /* justification only works on entire string, not line by line */

    int x = p.x;
    switch (justify) {
    case TJ_CENTER:
        x = p.x - WidthOf(txt, fontType) / 2;
        break;
    case TJ_RIGHT:
        x = p.x - WidthOf(txt, fontType);
        break;
    default:
        break;
    }

    string.setPosition(x, p.y);
    string.setString(txt);

    dest->draw(string);
}

}

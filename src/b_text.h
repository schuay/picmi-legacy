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

#include <SFML/Graphics.hpp>
#include <string>
#include <boost/shared_ptr.hpp>

#include "b_enums.h"
#include "b_point.h"
#include "b_exception.h"

using boost::shared_ptr;

namespace BoardGame {
class Text
{
public:

    void Load(std::string fnNormal, std::string fnBold, std::string fnItalic, unsigned int pt = 12);

    /* multiline text writing */
    void Blit(shared_ptr<sf::RenderWindow> dst, std::string txt, Point &p, const sf::Color &c = sf::Color::Black,
              FontTypeEnum fontType = FT_NORMAL, TextJustifyEnum justify = TJ_LEFT);

    int WidthOf(std::string txt, FontTypeEnum fontType = FT_NORMAL);
    int HeightOf(std::string txt, FontTypeEnum fontType = FT_NORMAL);

private:

    void SetFontType(FontTypeEnum fontType);

    unsigned int
            size;

    sf::String
            string;

    sf::Font
            fontNormal,
            fontBold,
            fontItalic;
};
}
#endif // TEXT_H

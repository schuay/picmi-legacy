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

#ifndef B_PAINTER_H
#define B_PAINTER_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include <boost/shared_ptr.hpp>

#include "b_boardgame.h"
#include "b_sprite.h"
#include "b_text.h"
#include "b_statscollection.h"
#include "config.h"

using boost::shared_ptr;

#define WINDOWTITLE "picmi"

namespace BoardGame {
class Painter
{
public:
    Painter(shared_ptr<sf::RenderWindow> &application);

    virtual void Paint() = 0;
    virtual void PaintGameOverScreen(StatsCollection c);
    virtual void PaintPauseScreen();

    virtual void ResetGame(shared_ptr<BoardGame> &p) = 0;

protected:

    void PaintBackground();

    void LoadCustomBackground(std::string path);

    virtual std::string GetGameOverText(StatsCollection c) = 0;

    virtual void LoadSprites() = 0;

    void InitSystems();

    shared_ptr<sf::RenderWindow> app;

    unsigned int
            nativeWidth,
            nativeHeight;

    /* text object  */
    Text txt;

    Sprite sprBackground;
};
}
#endif // B_PAINTER_H

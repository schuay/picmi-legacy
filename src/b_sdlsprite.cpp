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

#include "b_sdlsprite.h"
namespace BoardGame {

void SDLSprite::SetAsIcon(shared_ptr<sf::RenderWindow> target) const {

    target->SetIcon(
            Image.GetWidth(),
            Image.GetHeight(),
            Image.GetPixelsPtr());

}

void SDLSprite::Load(std::string Filename, unsigned int Angle) {

    if (!Image.LoadFromFile(Filename))
        throw Exception("Loading sprite failed.");

    Rotation = Angle;

    Surface.reset(new sf::Sprite(Image));

    Surface->SetRotation(Rotation);
}

void SDLSprite::Blit(shared_ptr<sf::RenderWindow> target, Point p) {

    /* rotation is done around pt 0,0, so we need to draw with offsets */

    int
            xOffset = 0,
            yOffset = 0;

    switch (Rotation) {
    case 90:
        yOffset = Image.GetWidth();
        break;
    case 180:
        xOffset = Image.GetHeight();
        yOffset = Image.GetWidth();
        break;
    case 270:
        xOffset = Image.GetHeight();
        break;
    }

    Surface->SetPosition(p.x + xOffset, p.y + yOffset);

    target->Draw(*Surface.get());
}

}

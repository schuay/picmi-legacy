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

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <boost/shared_ptr.hpp>

#include "b_point.h"
#include "b_exception.h"
#include "b_enums.h"

using boost::shared_ptr;

namespace BoardGame {
class SDLSprite
{
public:
    SDLSprite();

    void SetAsIcon();
    void Load(std::string Filename, unsigned int Zoom, unsigned int Rotation);
    void Blit(shared_ptr<SDL_Surface> , Point p, SpriteJustifyEnum justify = SJ_LEFTTOP);

private:

    void Zoom(unsigned int Zoom);
    void Rotate(unsigned int Rotation); /* customized for my needs, 90/180/270 degrees and square sprites only */

    shared_ptr<SDL_Surface> Surface;
};
}
#endif // SPRITE_H

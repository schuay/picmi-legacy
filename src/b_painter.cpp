/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_painter.h"

namespace BoardGame {

    Painter::Painter() {
        screen = NULL;

        if (TTF_Init() == -1)
            throw Exception("Could not initialize sdl_ttf");
    }

    Painter::~Painter() {
        if (screen)
            SDL_FreeSurface(screen);

        TTF_Quit();
    }

    void Painter::LoadCustomBackground(std::string path) {
        sprBackground.Load( path, 1, 0);
    }

    void Painter::PaintBackground() {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  /* paint bg white */
        sprBackground.Blit(screen, Point(0,0));
    }
}

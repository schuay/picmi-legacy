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

#include "b_painter.h"

namespace BoardGame {

    Painter::Painter() {
        if (TTF_Init() == -1)
            throw Exception("Could not initialize sdl_ttf");
    }

    Painter::~Painter() {
        TTF_Quit();
    }

    void Painter::LoadCustomBackground(std::string path) {
        sprBackground.Load( path, 1, 0);
    }

    void Painter::PaintBackground() {
        SDL_FillRect(screen.get(), NULL, SDL_MapRGB(screen->format, 255, 255, 255));  /* paint bg white */
        sprBackground.Blit(screen, Point(0,0));
    }
    void Painter::PaintGameOverScreen(StatsCollection c) {

        /* clone original state of screen */
        shared_ptr<SDL_Surface> originalScreen(
                SDL_CreateRGBSurface(screen->flags, screen->w, screen->h,
                                     screen->format->BitsPerPixel,
                                     screen->format->Rmask,
                                     screen->format->Gmask,
                                     screen->format->Bmask,
                                     screen->format->Amask),
                SDL_FreeSurface);

        SDL_BlitSurface(screen.get(), NULL, originalScreen.get(), NULL);

        /* construct a shade overlay */
        shared_ptr<SDL_Surface> shadeOverlay(
                SDL_CreateRGBSurface(screen->flags, screen->w, screen->h,
                                     screen->format->BitsPerPixel,
                                     screen->format->Rmask,
                                     screen->format->Gmask,
                                     screen->format->Bmask,
                                     screen->format->Amask),
                SDL_FreeSurface);

        /* construct a text overlay (and manually set alpha channel for transparent color) */
        shared_ptr<SDL_Surface> textOverlay(
                SDL_CreateRGBSurface(screen->flags, screen->w, screen->h,
                                     screen->format->BitsPerPixel,
                                     screen->format->Rmask,
                                     screen->format->Gmask,
                                     screen->format->Bmask,
                                     SDL_BYTEORDER == SDL_BIG_ENDIAN ? 0x000000ff : 0xff000000),
                SDL_FreeSurface);
        SDL_FillRect(textOverlay.get(), NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 0));

        SDL_Color col;
        col.r = col.g = col.b = 255;

        std::string infoText = GetGameOverText(c);

        Point p(textOverlay->w / 2, (textOverlay->h - txt.HeightOf(infoText)) / 2);

        txt.Blit(textOverlay, infoText, p, col, FT_BOLD, TJ_CENTER);

        /* fade in text overlay over 100 frames */
        for (int i = 1; i < 100; i++) {

            /* check for user input during fade to allow early fade abort */
            /* ugly because 'painter' shouldn't know about input..  */
            /* necessary because game over has its own loop within the main loop.. this should be fixed sometime */
            SDL_Event ev;
            while (SDL_PollEvent(&ev) == 1)
                if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_QUIT) {
                    SDL_PushEvent(&ev);
                    return;
                }

            SDL_SetAlpha(shadeOverlay.get(), SDL_SRCALPHA, i * 2);
            SDL_SetAlpha(textOverlay.get(), SDL_SRCALPHA, (( i * 127 ) / 100) * 2 ); /* 0 -> 255*/
            SDL_BlitSurface(originalScreen.get(), NULL, screen.get(), NULL);
            SDL_BlitSurface(shadeOverlay.get(), NULL, screen.get(), NULL);
            SDL_BlitSurface(textOverlay.get(), NULL, screen.get(), NULL);
            SDL_Flip(screen.get());
        }
    }
    void Painter::PaintPauseScreen() {

        Point p(screen->w / 2, screen->h / 2);
        SDL_Color col;
        col.r = col.g = col.b = 255;

        SDL_FillRect(screen.get(), NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        txt.Blit(screen, "PAUSED (press p to continue)", p, col, FT_BOLD, TJ_CENTER);
    }
}

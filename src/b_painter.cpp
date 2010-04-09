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
    void Painter::PaintGameOverScreen(StatsCollection c) {
        SDL_Rect r;
        SDL_Surface *surface = SDL_CreateRGBSurface(screen->flags, 200, 180,
                                                    screen->format->BitsPerPixel,
                                                    screen->format->Rmask,
                                                    screen->format->Gmask,
                                                    screen->format->Bmask,
                                                    screen->format->Amask);

        SDL_SetAlpha(surface, SDL_SRCALPHA, 200);

        r.x = (screen->w - surface->w) / 2;
        r.y = (screen->h - surface->h) / 2;
        r.w = surface->w;
        r.h = surface->h;

        Point p(surface->w / 2, 20);

        SDL_Color col;
        col.r = col.g = col.b = 255;

        std::stringstream out;


        out << std::setprecision(2) << "Games played: " << c.PlayedCount;
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);

        unsigned int textHeight = txt.HeightOf(out.str(), FONT_BOLD);

        out.str("");
        p.y += textHeight;
        out << "Won: " << c.WonCount << " (" << c.WonCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);

        out.str("");
        p.y += textHeight;
        out << "Lost: " << c.LostCount << " (" << c.LostCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);

        out.str("");
        p.y += textHeight;
        out << "Aborted: " << c.AbortedCount << " (" << c.AbortedCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);

        out.str("");
        p.y += textHeight*2;
        out << "Overall rank: " << c.Rank;
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);

        out.str("");
        p.y += textHeight;
        out << "Best time: " << c.BestTime;
        txt.Blit(surface, out.str(), p, col, FONT_NORMAL, JUSTIFY_C);


        SDL_BlitSurface(surface, NULL, screen, &r);
        SDL_Flip(screen);

        SDL_FreeSurface(surface);
    }
}

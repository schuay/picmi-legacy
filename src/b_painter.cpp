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

        r.x = (screen->w / 2) - 100;
        r.y = (screen->h / 2) - 80;
        r.w = 200;
        r.h = 160;

        SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0, 0, 0));

        std::stringstream out;

        Point p(r.x + 20, r.y + 20);

        SDL_Color col;
        col.r = col.g = col.b = 255;

        out << std::setprecision(2) << "Games played: " << c.PlayedCount;
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);

        unsigned int textHeight = txt.HeightOf(out.str(), FONT_BOLD);

        out.str("");
        p.y += textHeight;
        out << "Won: " << c.WonCount << " ( " << c.WonCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);

        out.str("");
        p.y += textHeight;
        out << "Lost: " << c.LostCount << " ( " << c.LostCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);

        out.str("");
        p.y += textHeight;
        out << "Aborted: " << c.AbortedCount << " ( " << c.AbortedCount * 100 / (float)c.PlayedCount << "%)";
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);

        out.str("");
        p.y += textHeight;
        out << "Overall rank: " << c.Rank;
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);

        out.str("");
        p.y += textHeight;
        out << "Best time: " << c.BestTime;
        txt.Blit(screen, out.str(), p, col, FONT_BOLD, JUSTIFY_L);


        SDL_Flip(screen);
    }
}

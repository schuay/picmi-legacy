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
        SDL_Surface *surface = SDL_CreateRGBSurface(screen->flags, screen->w, screen->h,
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

        Point p(surface->w / 2, surface->h / 2 - 100);

        SDL_Color col;
        col.r = col.g = col.b = 255;

        std::stringstream out;

        out << std::setprecision(2)
            << (c.CurrentResolution == GR_WON ? "YOU WIN :)" : (c.CurrentResolution == GR_LOST ? "you lose :'(" : "game aborted")) << std::endl
            << c.CurrentTime << " seconds played" << std::endl << std::endl
            << "Games played: " << c.PlayedCount << std::endl
            << "Won: " << c.WonCount << " (" << c.WonCount * 100 / (float)c.PlayedCount << "%)" << std::endl
            << "Lost: " << c.LostCount << " (" << c.LostCount * 100 / (float)c.PlayedCount << "%)" << std::endl
            << "Aborted: " << c.AbortedCount << " (" << c.AbortedCount * 100 / (float)c.PlayedCount << "%)" << std::endl << std::endl
            << "Overall rank: " << c.Rank << std::endl
            << "Best time: " << c.BestTime;

        Write(QString(out.str().c_str()), surface, p, col, FONT_BOLD, JUSTIFY_C);

        SDL_BlitSurface(surface, NULL, screen, &r);
        SDL_FreeSurface(surface);

        SDL_Flip(screen);
    }

    void Painter::Write(QString text, SDL_Surface *dst, Point &p, SDL_Color &c, unsigned int fontType, unsigned int justify) {
        QStringList qsplittext = text.split('\n');
        unsigned int textHeight = txt.HeightOf(text.toStdString(), fontType);

        for (int i = 0; i < qsplittext.count(); i++) {
            p.y += textHeight;
            txt.Blit(dst, qsplittext.at(i).toStdString(), p, c, fontType, justify);
        }
    }
}

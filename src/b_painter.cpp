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

        /* construct a text overlay */
        shared_ptr<SDL_Surface> textOverlay(
                SDL_CreateRGBSurface(screen->flags, screen->w, screen->h,
                                     screen->format->BitsPerPixel,
                                     screen->format->Rmask,
                                     screen->format->Gmask,
                                     screen->format->Bmask,
                                     screen->format->Amask),
                SDL_FreeSurface);

        Point p(textOverlay->w / 2, textOverlay->h / 2 - 100);

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

        txt.Blit(textOverlay, out.str(), p, col, FONT_BOLD, JUSTIFY_C);

        /* fade in text overlay over 100 frames */
        for (int i = 1; i < 100; i++) {
            SDL_SetAlpha(textOverlay.get(), SDL_SRCALPHA, i * 2);
            SDL_BlitSurface(originalScreen.get(), NULL, screen.get(), NULL);
            SDL_BlitSurface(textOverlay.get(), NULL, screen.get(), NULL);
            SDL_Flip(screen.get());
        }
    }
}

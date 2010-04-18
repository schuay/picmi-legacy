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

        Point p(textOverlay->w / 2, textOverlay->h / 2 - 200);

        SDL_Color col;
        col.r = col.g = col.b = 255;

        std::stringstream out;

        QString dateFormat("MMM dd yy, hh:mm:");

        out << std::fixed << std::setprecision(0)
            << (c.CurrentResolution == GR_WON ? "YOU WIN :)" : (c.CurrentResolution == GR_LOST ? "you lose :'(" : "game aborted")) << std::endl
            << c.CurrentTime << " seconds played" << std::endl << std::endl
            << "Games played: " << c.PlayedCount << std::endl
            << "Won: " << c.WonCount << " (" << c.WonPercentage() << "%)" << std::endl
            << "Lost: " << c.LostCount << " (" << c.LostPercentage() << "%)" << std::endl
            << "Aborted: " << c.AbortedCount << " (" << c.AbortedPercentage() << "%)" << std::endl << std::endl
            << "Overall rank: " << c.Rank << std::endl << std::endl
            << "Top 5 Games" << std::endl << std::endl
            << "1. " << std::setw(20) << c.Top5DateTime[0].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[0] << "s" << std::endl
            << "2. " << std::setw(20) << c.Top5DateTime[1].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[1] << "s" << std::endl
            << "3. " << std::setw(20) << c.Top5DateTime[2].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[2] << "s" << std::endl
            << "4. " << std::setw(20) << c.Top5DateTime[3].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[3] << "s" << std::endl
            << "5. " << std::setw(20) << c.Top5DateTime[4].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[4] << "s" << std::endl;

        txt.Blit(textOverlay, out.str(), p, col, FT_BOLD, TJ_CENTER);

        /* fade in text overlay over 100 frames */
        for (int i = 1; i < 100; i++) {
            SDL_SetAlpha(textOverlay.get(), SDL_SRCALPHA, i * 2);
            SDL_BlitSurface(originalScreen.get(), NULL, screen.get(), NULL);
            SDL_BlitSurface(textOverlay.get(), NULL, screen.get(), NULL);
            SDL_Flip(screen.get());
        }
    }
}

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweeppainter.h"

namespace BoardGame {

    SweepPainter::SweepPainter(BoardGame *p, BoardSettings &s) :
            Painter(), game(NULL)
    {
        game = dynamic_cast<Sweeper*>(p);

        if (!game)
            throw Exception("Game object not set");

        InitSystems();
        LoadSprites();

        if (s.UseCustomBG && s.BackgroundPath.length() != 0)
            LoadCustomBackground(s.BackgroundPath);
    }

    void SweepPainter::Paint() {
        PaintBackground();
        PaintBoardArea();
        PaintInfoArea();

        SDL_Flip(screen);
    }
    void SweepPainter::PaintBoardArea() {
        unsigned int i, j;
        Point p, q;

        for (i = 0; i < game->Width(); i++) {
            for (j = 0; j < game->Height(); j++) {
                p.x = game->PixOffsetX()*game->Zoom() + i*game->CellLength()*game->Zoom();
                p.y = game->PixOffsetY()*game->Zoom() + j*game->CellLength()*game->Zoom();

                q.x = i;
                q.y = j;

                /* cell frame */
                sprCellFrame.Blit(screen, p);

                /* tile states */
                int state = game->GetStateAt(q);

                if (state == S_BOARD_MARKED)
                    sprMarkedTile.Blit(screen, p);
                if (state == S_BOARD_CLEAN)
                    sprClearTile.Blit(screen, p);
                else if (state == S_BOARD_TENTATIVE)
                    sprTentativeTile.Blit(screen, p);
                else if (state == S_BOARD_BOMB)
                    sprBomb.Blit(screen, p);
                else if (state >= S_BOARD_EXPOSED_1 && state <= S_BOARD_EXPOSED_8)
                    sprNumbers[state-1].Blit(screen, p);
            }
        }
    }
    void SweepPainter::PaintInfoArea() {
        SDL_Rect to;
        SDL_Color color;
        std::stringstream out;
        Point p;

        to.x = to.y = 0;
        to.w = game->Width() * game->CellLength();
        to.h = game->PixOffsetY();

        p.x = 10 * game->Zoom();
        p.y = 10 * game->Zoom();

        color.r = color.g = color.b = 255;

        /* info -> black bg */
        SDL_FillRect(screen, &to, SDL_MapRGB(screen->format, 0, 0, 0));

        /* draw text */
        out << "Elapsed Time: " << game->GetElapsedTime();
        txt.Blit(screen, out.str(), p, color, FONT_BOLD, JUSTIFY_L);

        p.x = game->Width() * game->CellLength() - 10 * game->Zoom();
        out.str("");

        out << "Completed: " << game->MarkedBombCount() << " / " << game->TotalBombCount();
        txt.Blit(screen, out.str(), p, color, FONT_BOLD, JUSTIFY_R);
    }

    void SweepPainter::InitSystems() {

        screen = SDL_SetVideoMode(
                (game->PixOffsetX() + game->Width() * game->CellLength() + 5) * game->Zoom(),
                (game->PixOffsetY() + game->Height() * game->CellLength() + 5) * game->Zoom(),
                24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

        if (!screen)
            throw Exception(SDL_GetError());
    }

    void SweepPainter::LoadSprites() {
        txt.Load(FILEPREFIX "gfx/LiberationMono-Regular.ttf",
                 FILEPREFIX "gfx/LiberationMono-Bold.ttf",
                 FILEPREFIX "gfx/LiberationMono-Italic.ttf", 12);

        sprIcon.Load(FILEPREFIX "gfx/icon.png", 1, 0);
        sprIcon.SetAsIcon();

        sprCellFrame.Load(      FILEPREFIX "gfx/ms_cellframe.png", game->Zoom(), 0);
        sprClearTile.Load(      FILEPREFIX "gfx/ms_box.png", game->Zoom(), 0);
        sprMarkedTile.Load(     FILEPREFIX "gfx/ms_marked.png", game->Zoom(), 0);
        sprTentativeTile.Load(  FILEPREFIX "gfx/ms_tentative.png", game->Zoom(), 0);
        sprBomb.Load(           FILEPREFIX "gfx/ms_bomb.png", game->Zoom(), 0);

        sprNumbers[0].Load(FILEPREFIX "gfx/ms_1.png", game->Zoom(), 0);
        sprNumbers[1].Load(FILEPREFIX "gfx/ms_2.png", game->Zoom(), 0);
        sprNumbers[2].Load(FILEPREFIX "gfx/ms_3.png", game->Zoom(), 0);
        sprNumbers[3].Load(FILEPREFIX "gfx/ms_4.png", game->Zoom(), 0);
        sprNumbers[4].Load(FILEPREFIX "gfx/ms_5.png", game->Zoom(), 0);
        sprNumbers[5].Load(FILEPREFIX "gfx/ms_6.png", game->Zoom(), 0);
        sprNumbers[6].Load(FILEPREFIX "gfx/ms_7.png", game->Zoom(), 0);
        sprNumbers[7].Load(FILEPREFIX "gfx/ms_8.png", game->Zoom(), 0);

        sprBackground.Load(FILEPREFIX "gfx/ms_background.jpg", game->Zoom(), 0);
    }
}

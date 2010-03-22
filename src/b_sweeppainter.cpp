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

    SweepPainter::SweepPainter(BoardGame *p, std::string customBackground) :
            Painter(), game(NULL)
    {
        game = dynamic_cast<Sweeper*>(p);

        if (!game)
            throw Exception("Game object not set");

        InitSystems();
        LoadSprites();

        if (customBackground.length() != 0)
            LoadCustomBackground(customBackground);
    }

    void SweepPainter::Paint() {
        PaintBackground();
        PaintBoardArea();

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
                 FILEPREFIX "gfx/LiberationMono-Italic.ttf");

        sprIcon.Load(FILEPREFIX "gfx/icon.png", 1, 0);
        sprIcon.SetAsIcon();

        sprCellFrame.Load(FILEPREFIX "gfx/cellframe.png", game->Zoom(), 0);
        sprClearTile.Load(FILEPREFIX "gfx/box.png", game->Zoom(), 0);
        sprMarkedTile.Load(FILEPREFIX "gfx/sweepermarked.png", game->Zoom(), 0);
        sprTentativeTile.Load(FILEPREFIX "gfx/tentative.png", game->Zoom(), 0);
        sprBomb.Load(FILEPREFIX "gfx/bomb.png", game->Zoom(), 0);

        sprNumbers[0].Load(FILEPREFIX "gfx/1.png", game->Zoom(), 0);
        sprNumbers[1].Load(FILEPREFIX "gfx/2.png", game->Zoom(), 0);
        sprNumbers[2].Load(FILEPREFIX "gfx/3.png", game->Zoom(), 0);
        sprNumbers[3].Load(FILEPREFIX "gfx/4.png", game->Zoom(), 0);
        sprNumbers[4].Load(FILEPREFIX "gfx/5.png", game->Zoom(), 0);
        sprNumbers[5].Load(FILEPREFIX "gfx/6.png", game->Zoom(), 0);
        sprNumbers[6].Load(FILEPREFIX "gfx/7.png", game->Zoom(), 0);
        sprNumbers[7].Load(FILEPREFIX "gfx/8.png", game->Zoom(), 0);

        sprBackground.Load(FILEPREFIX "gfx/background.jpg", game->Zoom(), 0);
    }
}

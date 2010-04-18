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

        SDL_Flip(screen.get());
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
                else if (state == S_BOARD_CLEAN)
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
        to.w = game->Width() * game->CellLength() * game->Zoom();
        to.h = game->PixOffsetY() * game->Zoom();

        p.x = 10 * game->Zoom();
        p.y = 10 * game->Zoom();

        color.r = color.g = color.b = 255;

        /* info -> black bg */
        SDL_FillRect(screen.get(), &to, SDL_MapRGB(screen->format, 0, 0, 0));

        /* retrieve infos */
        int totalBombCount = game->TotalBombCount();
        int markedBombCount = game->MarkedBombCount();
        int elapsedTime = game->GetElapsedTime();
        float minesPerSecond = elapsedTime == 0 ? 0 : markedBombCount / (float)elapsedTime;
        bool lowWidth(false);

        /* check if entire text fits on screen */
        out << std::fixed << std::setprecision(2)
            << "Time: " << elapsedTime << " "
            << "Eff: " << minesPerSecond <<  " m/s "
            << "Rem. mines: " << totalBombCount - markedBombCount
                << " / " << totalBombCount;

        if ((unsigned int)txt.WidthOf(out.str(), FT_BOLD) > game->Width() * game->CellLength())
            lowWidth = true;

        /* draw text */
        out.str("");
        out << "Time: " << elapsedTime;
        txt.Blit(screen, out.str(), p, color, FT_BOLD, TJ_LEFT);
        p.y = 10 * game->Zoom();

        if (!lowWidth) {
            p.x = (game->Width() * game->CellLength()) / 2;
            out.str("");
            out << std::fixed << std::setprecision(2) << "Eff: " << minesPerSecond <<  " m/s";
            txt.Blit(screen, out.str(), p, color, FT_BOLD, TJ_CENTER);
            p.y = 10 * game->Zoom();
        }

        p.x = (game->Width() * game->CellLength() - 10) * game->Zoom();
        out.str("");
        out << "Rem. mines: " << totalBombCount - markedBombCount << " / " << totalBombCount;
        txt.Blit(screen, out.str(), p, color, FT_BOLD, TJ_RIGHT);
    }

    void SweepPainter::InitSystems() {

        screen.reset(SDL_SetVideoMode(
                (game->PixOffsetX() + game->Width() * game->CellLength() + 5) * game->Zoom(),
                (game->PixOffsetY() + game->Height() * game->CellLength() + 5) * game->Zoom(),
                24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF),
                SDL_FreeSurface);

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

    std::string SweepPainter::GetGameOverText(StatsCollection c) {
        std::stringstream out;

        QString dateFormat("MMM dd yyyy, hh:mm");

        out << std::fixed << std::setprecision(0)
            << (c.CurrentResolution == GR_WON ? "YOU WIN :)" : (c.CurrentResolution == GR_LOST ? "you lose :'(" : "game aborted")) << std::endl << std::endl
            << c.CurrentTime << " seconds played" << std::endl
            << "Overall rank: " << c.Rank << std::endl << std::endl
            << "Games played: " << c.PlayedCount << std::endl
            << "Won: " << c.WonCount << " (" << c.WonPercentage() << "%)" << std::endl
            << "Lost: " << c.LostCount << " (" << c.LostPercentage() << "%)" << std::endl
            << "Aborted: " << c.AbortedCount << " (" << c.AbortedPercentage() << "%)" << std::endl << std::endl
            << "Top 5 Games" << std::endl << std::endl
            << "1. " << std::setw(18) << c.Top5DateTime[0].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[0] << "s" << std::endl
            << "2. " << std::setw(18) << c.Top5DateTime[1].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[1] << "s" << std::endl
            << "3. " << std::setw(18) << c.Top5DateTime[2].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[2] << "s" << std::endl
            << "4. " << std::setw(18) << c.Top5DateTime[3].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[3] << "s" << std::endl
            << "5. " << std::setw(18) << c.Top5DateTime[4].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[4] << "s" << std::endl;

        return out.str();
    }
}

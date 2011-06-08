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

#include "b_sweeppainter.h"

namespace BoardGame {

    SweepPainter::SweepPainter(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> p, BoardSettings &s) :
            Painter(application), game(NULL)
    {
        game = dynamic_cast<Sweeper*>(p.get());

        if (!game)
            throw Exception("Game object not set");

        nativeWidth = game->PixOffsetX() + game->Width() * game->CellLength() + 5;
        nativeHeight = game->PixOffsetY() + game->Height() * game->CellLength() + 5;

        InitSystems();
        LoadSprites();

        if (s.UseCustomBG && s.BackgroundPath.length() != 0)
            LoadCustomBackground(s.BackgroundPath);
    }

    void SweepPainter::Paint() {
        if (game->GetPaused()) {
            PaintPauseScreen();
            app->Display();
            return;
        }

        PaintBackground();
        PaintBoardArea();
        PaintInfoArea();

        app->Display();
    }
    void SweepPainter::PaintBoardArea() {
        unsigned int i, j;
        sf::Vector2i p, q, currentLocation;

        currentLocation = game->GetLocation();

        for (i = 0; i < game->Width(); i++) {
            for (j = 0; j < game->Height(); j++) {
                p.x = game->PixOffsetX() + i*game->CellLength();
                p.y = game->PixOffsetY() + j*game->CellLength();

                q.x = i;
                q.y = j;

                /* cell frame */
                sprCellFrame.Blit(app, p);

                /* active tile */
                if (q == currentLocation)
                    sprActiveTile.Blit(app, p);

                /* tile states */
                int state = game->GetStateAt(q);

                if (state == S_BOARD_MARKED)
                    sprMarkedTile.Blit(app, p);
                else if (state == S_BOARD_CLEAN)
                    sprClearTile.Blit(app, p);
                else if (state == S_BOARD_TENTATIVE)
                    sprTentativeTile.Blit(app, p);
                else if (state == S_BOARD_BOMB)
                    sprBomb.Blit(app, p);
                else if (state >= S_BOARD_EXPOSED_1 && state <= S_BOARD_EXPOSED_8)
                    sprNumbers[state-1].Blit(app, p);
            }
        }
    }
    void SweepPainter::PaintInfoArea() {

        sf::Color color(sf::Color::White);
        std::stringstream out;
        sf::Vector2i p;

        p.x = p.y = 10;

        /* info -> black bg */

        sf::Shape shape = sf::Shape::Rectangle(0, 0, game->Width() * game->CellLength(), game->PixOffsetY(), sf::Color(0, 0, 0, 200));
        app->Draw(shape);

        /* game not started - display instructions and exit */
        if (!game->IsStarted()) {
            out.str("");
            if (game->IsWorking())
                out << "Generating board, please wait...";
            else
                out << "Click on any tile to start the game...";

            p.x = (game->Width() * game->CellLength()) / 2;
            txt.Blit(app, out.str(), p, color, FT_BOLD, TJ_CENTER);
            return;
        }

        /* retrieve infos */
        int totalBombCount = game->TotalBombCount();
        int markedBombCount = game->MarkedBombCount();
        int elapsedTime = game->GetElapsedTime();
        float minesPerSecond = elapsedTime == 0 ? 0 : markedBombCount / (float)elapsedTime;
        bool lowWidth(false);

        /* generate info strings */
        out.str("");
        out << "Time: " << elapsedTime / 60 << "m " << elapsedTime % 60 << "s";
        std::string strTime = out.str();

        out.str("");
        out << std::fixed << std::setprecision(2) << "Eff: " << minesPerSecond <<  " m/s";
        std::string strEfficiency = out.str();

        out.str("");
        out << "Rem. mines: " << totalBombCount - markedBombCount << " / " << totalBombCount;
        std::string strRemaining = out.str();

        /* check if entire text fits on screen
           since we do not display infos as a single string (time justified left, efficiency centered,
           remaining bombs right), we need to check if the strings INCLUDING formatting overlap
         */
        if (     txt.WidthOf(strTime, FT_BOLD)      + txt.WidthOf(strEfficiency, FT_BOLD) / 2 + 25 > game->Width() * game->CellLength() / 2)
            lowWidth = true;
        else if (txt.WidthOf(strRemaining, FT_BOLD) + txt.WidthOf(strEfficiency, FT_BOLD) / 2 + 25 > game->Width() * game->CellLength() / 2)
            lowWidth = true;

        /* draw text */
        txt.Blit(app, strTime, p, color, FT_BOLD, TJ_LEFT);
        p.y = 10;

        if (!lowWidth) {
            p.x = (game->Width() * game->CellLength()) / 2;
            txt.Blit(app, strEfficiency, p, color, FT_BOLD, TJ_CENTER);
            p.y = 10;
        }

        p.x = (game->Width() * game->CellLength() - 10);
        txt.Blit(app, strRemaining, p, color, FT_BOLD, TJ_RIGHT);
    }

    void SweepPainter::InitSystems() {

        app->Create(sf::VideoMode(nativeWidth, nativeHeight), WINDOWTITLE);

    }

    void SweepPainter::LoadSprites() {
        txt.Load(FILEPREFIX "gfx/LiberationMono-Regular.ttf",
                 FILEPREFIX "gfx/LiberationMono-Bold.ttf",
                 FILEPREFIX "gfx/LiberationMono-Italic.ttf", 12);

        sprIcon.Load(FILEPREFIX "gfx/icon.png", 0);
        sprIcon.SetAsIcon(app);

        sprCellFrame.Load(      FILEPREFIX "gfx/ms_cellframe.png", 0);
        sprActiveTile.Load(     FILEPREFIX "gfx/ms_activecell.png", 0);
        sprClearTile.Load(      FILEPREFIX "gfx/ms_box.png", 0);
        sprMarkedTile.Load(     FILEPREFIX "gfx/ms_marked.png", 0);
        sprTentativeTile.Load(  FILEPREFIX "gfx/ms_tentative.png", 0);
        sprBomb.Load(           FILEPREFIX "gfx/ms_bomb.png", 0);

        sprNumbers[0].Load(FILEPREFIX "gfx/ms_1.png", 0);
        sprNumbers[1].Load(FILEPREFIX "gfx/ms_2.png", 0);
        sprNumbers[2].Load(FILEPREFIX "gfx/ms_3.png", 0);
        sprNumbers[3].Load(FILEPREFIX "gfx/ms_4.png", 0);
        sprNumbers[4].Load(FILEPREFIX "gfx/ms_5.png", 0);
        sprNumbers[5].Load(FILEPREFIX "gfx/ms_6.png", 0);
        sprNumbers[6].Load(FILEPREFIX "gfx/ms_7.png", 0);
        sprNumbers[7].Load(FILEPREFIX "gfx/ms_8.png", 0);

        sprBackground.Load(FILEPREFIX "gfx/ms_background.jpg", 0);
    }

    std::string SweepPainter::GetGameOverText(StatsCollection c) {
        std::stringstream out;

        QString dateFormat("MMM dd yyyy, hh:mm");

        out << std::fixed << std::setprecision(0)
            << (c.CurrentResolution == GR_WON ? "YOU WIN :)" : (c.CurrentResolution == GR_LOST ? "you lose :'(" : "game aborted")) << std::endl
            << "press 'r' to retry, any key to quit" << std::endl << std::endl
            << c.CurrentTime / 60 << "m " << c.CurrentTime % 60 << "s played" << std::endl
            << "Overall rank: " << c.Rank << std::endl << std::endl
            << "Games played: " << c.PlayedCount << std::endl
            << "Won: " << c.WonCount << " (" << c.WonPercentage() << "%)" << std::endl
            << "Lost: " << c.LostCount << " (" << c.LostPercentage() << "%)" << std::endl
            << "Aborted: " << c.AbortedCount << " (" << c.AbortedPercentage() << "%)" << std::endl << std::endl
            << "Top 5 Games" << std::endl << std::endl
            << "1. " << std::setw(18) << c.Top5DateTime[0].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[0] / 60 << "m " << c.Top5Time[0] % 60 << "s" << std::endl
            << "2. " << std::setw(18) << c.Top5DateTime[1].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[1] / 60 << "m " << c.Top5Time[1] % 60 << "s" << std::endl
            << "3. " << std::setw(18) << c.Top5DateTime[2].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[2] / 60 << "m " << c.Top5Time[2] % 60 << "s" << std::endl
            << "4. " << std::setw(18) << c.Top5DateTime[3].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[3] / 60 << "m " << c.Top5Time[3] % 60 << "s" << std::endl
            << "5. " << std::setw(18) << c.Top5DateTime[4].toString(dateFormat).toStdString() << std::setw(5) << c.Top5Time[4] / 60 << "m " << c.Top5Time[4] % 60 << "s" << std::endl;

        return out.str();
    }
}

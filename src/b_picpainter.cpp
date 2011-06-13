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

#include "b_picpainter.h"
namespace BoardGame {
PicPainter::PicPainter(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p, BoardSettings &s)
    : Painter(application), game(NULL)
{
    game = dynamic_cast<Picross*>(p.get());

    if (!game)
        throw Exception("Game object not set");

    nativeWidth = game->PixOffsetX() + game->Width() * game->CellLength() + 5;
    nativeHeight = game->PixOffsetY() + game->Height() * game->CellLength() + 5;

    InitSystems();
    LoadSprites();

    if (s.UseCustomBG && s.BackgroundPath.length() != 0)
        LoadCustomBackground(s.BackgroundPath);
}

void PicPainter::LoadSprites() {
    txt.Load(FILEPREFIX "gfx/LiberationMono-Regular.ttf",
             FILEPREFIX "gfx/LiberationMono-Bold.ttf",
             FILEPREFIX "gfx/LiberationMono-Italic.ttf",
             14);

    sprIcon.Load(FILEPREFIX "gfx/icon.png", 0);
    sprIcon.SetAsIcon(app);

    sprCellFrame.Load(FILEPREFIX    "gfx/p_cellframe.png", 0);
    sprBoxTile.Load(FILEPREFIX      "gfx/p_box.png", 0);
    sprMarkTile.Load(FILEPREFIX     "gfx/p_mark.png", 0);
    sprActiveTile.Load(FILEPREFIX   "gfx/p_activecell.png", 0);

    sprDividerR.Load(FILEPREFIX "gfx/p_divider.png", 0);
    sprDividerD.Load(FILEPREFIX "gfx/p_divider.png", 90);
    sprDividerL.Load(FILEPREFIX "gfx/p_divider.png", 180);
    sprDividerU.Load(FILEPREFIX "gfx/p_divider.png", 270);

    sprStreakAreaHorA.Load(FILEPREFIX "gfx/p_streakA.png", 0);
    sprStreakAreaHorB.Load(FILEPREFIX "gfx/p_streakB.png", 0);
    sprStreakAreaVerA.Load(FILEPREFIX "gfx/p_streakA.png", 90);
    sprStreakAreaVerB.Load(FILEPREFIX "gfx/p_streakB.png", 90);

    sprBackground.Load(FILEPREFIX "gfx/p_background.jpg", 0);
}

void PicPainter::Paint() {
    if (game->GetPaused()) {
        PaintPauseScreen();
        app->Display();
        return;
    }

    game->CalculateStreakSolvedState();

    PaintBackground();
    PaintInfoArea();
    PaintStreakArea();
    PaintBoardArea();

    app->Display();
}

void PicPainter::PaintInfoArea() {

    std::stringstream out;
    sf::Vector2i p;
    sf::Color color(sf::Color::White);

    p.x = p.y = 10;

    sf::Shape shape = sf::Shape::Rectangle(0, 0, game->PixOffsetX(), game->PixOffsetY(), sf::Color(0, 0, 0, 200));
    app->Draw(shape);

    /* draw text */
    out << std::fixed << std::setprecision(0);

    out << "Elapsed Time";
    txt.Blit(app, out.str(), p, color, FT_BOLD);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------" << std::endl
        << "Total: " << game->GetElapsedTime() / 60 << "m " << game->GetElapsedTime() % 60 << "s";
    txt.Blit(app, out.str(), p, color, FT_NORMAL);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "Real: " << game->GetElapsedRealTime() / 60 << "m " << game->GetElapsedRealTime() % 60 << "s" << std::endl;
    txt.Blit(app, out.str(), p, color, FT_ITALIC);
    p.y += txt.HeightOf(out.str()) * 3;

    out.str("");
    out << "Completed";
    txt.Blit(app, out.str(), p, color, FT_BOLD);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------" << std::endl
        << game->GetCompletedPercentageBoxes() << " % done";
    txt.Blit(app, out.str(), p, color, FT_NORMAL);
}
void PicPainter::PaintStreakArea() {
    unsigned int i, j;
    sf::Vector2i p;
    sf::Color colorSolved(84, 84, 84),
              colorUnsolved(0, 0, 0);

    std::stringstream out;

    /* highlight active row/col */

    if (!game->GetQuit()) {

        p.x = game->PixOffsetX() + game->GetLocation().x * game->CellLength();

        for (int i = 0; i * game->CellLength() < game->PixOffsetX(); i++) {
            p.y = i * game->CellLength();
            sprActiveTile.Blit(app, p);
        }

        p.y = game->PixOffsetY() + game->GetLocation().y * game->CellLength();

        for (int j = 0; j * game->CellLength() < game->PixOffsetX(); j++) {
            p.x = j * game->CellLength();
            sprActiveTile.Blit(app, p);
        }
    }

    /* streak areas */

    p.y = 0;
    for (i = 0; i < game->Width(); i++) {
        p.x = game->PixOffsetX() + i*game->CellLength();
        if (i%2 == 0)
            sprStreakAreaVerA.Blit(app, p);
        else
            sprStreakAreaVerB.Blit(app, p);
    }
    p.x = 0;
    for (j = 0; j < game->Height(); j++) {
        p.y = game->PixOffsetY() + j*game->CellLength();
        if (j%2 == 0)
            sprStreakAreaHorA.Blit(app, p);
        else
            sprStreakAreaHorB.Blit(app, p);
    }

    unsigned int streakLength;

    /* draw row streaks */
    for (i = 0; i < game->Height(); i++) {
        streakLength = 0;

        for (int js = game->RowStreaks[i].size() - 1; js >= 0; js--) {
            PicStreak s = game->RowStreaks[i][js];     /* note the reverse order of loop  */
                                                       /* we need to do this to draw streaks in correct order */
            out.str("");
            out << s.GetLength() << ' ';

            streakLength += txt.WidthOf(out.str()) + 2;

            p.x = game->PixOffsetX() - 2 - streakLength;
            p.y = game->PixOffsetY() + i * game->CellLength();

            txt.Blit(   app,
                        out.str(),
                        p,
                        s.Solved ? colorSolved : colorUnsolved,
                        s.Solved ? FT_ITALIC : FT_BOLD);
        }
    }

    /* draw col streaks */
    for (i = 0; i < game->Width(); i++) {
        streakLength = 0;

        for (int js = game->ColStreaks[i].size() - 1; js >= 0; js--) {
            PicStreak s = game->ColStreaks[i][js];

            out.str("");    //clear the stream
            out << s.GetLength();

            streakLength += txt.HeightOf(out.str()) + 2;    /* used in next statement, don't move */

            p.x = game->PixOffsetX()        /* puzzle starting position */
                  + i * game->CellLength()  /* plus the appropriate column position */
                  + 10;                     /* and centre within column */
            p.y = game->PixOffsetY()        /* puzzle starting position */
                  - streakLength            /* stack numbers above each other */
                  - 5;                      /* and adjust the whole stack upwards */

            txt.Blit(   app,
                        out.str(),
                        p,
                        s.Solved ? colorSolved : colorUnsolved,
                        s.Solved ? FT_ITALIC : FT_BOLD,
                        TJ_CENTER);
        }
    }
}
void PicPainter::PaintBoardArea() {
    unsigned int i, j;
    sf::Vector2i p, q;

    for (i = 0; i < game->Width(); i++) {
        for (j = 0; j < game->Height(); j++) {
            p.x = game->PixOffsetX() + i*game->CellLength();
            p.y = game->PixOffsetY() + j*game->CellLength();

            q.x = i;
            q.y = j;

            /* active cells (and entire row / column) */
            if (!game->GetQuit() &&
                ( q.x == game->GetLocation().x || q.y == game->GetLocation().y )) {
                sprActiveTile.Blit(app, p);
            }

            /* cell frame */
            sprCellFrame.Blit(app, p);

            /* dividers (mark 5x5 areas */
            if ((i+1)%5 == 0) {
                sprDividerR.Blit(app, p);
            } else if (i%5 == 0) {
                sprDividerL.Blit(app, p);
            }
            if ((j+1)%5 == 0) {
                sprDividerD.Blit(app, p);
            } else if (j%5 == 0) {
                sprDividerU.Blit(app, p);
            }

            /* box / marked tiles */
            if (game->GetStateAt(q) == BOARD_HIT) {
                sprBoxTile.Blit(app, p);
            } else if (game->GetStateAt(q) == BOARD_MARKED) {
                sprMarkTile.Blit(app, p);
            }
        }
    }
}

std::string PicPainter::GetGameOverText(StatsCollection c) {
    std::stringstream out;

    QString dateFormat("MMM dd yyyy, hh:mm");

    out << std::fixed << std::setprecision(0)
        << (c.CurrentResolution == GR_WON ? "YOU WIN :)" : (c.CurrentResolution == GR_LOST ? "you lose :'(" : "game aborted")) << std::endl
        << "press 'r' to retry, any key to quit" << std::endl << std::endl
        << c.CurrentTime / 60 << "m " << c.CurrentTime % 60 << "s played" << std::endl
        << "Overall rank: " << c.Rank << std::endl << std::endl
        << "Games played: " << c.PlayedCount << std::endl
        << "Won: " << c.WonCount << " (" << c.WonPercentage() << "%)" << std::endl
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

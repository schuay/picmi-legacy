/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picpainter.h"

PicPainter::PicPainter(BoardGame *p, std::string customBackground)
    : screen(NULL), game(NULL)
{
    game = dynamic_cast<Picross*>(p);

    if (!game)
        throw PicException("Game object not set");

    InitSystems();
    LoadSprites();

    if (customBackground.length() != 0)
        LoadCustomBackground(customBackground);
}
PicPainter::~PicPainter() {
    TTF_Quit();
}

void PicPainter::LoadCustomBackground(std::string path) {
    sprBackground.Load( path, game->Zoom(), 0);
}

void PicPainter::LoadSprites() {
    txt.Load(FILEPREFIX "gfx/LiberationMono-Regular.ttf",
             FILEPREFIX "gfx/LiberationMono-Bold.ttf",
             FILEPREFIX "gfx/LiberationMono-Italic.ttf");


    sprIcon.Load(FILEPREFIX "gfx/icon.png", 1, 0);
    sprIcon.SetAsIcon();

    sprCellFrame.Load(FILEPREFIX "gfx/cellframe.png", game->Zoom(), 0);
    sprBoxTile.Load(FILEPREFIX "gfx/box.png", game->Zoom(), 0);
    sprMarkTile.Load(FILEPREFIX "gfx/mark.png", game->Zoom(), 0);
    sprActiveTile.Load(FILEPREFIX "gfx/activecell.png", game->Zoom(), 0);

    sprDividerR.Load(FILEPREFIX "gfx/divider.png", game->Zoom(),0);
    sprDividerD.Load(FILEPREFIX "gfx/divider.png", game->Zoom(), 270);
    sprDividerL.Load(FILEPREFIX "gfx/divider.png", game->Zoom(), 180);
    sprDividerU.Load(FILEPREFIX "gfx/divider.png", game->Zoom(), 90);

    sprStreakAreaHorA.Load(FILEPREFIX "gfx/streakA.png", game->Zoom(), 0);
    sprStreakAreaHorB.Load(FILEPREFIX "gfx/streakB.png", game->Zoom(), 0);
    sprStreakAreaVerA.Load(FILEPREFIX "gfx/streakA.png", game->Zoom(), 270);
    sprStreakAreaVerB.Load(FILEPREFIX "gfx/streakB.png", game->Zoom(), 270);

    sprBackground.Load(FILEPREFIX "gfx/background.jpg", game->Zoom(), 0);
}

void PicPainter::InitSystems() {
    if (TTF_Init() == -1)
        throw PicException("Could not initialize sdl_ttf");

    screen = SDL_SetVideoMode(
            (game->PixOffsetX() + game->Width() * game->CellLength() + 5) * game->Zoom(),
            (game->PixOffsetY() + game->Height() * game->CellLength() + 5) * game->Zoom(),
            24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

    if (!screen)
        throw PicException(SDL_GetError());
}

void PicPainter::Paint() {
    game->CalculateStreakSolvedState();

    PaintBackground();
    PaintInfoArea();
    PaintStreakArea();
    PaintBoardArea();

    SDL_Flip(screen);
}

void PicPainter::PaintBackground() {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  /* paint bg white */
    sprBackground.Blit(screen, PicPoint(0,0));
}
void PicPainter::PaintInfoArea() {
    SDL_Rect to;
    SDL_Color color;
    std::stringstream out;
    PicPoint p;

    to.x = to.y = 0;
    to.w = game->PixOffsetX();
    to.h = game->PixOffsetY();

    p.x = 10 * game->Zoom();
    p.y = 10 * game->Zoom();

    color.r = color.g = color.b = 255;


    SDL_FillRect(screen, &to, SDL_MapRGB(screen->format, 0, 0, 0)); /* info -> black bg */

    /* draw text */
    out << "Elapsed Time";
    txt.Blit(screen, out.str(), p, color, FONT_BOLD, JUSTIFY_L);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------";
    txt.Blit(screen, out.str(), p, color, FONT_NORMAL, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << "Total: " << game->GetElapsedTime() << "s";
    txt.Blit(screen, out.str(), p, color, FONT_NORMAL, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << "Real: " << game->GetElapsedRealTime() << "s";
    txt.Blit(screen, out.str(), p, color, FONT_ITALIC, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 25;

    out.str("");
    out << "Completed";
    txt.Blit(screen, out.str(), p, color, FONT_BOLD, JUSTIFY_L);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------";
    txt.Blit(screen, out.str(), p, color, FONT_NORMAL, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << std::fixed << std::setprecision(0) << game->GetCompletedPercentageBoxes() << " % done";
    txt.Blit(screen, out.str(), p, color, FONT_NORMAL, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 5;
}
void PicPainter::PaintStreakArea() {
    unsigned int i, j;
    PicPoint p;
    SDL_Color colorSolved,
              colorUnsolved;

    colorSolved.r = colorSolved.g = colorSolved.b = 84;         /* dark gray */
    colorUnsolved.r = colorUnsolved.g = colorUnsolved.b = 0;    /* black */

    std::stringstream out;

    /* highlight active row/col - currently deactivated because streak gfx are not translucent*/

    if (!game->GameWon()) {
        p.x = game->PixOffsetX()*game->Zoom() +
              game->GetLocation().x*game->CellLength()*game->Zoom();
        for (int i = 0; i * game->CellLength() < game->PixOffsetX(); i++) {
            p.y = i*game->CellLength()*game->Zoom();

            sprActiveTile.Blit(screen, p);
        }
        p.y = game->PixOffsetY()*game->Zoom() +
              game->GetLocation().y*game->CellLength()*game->Zoom();
        for (int j = 0; j * game->CellLength() < game->PixOffsetX(); j++) {
        p.x = j*game->CellLength()*game->Zoom();

        sprActiveTile.Blit(screen, p);
    }
    }

    /* streak areas */

    p.y = 0;
    for (i = 0; i < game->Width(); i++) {
        p.x = game->PixOffsetX()*game->Zoom() + i*game->CellLength()*game->Zoom();
        if (i%2 == 0)
            sprStreakAreaVerA.Blit(screen, p, JUSTIFY_LB);
        else
            sprStreakAreaVerB.Blit(screen, p, JUSTIFY_LB);
    }
    p.x = 0;
    for (j = 0; j < game->Height(); j++) {
        p.y = game->PixOffsetY()*game->Zoom() + j*game->CellLength()*game->Zoom();
        if (j%2 == 0)
            sprStreakAreaHorA.Blit(screen, p, JUSTIFY_RT);
        else
            sprStreakAreaHorB.Blit(screen, p, JUSTIFY_RT);
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

            p.x = game->PixOffsetX()*game->Zoom() - 2*game->Zoom() - streakLength;
            p.y = game->PixOffsetY()*game->Zoom() + i*game->Zoom()*game->CellLength();

            streakLength += txt.WidthOf(out.str()) + 2;

            txt.Blit(   screen,
                        out.str(),
                        p,
                        s.Solved ? colorSolved : colorUnsolved,
                        s.Solved ? FONT_ITALIC : FONT_BOLD,
                        JUSTIFY_R);
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

            p.x = game->PixOffsetX()*game->Zoom()     /* puzzle starting position */
                  + i*game->Zoom()*game->CellLength()  /* plus the appropriate column position */
                  + 10*game->Zoom();           /* and centre within column */
            p.y = game->PixOffsetY()*game->Zoom()     /* puzzle starting position */
                  - streakLength                      /* stack numbers above each other */
                  - 2*game->Zoom();            /* and adjust the whole stack upwards */

            txt.Blit(   screen,
                        out.str(),
                        p,
                        s.Solved ? colorSolved : colorUnsolved,
                        s.Solved ? FONT_ITALIC : FONT_BOLD,
                        JUSTIFY_C);
        }
    }
}
void PicPainter::PaintBoardArea() {
    unsigned int i, j;
    PicPoint p, q;

    for (i = 0; i < game->Width(); i++) {
        for (j = 0; j < game->Height(); j++) {
            p.x = game->PixOffsetX()*game->Zoom() + i*game->CellLength()*game->Zoom();
            p.y = game->PixOffsetY()*game->Zoom() + j*game->CellLength()*game->Zoom();

            q.x = i;
            q.y = j;

            /* active cells (and entire row / column) */
            if (!game->GameWon() &&
                ( q.x == game->GetLocation().x || q.y == game->GetLocation().y ))
                sprActiveTile.Blit(screen, p);

            /* cell frame */
            sprCellFrame.Blit(screen, p);

            /* dividers (mark 5x5 areas */
            if ((i+1)%5 == 0) {
                sprDividerR.Blit(screen, p);
            }
            else if (i%5 == 0) {
                sprDividerL.Blit(screen, p);
            }
            if ((j+1)%5 == 0) {
                sprDividerD.Blit(screen, p);
            }
            else if (j%5 == 0) {
                sprDividerU.Blit(screen, p);
            }

            /* box / marked tiles */
            if (game->GetStateAt(q) == BOARD_HIT) {
                sprBoxTile.Blit(screen, p);
            }
            else if (game->GetStateAt(q) == BOARD_MARKED) {
                sprMarkTile.Blit(screen, p);
            }
        }
    }
}
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

#include "b_tetrispainter.h"

namespace BoardGame {

TetrisPainter::TetrisPainter(BoardGame *p, BoardSettings& /* unused parameter s */) :
    Painter(), game(NULL)
{
    game = dynamic_cast<Tetris*>(p);

    if (!game)
        throw Exception("Game object not set");

    InitSystems();
    LoadSprites();
}

void TetrisPainter::PaintBoardArea() {
    unsigned int i, j;
    Point p, q;

    for (i = 0; i < game->Width(); i++) {
        for (j = 0; j < game->Height(); j++) {
            p.x = game->PixOffsetX() * game->Zoom() + i * game->CellLength() * game->Zoom();
            p.y = game->PixOffsetY() * game->Zoom() + j * game->CellLength() * game->Zoom();

            q.x = i;
            q.y = j;

            /* cell frame */
            sprBackgroundTile.Blit(screen, p);

            /* tile states */
            int state = game->GetStateAt(q);

            if (state == T_BOARD_I)
                sprITile.Blit(screen, p);
            else if (state == T_BOARD_J)
                sprJTile.Blit(screen, p);
            else if (state == T_BOARD_L)
                sprLTile.Blit(screen, p);
            else if (state == T_BOARD_O)
                sprOTile.Blit(screen, p);
            else if (state == T_BOARD_S)
                sprSTile.Blit(screen, p);
            else if (state == T_BOARD_T)
                sprTTile.Blit(screen, p);
            else if (state == T_BOARD_Z)
                sprZTile.Blit(screen, p);
        }
    }
}
void TetrisPainter::PaintInfoArea() {
    unsigned int i, j, xOffset, yOffset;
    Point p, q;
    TetrisPiece *nextPiece = game->NextPiece();
    int state = nextPiece->GetShape();

    xOffset = game->PixOffsetX() * game->Zoom() * 2 + game->Width() * game->CellLength() * game->Zoom();
    yOffset = game->PixOffsetY() * game->Zoom();

    const unsigned int infoSize = 6;

    for (i = 0; i < infoSize; i++) {
        for (j = 0; j < infoSize; j++) {
            p.x = xOffset + i * game->CellLength() * game->Zoom();
            p.y = yOffset + j * game->CellLength() * game->Zoom();

            q.x = i;
            q.y = j;

            /* cell frame */
            sprBackgroundTile.Blit(screen, p);

            /* painting next piece */

            if (!nextPiece->IsCoveringInPieceCoords(i - 1, j - 1))
                continue;

            if (state == T_BOARD_I)
                sprITile.Blit(screen, p);
            else if (state == T_BOARD_J)
                sprJTile.Blit(screen, p);
            else if (state == T_BOARD_L)
                sprLTile.Blit(screen, p);
            else if (state == T_BOARD_O)
                sprOTile.Blit(screen, p);
            else if (state == T_BOARD_S)
                sprSTile.Blit(screen, p);
            else if (state == T_BOARD_T)
                sprTTile.Blit(screen, p);
            else if (state == T_BOARD_Z)
                sprZTile.Blit(screen, p);
        }
    }

    /* display level */

    std::stringstream displayLine;
    SDL_Color c = { 0, 0, 0 };

    p.y += game->CellLength() * game->Zoom() * 2;
    p.x = xOffset;

    displayLine << "LEVEL";
    txt.Blit(screen, displayLine.str(), p, c, FT_BOLD );

    displayLine.str("");
    displayLine << game->Level();
    p.y += game->CellLength() * game->Zoom() / 2;
    txt.Blit(screen, displayLine.str(), p, c, FT_NORMAL );

    /* display score */

    displayLine.str("");
    displayLine << "SCORE";
    p.y += game->CellLength() * game->Zoom() * 2;
    txt.Blit(screen, displayLine.str(), p, c, FT_BOLD );

    displayLine.str("");
    displayLine << game->Score();
    p.y += game->CellLength() * game->Zoom() / 2;
    txt.Blit(screen, displayLine.str(), p, c, FT_NORMAL );
}

void TetrisPainter::Paint() {
    if (game->GetPaused()) {
        PaintPauseScreen();
        SDL_Flip(screen.get());
        return;
    }

    PaintBackground();
    PaintBoardArea();
    PaintInfoArea();

    SDL_Flip(screen.get());
}
std::string TetrisPainter::GetGameOverText(StatsCollection c) {
    /* TODO */
    return "";
}
void TetrisPainter::LoadSprites() {
    txt.Load(FILEPREFIX "gfx/LiberationMono-Regular.ttf",
             FILEPREFIX "gfx/LiberationMono-Bold.ttf",
             FILEPREFIX "gfx/LiberationMono-Italic.ttf");

    sprIcon.Load(FILEPREFIX "gfx/icon.png", 1, 0);
    sprIcon.SetAsIcon();

    sprBackgroundTile.Load(FILEPREFIX "gfx/t_none.png", game->Zoom(), 0);
    sprITile.Load(         FILEPREFIX "gfx/t_i.png", game->Zoom(), 0);
    sprJTile.Load(         FILEPREFIX "gfx/t_j.png", game->Zoom(), 0);
    sprLTile.Load(         FILEPREFIX "gfx/t_l.png", game->Zoom(), 0);
    sprOTile.Load(         FILEPREFIX "gfx/t_o.png", game->Zoom(), 0);
    sprSTile.Load(         FILEPREFIX "gfx/t_s.png", game->Zoom(), 0);
    sprTTile.Load(         FILEPREFIX "gfx/t_t.png", game->Zoom(), 0);
    sprZTile.Load(         FILEPREFIX "gfx/t_z.png", game->Zoom(), 0);

    sprBackground.Load(FILEPREFIX "gfx/p_background.jpg", game->Zoom(), 0);
}
void TetrisPainter::InitSystems() {
    screen.reset(SDL_SetVideoMode(
            /* 3x offset (left,right,mid), main area and preview area */
            (game->PixOffsetX() * 3 + game->Width() * game->CellLength() + 6 * game->CellLength()) * game->Zoom(),
            (game->PixOffsetY() * 2 + game->Height() * game->CellLength()) * game->Zoom(),
            24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF),
            SDL_FreeSurface);

    if (!screen)
        throw Exception(SDL_GetError());
}

}

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

TetrisPainter::TetrisPainter(BoardGame *p, BoardSettings &s) :
    Painter(), game(NULL)
{
    game = dynamic_cast<Tetris*>(p);

    if (!game)
        throw Exception("Game object not set");

    InitSystems();
    LoadSprites();
}

void TetrisPainter::Paint() {
    /* TODO */
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
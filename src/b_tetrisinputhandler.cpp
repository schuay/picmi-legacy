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

#include "b_tetrisinputhandler.h"

namespace BoardGame {

TetrisInputHandler::TetrisInputHandler(BoardGame *p)
{
    game = dynamic_cast<Tetris*>(p);
    if (!game)
        throw Exception("Game object not set");
}

/*  Implement custom key repeats here (use key pressed instead of key down event and check
    the amount of time passed since last action was taken).
 */

void TetrisInputHandler::HandleInput() {
    SDL_Event ev;

    while (SDL_PollEvent(&ev) == 1) {
        int dx = 0, op = OP_NONE;

        /* get input... */

        switch (ev.type) {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
                game->SetResolution(GR_ABORTED);
                break;
            case SDLK_p:
                game->SetPaused(!game->GetPaused());
                break;
            case SDLK_KP4:
            case SDLK_h:
            case SDLK_LEFT:
                dx = -1;
                break;
            case SDLK_KP6:
            case SDLK_l:
            case SDLK_RIGHT:
                dx = 1;
                break;
            case SDLK_KP8:
            case SDLK_k:
            case SDLK_UP:
                op = T_OP_DROPDOWN;
                break;
            case SDLK_KP2:
            case SDLK_j:
            case SDLK_DOWN:
                op = T_OP_STEPDOWN;
                break;
            case SDLK_x:
                op = T_OP_ROTATELEFT;
                break;
            case SDLK_c:
                op = T_OP_ROTATERIGHT;
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            game->SetResolution(GR_ABORTED);
            break;
        default:
            break;
        }

        /* perform actual logic... */

        if (dx)
            game->TrySetLocationRel(dx, 0);

        if (op != OP_NONE)
            game->DoOp(op);
    }
}

}

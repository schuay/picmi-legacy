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

#include "b_picinputhandler.h"
namespace BoardGame {
PicInputHandler::PicInputHandler(BoardGame* p)
{
    game = dynamic_cast<Picross*>(p);

    if (!game)
        throw Exception("Game object not set");

    dragDirection = DRAG_UNDEF;
    dragOperation = DRAG_UNDEF;

    InitSystems();
}

void PicInputHandler::InitSystems() {
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

int PicInputHandler::HandleMouseEvent(int x, int y, int btn, int event) {
    Point newLocation(
            (x - game->PixOffsetX()) / game->CellLength(),
            (y - game->PixOffsetY()) / game->CellLength());

    /* only handle mouse events in game board area */
    if (!game->IsInBounds(newLocation))
        return OP_NONE;

    switch (event) {
    case SDL_MOUSEBUTTONDOWN:
        lastClickLocation = newLocation;    /* remember where the first click happened so we can limit movement to that row/column during mouse drags */
        dragDirection = DRAG_UNDEF;         /* reset drag direction */
        dragOperation =                     /* set drag operation */
                game->GetStateAt(newLocation) == BOARD_CLEAN ? OP_FORCE_MARK : OP_FORCE_CLEAR;
        lastDragLocation = newLocation;     /* remember last handled tile so we only to a single op per tile on drags */
        break;
    case SDL_MOUSEMOTION:
        if (btn == SDL_BUTTON_LEFT || btn == SDL_BUTTON_RIGHT) {    /* only run drag logic if a mousebutton is pressed, otherwise only set location */
            if ( newLocation != lastClickLocation && dragDirection == DRAG_UNDEF ) { /* calc drag direction */
                unsigned int diffX = abs(lastClickLocation.x - newLocation.x);
                unsigned int diffY = abs(lastClickLocation.y - newLocation.y);
                if (diffX < diffY)
                    dragDirection = DRAG_VER;
                else if (diffX > diffY)
                    dragDirection = DRAG_HOR;
                else
                    dragDirection = DRAG_HOR;
            }

            if (dragDirection == DRAG_HOR)   /* adjust newLocation according to dragDirection */
                newLocation.y = game->GetLocation().y;
            else if (dragDirection == DRAG_VER)
                newLocation.x = game->GetLocation().x;

            if (lastDragLocation == newLocation)
                return OP_NONE; /* tile already handled, nothing to be done */
            else {
                lastDragLocation = newLocation;
            }
        }
        break;
    default:
        break;
    }

    game->TrySetLocation(newLocation);

    if (btn == SDL_BUTTON_LEFT)
        return OP_HIT;
    else if (btn == SDL_BUTTON_RIGHT)
        return dragOperation;

    return OP_NONE;
}
void PicInputHandler::HandleInput() {
    SDL_Event ev;

    while (SDL_PollEvent(&ev) == 1) {
        int dx = 0, dy = 0, op = OP_NONE;

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
            case SDLK_KP7:
            case SDLK_y:
                dx = -1;
                dy = -1;
                break;
            case SDLK_KP9:
            case SDLK_u:
                dx = 1;
                dy = -1;
                break;
            case SDLK_KP1:
            case SDLK_b:
                dx = -1;
                dy = 1;
                break;
            case SDLK_KP3:
            case SDLK_n:
                dx = 1;
                dy = 1;
                break;
            case SDLK_KP4:
            case SDLK_h:
            case SDLK_a:
            case SDLK_LEFT:
                dx = -1;
                break;
            case SDLK_KP6:
            case SDLK_l:
            case SDLK_d:
            case SDLK_RIGHT:
                dx = 1;
                break;
            case SDLK_KP8:
            case SDLK_k:
            case SDLK_w:
            case SDLK_UP:
                dy = -1;
                break;
            case SDLK_KP2:
            case SDLK_j:
            case SDLK_s:
            case SDLK_DOWN:
                dy = 1;
                break;
            case SDLK_KP0:
            case SDLK_SPACE:
                op = OP_HIT;
                break;
            case SDLK_KP5:
            case SDLK_RCTRL:
            case SDLK_LCTRL:
                op = OP_MARK;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            op = HandleMouseEvent(ev.button.x, ev.button.y, ev.button.button, ev.type);
            break;
        case SDL_MOUSEMOTION:
            if (ev.motion.state & SDL_BUTTON(1))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_LEFT, ev.type);
            else if (ev.motion.state & SDL_BUTTON(3))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_RIGHT, ev.type);
            else HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_NONE, ev.type);
            break;
         case SDL_QUIT:
            game->SetResolution(GR_ABORTED);
            break;
         default:
            break;
        }

        /* perform actual logic... */

        if (dx || dy)
            game->TrySetLocationRel(dx, dy);

        if (op != OP_NONE)
            game->DoOp(op);
    }
}
}

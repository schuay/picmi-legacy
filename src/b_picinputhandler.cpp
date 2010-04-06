/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
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
            (x - game->PixOffsetX() * game->Zoom()) / (game->CellLength() * game->Zoom()),
            (y - game->PixOffsetY() * game->Zoom()) / (game->CellLength() * game->Zoom()));

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
                game->Quit = true;
                break;
            case SDLK_LEFT:
                dx = -1;
                break;
            case SDLK_RIGHT:
                dx = 1;
                break;
            case SDLK_UP:
                dy = -1;
                break;
            case SDLK_DOWN:
                dy = 1;
                break;
            case SDLK_SPACE:
                op = OP_HIT;
                break;
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
            game->Quit = true;
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

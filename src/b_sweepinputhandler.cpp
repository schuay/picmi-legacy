/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweepinputhandler.h"
namespace BoardGame {
    SweepInputHandler::SweepInputHandler(BoardGame *p)
    {
        game = dynamic_cast<Sweeper*>(p);

        if (!game)
            throw Exception("Game object not set");

        InitSystems();
    }

    void SweepInputHandler::InitSystems() {
        SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
    }

    int SweepInputHandler::HandleMouseEvent(int x, int y, int btn) {
        Point newLocation(
                (x - game->PixOffsetX() * game->Zoom()) / (game->CellLength() * game->Zoom()),
                (y - game->PixOffsetY() * game->Zoom()) / (game->CellLength() * game->Zoom()));

        /* only handle mouse events in game board area */
        if (!game->IsInBounds(newLocation))
            return OP_NONE;

        game->TrySetLocation(newLocation);

        if (btn == SDL_BUTTON_LEFT)
            return S_OP_EXPOSE;
        else if (btn == SDL_BUTTON_RIGHT)
            return S_OP_MARK;
        else if (btn == SDL_BUTTON_MIDDLE)
            return S_OP_TENTATIVE;

        return OP_NONE;
    }
    void SweepInputHandler::HandleInput() {
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
                case SDLK_RCTRL:
                case SDLK_LCTRL:
                    op = S_OP_MARK;
                    break;
                case SDLK_SPACE:
                    op = S_OP_EXPOSE;
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                op = HandleMouseEvent(ev.button.x, ev.button.y, ev.button.button);
                break;
            case SDL_MOUSEMOTION:
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_NONE);
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

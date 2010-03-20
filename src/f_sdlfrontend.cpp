/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_sdlfrontend.h"

/* temp defines until input handling is moved to own class */
#define CELLLENGTH 24           // length of a single tile (width and height must be equal)
#define PUZZLE_POSX 200         // position of the board's left upper corner
#define PUZZLE_POSY 200
#define MAGNIFICATION_LEVEL 1   // zoom level, must be a whole number (1==100%, 2==200%, ...)


bool SDLFrontend::GetQuit() {
    return quit;
}

int SDLFrontend::HandleMouseEvent(int x, int y, int btn, int event) {
    PicPoint newLocation(
            (x - PUZZLE_POSX * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL),
            (y - PUZZLE_POSY * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL));

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
void SDLFrontend::ProcessInput() {
    SDL_Event ev;

    while (SDL_PollEvent(&ev) == 1) {
        int dx = 0, dy = 0, op = OP_NONE;

        /* get input... */

        switch (ev.type) {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_d:
                DebugKeyAction();
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
                op = OP_HIT;
                break;
            case SDLK_RSHIFT:
            case SDLK_LSHIFT:
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
            quit = true;
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

    game->CalculateStreakSolvedState();    /* prepare streaks for drawing */
}

void SDLFrontend::GameWon() {

    SDL_Delay(1000);

    /* empty event loop, then wait for user input */
    SDL_Event ev;
    while (SDL_PollEvent(&ev) == 1) {}

    while (!quit) {
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_QUIT)
            quit = true;
    }

    unsigned int elapsedRealTime = game->GetElapsedRealTime();
    unsigned int elapsedPenaltyTime = game->GetElapsedPenaltyTime();
    printf("\n-----------------------------\n\n"
           "Game solved in %u s (%u s real, %u s penalty)!\n\n"
           "------------------------------\n",
           elapsedRealTime + elapsedPenaltyTime, elapsedRealTime, elapsedPenaltyTime);
}

void SDLFrontend::DoMainLoop() {

    ProcessInput();
    painter->Paint();

    SDL_Delay(30);  /* relinquish cpu time we don't need */

    if (game->GameWon())
        GameWon();
}

void SDLFrontend::NewPuzzle(PicSettings &s) {

    if (game) {
        delete game;
        game = NULL;
    }
    if (painter) {
        delete painter;
        painter = NULL;
    }

    /* create puzzle */
    game = new Picross(s);
    painter = new PicPainter(game);


    /* initialize vars */

    dragDirection = DRAG_UNDEF;
    dragOperation = DRAG_UNDEF;
    quit = false;
}

void SDLFrontend::Initialize() {

    /* Initialize SDL systems */

    if (SDL_Init(SDL_INIT_VIDEO) == -1 ) {
        SDL_Quit();
        throw PicException(SDL_GetError());
    }

    SDL_WM_SetCaption(WINDOWCAPTION, NULL);

    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    TTF_Init();
}
SDLFrontend::SDLFrontend() {
    game = NULL;
    painter = NULL;

    Initialize();
}
SDLFrontend::~SDLFrontend() {
    if (game)
        delete game;
    if (painter)
        delete painter;

    TTF_Quit();
    SDL_Quit();
}

void SDLFrontend::DebugKeyAction() {
}

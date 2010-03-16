/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_sdlfrontend.h"

bool SDLFrontend::GetQuit() {
    return quit;
}

void SDLFrontend::ProcessDrawing() {
    DrawBackground();
    DrawInfoArea();
    DrawStreakArea();
    DrawBoardArea();
}
void SDLFrontend::DrawBackground() {
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));  /* paint bg white */
    sprBackground.Blit(PicPoint(0,0));
}
void SDLFrontend::DrawInfoArea() {
    SDL_Rect to;
    SDL_Color color;
    std::stringstream out;
    PicPoint p;

    to.x = to.y = 0;
    to.w = PUZZLE_POSX;
    to.h = PUZZLE_POSY;

    p.x = 10 * MAGNIFICATION_LEVEL;
    p.y = 10 * MAGNIFICATION_LEVEL;

    color.r = color.g = color.b = 255;


    SDL_FillRect(Screen, &to, SDL_MapRGB(Screen->format, 0, 0, 0)); /* info -> black bg */

    /* draw text */
    out << "Elapsed Time";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << "Total: " << curPuzzle->GetElapsedTime() << "s";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << "Real: " << curPuzzle->GetElapsedRealTime() << "s";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 25;

    out.str("");
    out << "Completed";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str());

    out.str("");
    out << "--------------";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 2;

    out.str("");
    out << std::fixed << std::setprecision(0) << curPuzzle->GetCompletedPercentageBoxes() << " % done";
    txt.Blit(out.str(), p, color, JUSTIFY_L);
    p.y += txt.HeightOf(out.str()) + 5;
}
void SDLFrontend::DrawStreakArea() {
    unsigned int i, j;
    PicPoint p;
    SDL_Color color;
    std::stringstream out;

    /* highlight active row/col - currently deactivated because streak gfx are not translucent*/

    p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL +
          curPuzzle->GetLocation().x*CELLLENGTH*MAGNIFICATION_LEVEL;
    for (int i = 0; i * CELLLENGTH < PUZZLE_POSX; i++) {
        p.y = i*CELLLENGTH*MAGNIFICATION_LEVEL;

        sprActiveTile.Blit(p);
    }
    p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL +
          curPuzzle->GetLocation().y*CELLLENGTH*MAGNIFICATION_LEVEL;
    for (int j = 0; j * CELLLENGTH < PUZZLE_POSX; j++) {
        p.x = j*CELLLENGTH*MAGNIFICATION_LEVEL;

        sprActiveTile.Blit(p);
    }

    /* streak areas */

    p.y = 0;
    for (i = 0; i < curPuzzle->Width(); i++) {
        p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (i%2 == 0)
            sprStreakAreaVerA.Blit(p, JUSTIFY_LB);
        else
            sprStreakAreaVerB.Blit(p, JUSTIFY_LB);
    }
    p.x = 0;
    for (j = 0; j < curPuzzle->Height(); j++) {
        p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (j%2 == 0)
            sprStreakAreaHorA.Blit(p, JUSTIFY_RT);
        else
            sprStreakAreaHorB.Blit(p, JUSTIFY_RT);
    }

    unsigned int streakLength;

    /* draw row streaks */
    for (i = 0; i < curPuzzle->Height(); i++) {
        streakLength = 0;

        for (int js = curPuzzle->RowStreaks[i].size() - 1; js >= 0; js--) {
            PicStreak s = curPuzzle->RowStreaks[i][js];    /* note the reverse order of loop  */
            color.r = color.g = color.b = s.Solved ? 200 : 0;       /* we need to do this to draw streaks in correct order */

            out.str("");
            out << s.GetLength() << ' ';

            p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL - 2*MAGNIFICATION_LEVEL - streakLength;
            p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL + i*MAGNIFICATION_LEVEL*CELLLENGTH;

            streakLength += txt.WidthOf(out.str()) + 2;
            txt.Blit(out.str(), p, color, JUSTIFY_R);
        }
    }

    /* draw col streaks */
    for (i = 0; i < curPuzzle->Width(); i++) {
        streakLength = 0;

        for (int js = curPuzzle->ColStreaks[i].size() - 1; js >= 0; js--) {
            PicStreak s = curPuzzle->ColStreaks[i][js];
            color.r = color.g = color.b = s.Solved ? 200 : 0;

            out.str("");    //clear the stream
            out << s.GetLength();

            streakLength += txt.HeightOf(out.str()) + 2;

            p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL     /* puzzle starting position */
                  + i*MAGNIFICATION_LEVEL*CELLLENGTH  /* plus the appropriate column position */
                  + 10*MAGNIFICATION_LEVEL;           /* and centre within column */
            p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL     /* puzzle starting position */
                  - streakLength                      /* stack numbers above each other */
                  - 2*MAGNIFICATION_LEVEL;            /* and adjust the whole stack upwards */

            txt.Blit(out.str(), p, color, JUSTIFY_C);
        }
    }
}
void SDLFrontend::DrawBoardArea() {
    unsigned int i, j;
    PicPoint p, q;

    for (i = 0; i < curPuzzle->Width(); i++) {
        for (j = 0; j < curPuzzle->Height(); j++) {
            p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL;
            p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL;

            q.x = i;
            q.y = j;
            
            /* active cells (and entire row / column) */
            if (q.x == curPuzzle->GetLocation().x || q.y == curPuzzle->GetLocation().y)
                sprActiveTile.Blit(p);

            /* cell frame */
            sprCellFrame.Blit(p);

            /* dividers (mark 5x5 areas */
            if ((i+1)%5 == 0) {
                sprDividerR.Blit(p);
            }
            else if (i%5 == 0) {
                sprDividerL.Blit(p);
            }
            if ((j+1)%5 == 0) {
                sprDividerD.Blit(p);
            }
            else if (j%5 == 0) {
                sprDividerU.Blit(p);
            }

            /* box / marked tiles */
            if (curPuzzle->GetStateAt(q) == BOARD_HIT) {
                sprBoxTile.Blit(p);
            }
            else if (curPuzzle->GetStateAt(q) == BOARD_MARKED) {
                sprMarkTile.Blit(p);
            }
        }
    }
}

int SDLFrontend::HandleMouseEvent(int x, int y, int btn, int event) {
    PicPoint newLocation(
            (x - PUZZLE_POSX * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL),
            (y - PUZZLE_POSY * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL));

    /* only handle mouse events in game board area */
    if (!curPuzzle->IsInBounds(newLocation))
        return OP_NONE;

    switch (event) {
    case SDL_MOUSEBUTTONDOWN:
        lastClickLocation = newLocation;    /* remember where the first click happened so we can limit movement to that row/column during mouse drags */
        dragDirection = DRAG_UNDEF;         /* reset drag direction */
        dragOperation =                     /* set drag operation */
                curPuzzle->GetStateAt(newLocation) == BOARD_CLEAN ? OP_FORCE_MARK : OP_FORCE_CLEAR;
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
                newLocation.y = curPuzzle->GetLocation().y;
            else if (dragDirection == DRAG_VER)
                newLocation.x = curPuzzle->GetLocation().x;

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

    curPuzzle->TrySetLocation(newLocation);

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
            curPuzzle->TrySetLocationRel(dx, dy);

        if (op != OP_NONE)
            curPuzzle->DoOp(op);
    }

    curPuzzle->CalculateStreakSolvedState();    /* prepare streaks for drawing */
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

    unsigned int elapsedRealTime = curPuzzle->GetElapsedRealTime();
    unsigned int elapsedPenaltyTime = curPuzzle->GetElapsedPenaltyTime();
    printf("\n-----------------------------\n\n"
           "Game solved in %u s (%u s real, %u s penalty)!\n\n"
           "------------------------------\n",
           elapsedRealTime + elapsedPenaltyTime, elapsedRealTime, elapsedPenaltyTime);
}

void SDLFrontend::DoMainLoop() {

    ProcessInput();
    ProcessDrawing();

    SDL_Flip(Screen);
    SDL_Delay(30);  /* relinquish cpu time we don't need */

    if (curPuzzle->GameWon())
        GameWon();
}

void SDLFrontend::NewPuzzle(PicSettings &s) {

    if (curPuzzle) {
        delete curPuzzle;
        curPuzzle = NULL;
    }

    /* create puzzle */
    curPuzzle = new Picross(s);

    if (Screen) {
        SDL_FreeSurface(Screen);
        Screen = NULL;
    }

    Screen = SDL_SetVideoMode(
            (PUZZLE_POSX + curPuzzle->Width() * CELLLENGTH + 5) * MAGNIFICATION_LEVEL,
            (PUZZLE_POSY + curPuzzle->Height() * CELLLENGTH + 5) * MAGNIFICATION_LEVEL,
            24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

    if (!Screen) {
        SDL_Quit();
        throw PicException(SDL_GetError());
    }

    /* initialize vars */

    dragDirection = DRAG_UNDEF;
    dragOperation = DRAG_UNDEF;
    quit = false;
}
void SDLFrontend::LoadBackground(std::string path) {
    std::string fullpath = FILEPREFIX + path;
    sprBackground.Load( fullpath, MAGNIFICATION_LEVEL, 0);
}

void SDLFrontend::Initialize() {

    /* Initialize SDL systems */

    if (SDL_Init(SDL_INIT_VIDEO) == -1 ) {
        SDL_Quit();
        throw PicException(SDL_GetError());
    }

    SDL_WM_SetCaption(GAMEBUILD, NULL);

    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    TTF_Init();

    /* Load resources */

    txt.Load(FILEPREFIX "gfx/cour.ttf");

    sprIcon.Load(FILEPREFIX "gfx/icon.png", 1, 0);
    sprIcon.SetAsIcon();

    sprCellFrame.Load(FILEPREFIX "gfx/cellframe.png", MAGNIFICATION_LEVEL, 0);
    sprBoxTile.Load(FILEPREFIX "gfx/box.png", MAGNIFICATION_LEVEL, 0);
    sprMarkTile.Load(FILEPREFIX "gfx/mark.png", MAGNIFICATION_LEVEL, 0);
    sprActiveTile.Load(FILEPREFIX "gfx/activecell.png", MAGNIFICATION_LEVEL, 0);

    sprDividerR.Load(FILEPREFIX "gfx/divider.png", MAGNIFICATION_LEVEL,0);
    sprDividerD.Load(FILEPREFIX "gfx/divider.png", MAGNIFICATION_LEVEL, 270);
    sprDividerL.Load(FILEPREFIX "gfx/divider.png", MAGNIFICATION_LEVEL, 180);
    sprDividerU.Load(FILEPREFIX "gfx/divider.png", MAGNIFICATION_LEVEL, 90);

    sprStreakAreaHorA.Load(FILEPREFIX "gfx/streakA.png", MAGNIFICATION_LEVEL, 0);
    sprStreakAreaHorB.Load(FILEPREFIX "gfx/streakB.png", MAGNIFICATION_LEVEL, 0);
    sprStreakAreaVerA.Load(FILEPREFIX "gfx/streakA.png", MAGNIFICATION_LEVEL, 270);
    sprStreakAreaVerB.Load(FILEPREFIX "gfx/streakB.png", MAGNIFICATION_LEVEL, 270);

    sprBackground.Load(FILEPREFIX "gfx/background.jpg", MAGNIFICATION_LEVEL, 0);
}
SDLFrontend::SDLFrontend() {
    Screen = NULL;
    curPuzzle = NULL;

    Initialize();
}
SDLFrontend::~SDLFrontend() {
    if (curPuzzle)
        delete curPuzzle;

    txt.~SDLText(); /* force deinitialization of font before TTF_Quit is called */

    TTF_Quit();
    SDL_Quit();
}

void SDLFrontend::DebugKeyAction() {
}

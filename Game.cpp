/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Game.h"

bool Game::GetQuit() {
    return quit;
}

void Game::ProcessDrawing() {
    unsigned int i, j;
    Point p, q;
    std::stringstream out;

    /* game board */

    sprBackground.Blit(Point(0,0));

    /* streak areas */

    p.y = PUZZLE_POSY - 200;
    for (i = 0; i < curPuzzle->Width; i++) {
        p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (i%2 == 0)
            sprStreakAreaVerA.Blit(p);
        else
            sprStreakAreaVerB.Blit(p);
    }
    p.x = PUZZLE_POSX - 200;
    for (j = 0; j < curPuzzle->Width; j++) {
        p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (j%2 == 0)
            sprStreakAreaHorA.Blit(p);
        else
            sprStreakAreaHorB.Blit(p);
    }

    /* main area */

    for (i = 0; i < curPuzzle->Width; i++) {
        for (j = 0; j < curPuzzle->Height; j++) {
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

    /* draw timer */
    out << curPuzzle->GetElapsedTime();

    p.x = TIMERX*MAGNIFICATION_LEVEL;
    p.y = TIMERY*MAGNIFICATION_LEVEL;

    txt.Blit(out.str(), p, JUSTIFY_R);

    SDL_Color c;
    unsigned int rowStreakLength;

    /* draw row streaks */
    for (i = 0; i < curPuzzle->Height; i++) {
        rowStreakLength = 0;

        for (int js = curPuzzle->RowStreaks[i].size() - 1; js >= 0; js--) {
            Streak s = curPuzzle->RowStreaks[i][js];    /* note the reverse order of loop  */
            c.r = c.g = c.b = s.Solved ? 200 : 0;       /* we need to do this to draw streaks in correct order */

            out.str("");
            out << s.GetLength() << ' ';

            p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL - 3*MAGNIFICATION_LEVEL - rowStreakLength*txt.Size/2;
            p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL + i*MAGNIFICATION_LEVEL*CELLLENGTH;

            rowStreakLength += out.str().length() + 1;
            txt.Blit(out.str(), p, c, JUSTIFY_R);
        }
    }

    /* draw col streaks */
    for (i = 0; i < curPuzzle->Width; i++) {
        for (j = 0; j < curPuzzle->ColStreaks[i].size(); j++) {
            Streak s = curPuzzle->ColStreaks[i][j];
            c.r = c.g = c.b = s.Solved ? 200 : 0;

            int drawLocation = curPuzzle->ColStreaks[i].size() - j;

            out.str("");    //clear the stream
            out << s.GetLength();

            p.x = PUZZLE_POSX*MAGNIFICATION_LEVEL     /* puzzle starting position */
                  + i*MAGNIFICATION_LEVEL*CELLLENGTH  /* plus the appropriate column position */
                  + 10*MAGNIFICATION_LEVEL;           /* and centre within column */
            p.y = PUZZLE_POSY*MAGNIFICATION_LEVEL     /* puzzle starting position */
                  - 10*drawLocation*2                 /* stack numbers above each other */
                  - 5*MAGNIFICATION_LEVEL;           /* and adjust the whole stack upwards */

            txt.Blit(out.str(), p, c, JUSTIFY_C);
        }
    }
}

int Game::HandleMouseEvent(int x, int y, int btn, int event) {
    Point newLocation(
            (x - PUZZLE_POSX * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL),
            (y - PUZZLE_POSY * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL));

    /* only handle mouse events in game board area */
    if (!curPuzzle->IsInBounds(newLocation))
        return OP_NONE;

    switch (event) {
    case SDL_MOUSEBUTTONDOWN:
        lastClickLocation = newLocation; /* remember where the first click happened so we can limit movement to that row/column during mouse drags */
        dragDirection = -1; /* reset drag direction */
        lastDragLocation = newLocation;  /* remember last handled tile so we only to a single op per tile on drags */
        break;
    case SDL_MOUSEMOTION:
        if (btn == SDL_BUTTON_LEFT || btn == SDL_BUTTON_RIGHT) {    /* only run drag logic if a mousebutton is pressed, otherwise only set location */
            if ( newLocation != lastClickLocation && dragDirection == -1 ) { /* calc drag direction */
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
        return OP_MARK;

        return OP_NONE;
}

void Game::ProcessInput() {
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
            op = HandleMouseEvent(ev.button.x, ev.button.y, ev.button.button, SDL_MOUSEBUTTONDOWN);
            break;
        case SDL_MOUSEMOTION:
            if (ev.motion.state & SDL_BUTTON(1))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_LEFT, SDL_MOUSEMOTION);
            else if (ev.motion.state & SDL_BUTTON(3))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_RIGHT, SDL_MOUSEMOTION);
            else HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_NONE, SDL_MOUSEMOTION);
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

        if (curPuzzle->GameWon()) {
            unsigned int elapsedRealTime = curPuzzle->GetElapsedRealTime();
            unsigned int elapsedPenaltyTime = curPuzzle->GetElapsedPenaltyTime();
            printf("\nGame solved in %u s (%u s real, %u s penalty)!\n\n",
                   elapsedRealTime + elapsedPenaltyTime, elapsedRealTime, elapsedPenaltyTime);
            quit = true;
        }
    }

    curPuzzle->CalculateStreakSolvedState();    /* prepare streaks for drawing */
}

void Game::Initialize() {

    /* Initialize SDL systems */

    if (SDL_Init(SDL_INIT_VIDEO) == -1 ) {
        SDL_Quit();
        throw PicrossException(SDL_GetError());
    }

    Screen = SDL_SetVideoMode(RESX * MAGNIFICATION_LEVEL, RESY * MAGNIFICATION_LEVEL, 24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

    if (!Screen) {
        SDL_Quit();
        throw PicrossException(SDL_GetError());
    }

    SDL_WM_SetCaption(GAMEBUILD, NULL);

    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    TTF_Init();

    /* Load resources */

    txt.Load(FILEPREFIX "gfx/cour.ttf");

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

    sprBackground.Load(FILEPREFIX "gfx/background.png", MAGNIFICATION_LEVEL, 0);
}

void Game::NewPuzzle(int type, unsigned int difficulty, bool noHintsMode) {

    if (curPuzzle) {
        delete curPuzzle;
        curPuzzle = NULL;
    }

    std::stringstream puzzleInitializer;

    switch (type) {
    case PUZ_STAT:
        puzzleInitializer <<
            "##.#.#.###.#.#." <<
            "#.#.#.#.#......" <<
            "###############" <<
            "#.#.#.#.#......" <<
            "###....##......" <<
            "#.#######......" <<
            "###....##......" <<
            "#.#....##......" <<
            "###....##......" <<
            "#.......#......" <<
            "#.#.#.........." <<
            "#.......#......" <<
            ".#.#..........." <<
            ".#.......#....." <<
            "#.#.....#......";

        curPuzzle = new Puzzle(15, 15, puzzleInitializer.str());
        break;
    case PUZ_RAND:
        curPuzzle = Puzzle::RandomPuzzle(15, 15, difficulty);
        break;
    default:
        curPuzzle = Puzzle::RandomPuzzle(15, 15, difficulty);
        break;
    }

    curPuzzle->NoHintsMode = noHintsMode;

    /* initialize vars */

    dragDirection = DRAG_UNDEF;

    quit = false;
}

Game::Game() {
    curPuzzle = NULL;
}
Game::~Game() {
    if (curPuzzle)
        delete curPuzzle;

    TTF_Quit();
    SDL_Quit();
}

void Game::DoMainLoop() {
    ProcessInput();

    ProcessDrawing();
    SDL_Flip(Screen);

    SDL_Delay(30);  /* relinquish cpu time we don't need */
}

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
    unsigned int i, j, x, y;
    std::stringstream out;

    /* game board */

    sprBackground.Blit(0, 0);

    /* streak areas */

    for (i = 0; i < curPuzzle->Width; i++) {
        x = PUZZLE_POSX*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (i%2 == 0)
            sprStreakAreaVerA.Blit(x, PUZZLE_POSY - 200);
        else
            sprStreakAreaVerB.Blit(x, PUZZLE_POSY - 200);
    }
    for (j = 0; j < curPuzzle->Width; j++) {
        y = PUZZLE_POSY*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL;
        if (j%2 == 0)
            sprStreakAreaHorA.Blit(PUZZLE_POSX - 200, y);
        else
            sprStreakAreaHorB.Blit(PUZZLE_POSX - 200, y);
    }


    for (i = 0; i < curPuzzle->Width; i++) {
        for (j = 0; j < curPuzzle->Height; j++) {
            x = PUZZLE_POSX*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL;
            y = PUZZLE_POSY*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL;

            /* cell frame */
            sprCellFrame.Blit(x,y);

            /* dividers (mark 5x5 areas */
            if ((i+1)%5 == 0) {
                sprDividerR.Blit(x,y);
            }
            else if (i%5 == 0) {
                sprDividerL.Blit(x,y);
            }
            if ((j+1)%5 == 0) {
                sprDividerD.Blit(x,y);
            }
            else if (j%5 == 0) {
                sprDividerU.Blit(x,y);
            }

            /* box tile */
            if (PUZSTATE(i,j) == MAP_HIT) {
                sprBoxTile.Blit(x,y);
            }

            /* marked tile */
            else if (PUZSTATE(i,j) == MAP_MARKED) {
                sprMarkTile.Blit(x,y);
            }
        }
    }

    /* draw timer */
    unsigned int elapsedTime = time(NULL) - startTime;
    out << elapsedTime + penaltyTime;
    txt.Blit(
            out.str(),
            Point(TIMERX*MAGNIFICATION_LEVEL,
                  TIMERY*MAGNIFICATION_LEVEL),
            JUSTIFY_R);


    /* draw row streaks */
    for (i = 0; i < curPuzzle->Height; i++) {
        out.str("");

        for (j = 0; j < curPuzzle->RowStreaks[i].size(); j++)
            out << curPuzzle->RowStreaks[i][j] << ' ';

        txt.Blit(out.str(),
                 Point(PUZZLE_POSX*MAGNIFICATION_LEVEL - 3*MAGNIFICATION_LEVEL,
                       PUZZLE_POSY*MAGNIFICATION_LEVEL + i*MAGNIFICATION_LEVEL*CELLLENGTH),
                 JUSTIFY_R);
    }

    /* draw col streaks */
    for (i = 0; i < curPuzzle->Width; i++) {
        out.str("");

        for (j = 0; j < curPuzzle->ColStreaks[i].size(); j++) {
            int drawLocation = curPuzzle->ColStreaks[i].size() - j;

            out.str("");    //clear the stream
            out << curPuzzle->ColStreaks[i][j];

            txt.Blit(
                    out.str(),

                    Point(PUZZLE_POSX*MAGNIFICATION_LEVEL     /* puzzle starting position */
                          + i*MAGNIFICATION_LEVEL*CELLLENGTH  /* plus the appropriate column position */
                          + 10*MAGNIFICATION_LEVEL,           /* and centre within column */

                          PUZZLE_POSY*MAGNIFICATION_LEVEL     /* puzzle starting position */
                          - 10*drawLocation*2                 /* stack numbers above each other */
                          - 5*MAGNIFICATION_LEVEL),           /* and adjust the whole stack upwards */
                    JUSTIFY_C);
        }
    }
}

int Game::HandleMouseEvent(int x, int y, int btn, int event) {
    Point _currentLocation(
            (x - PUZZLE_POSX * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL),
            (y - PUZZLE_POSY * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL));

    /* only handle mouse events in game board area */
    if (_currentLocation.x < 0 || _currentLocation.x >= curPuzzle->Width ||
        _currentLocation.y < 0 || _currentLocation.y >= curPuzzle->Height)
        return OP_NONE;

    switch (event) {
    case SDL_MOUSEBUTTONDOWN:
        lastClickLocation = _currentLocation; /* remember where the first click happened so we can limit movement to that row/column during mouse drags */
        dragDirection = -1; /* reset drag direction */
        lastDragLocation = _currentLocation;  /* remember last handled tile so we only to a single op per tile on drags */
        break;
    case SDL_MOUSEMOTION:
        if ( _currentLocation != lastClickLocation && dragDirection == -1 ) { /* calc drag direction */
            unsigned int diffX = abs(lastClickLocation.x - _currentLocation.x);
            unsigned int diffY = abs(lastClickLocation.y - _currentLocation.y);
            if (diffX < diffY)
                dragDirection = DRAG_VER;
            else if (diffX > diffY)
                dragDirection = DRAG_HOR;
            else
                dragDirection = DRAG_HOR;
        }

        if (dragDirection == DRAG_HOR)   /* adjust _currentLocation according to dragDirection */
            _currentLocation.y = currentLocation.y;
        else if (dragDirection == DRAG_VER)
            _currentLocation.x = currentLocation.x;

        if (lastDragLocation == _currentLocation)
            return OP_NONE; /* tile already handled, nothing to be done */
        else {
            lastDragLocation = _currentLocation;
        }

        break;
    default:
        break;
    }

    currentLocation = _currentLocation;

    if (btn == SDL_BUTTON_LEFT)
        return OP_HIT;
    else if (btn == SDL_BUTTON_RIGHT)
        return OP_MARK;

        return OP_NONE;
}

void Game::ProcessInput() {
    SDL_Event ev;
    int dx = 0, dy = 0, op = OP_NONE;

    while (SDL_PollEvent(&ev) == 1) {
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
            break;
         default:
            break;
        }
        ProcessLogic(dx, dy, op);
    }
}

void Game::ProcessLogic(int dx, int dy, int op) {

    /* movement logic */
    if (currentLocation.x + dx < curPuzzle->Width &&
        currentLocation.x + dx >= 0)
        currentLocation.x += dx;
    if (currentLocation.y + dy < curPuzzle->Height &&
        currentLocation.y + dy >= 0)
        currentLocation.y += dy;

    /* hit/mark logic */
    if (PUZSTATEP(currentLocation) == MAP_HIT) {}    /* we cannot mark spots that are already hit */
    else if (op == OP_MARK) {
        if (PUZSTATEP(currentLocation) == MAP_MARKED)
            PUZSTATEP(currentLocation) = MAP_CLEAN;
        else
            PUZSTATEP(currentLocation) = MAP_MARKED;
    }
    else if (op == OP_HIT) {                                 /* HIT */
        if (PUZSTATEP(currentLocation) == MAP_MARKED)             /* was marked -> unmarked */
            PUZSTATEP(currentLocation) = MAP_CLEAN;
        else if (PUZMAPP(currentLocation) == MAP_TRUE)      /* if correct -> hit */
            PUZSTATEP(currentLocation) = MAP_HIT;
        else if (PUZMAPP(currentLocation) == MAP_FALSE) {     /* if incorrect -> marked and add to penaltyTime*/
            PUZSTATEP(currentLocation) = MAP_MARKED;
            penaltyTime += 120*penaltyMultiplier++;
        }
    }

    if (curPuzzle->GameWon()) {
        unsigned int elapsedTime = time(NULL) - startTime;
        printf("Game solved in %u s (%u s real, %u s penalty)!", elapsedTime + penaltyTime, elapsedTime, penaltyTime);
        quit = true;
    }
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

void Game::NewPuzzle(int type, unsigned int difficulty) {

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

    /* initialize vars */

    dragDirection = DRAG_UNDEF;

    penaltyMultiplier = 1;
    penaltyTime = 0;

    quit = false;

    startTime = time(NULL);
}

Game::Game() {
    curPuzzle = NULL;
}
Game::~Game() {
    if (curPuzzle)
        delete curPuzzle;

    TTF_Quit();
}

void Game::DoMainLoop() {
    ProcessInput();
    ProcessDrawing();
}

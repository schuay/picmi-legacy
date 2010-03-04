/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Game.h"

#define CELLLENGTH 12
#define PUZZLE_POSX 117
#define PUZZLE_POSY 107
#define OP_NONE 0
#define OP_HIT 1
#define OP_MARK 2
#define MAGNIFICATION_LEVEL 2

bool Game::GetQuit() {
    return quit;
}

void Game::ProcessDrawing() {
    unsigned int i, j;

    /* game board */

    FIFTEEN.GB_SetXY(PUZZLE_POSX * MAGNIFICATION_LEVEL, PUZZLE_POSY * MAGNIFICATION_LEVEL);
    FIFTEEN.GB_ShowSprite(0,0);

    for (i = 0; i < currentPuzzle->Height; i++) {
        for (j = 0; j < currentPuzzle->Width; j++) {
            if (currentPuzzle->BoardState[i*currentPuzzle->Width + j] == MAP_HIT) {
                PushedBlock.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL,
                                     PUZZLE_POSY*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL);
                PushedBlock.GB_ShowSprite(0,0);
            }
            else if (currentPuzzle->BoardState[i*currentPuzzle->Width + j] == MAP_MARKED) {
                CheckedBlock.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + j*CELLLENGTH*MAGNIFICATION_LEVEL,
                                      PUZZLE_POSY*MAGNIFICATION_LEVEL + i*CELLLENGTH*MAGNIFICATION_LEVEL);
                CheckedBlock.GB_ShowSprite(0,0);
            }
        }
    }


    /* draw row streaks */
    for (i = 0; i < currentPuzzle->Height; i++) {
        std::stringstream out;

        for (j = 0; j < currentPuzzle->RowStreaks[i].size(); j++)
            out << currentPuzzle->RowStreaks[i][j] << ' ';

        GB_DrawText(out.str().c_str(),
                    PUZZLE_POSX*MAGNIFICATION_LEVEL - 10*out.str().length() - 5*MAGNIFICATION_LEVEL,
                    PUZZLE_POSY*MAGNIFICATION_LEVEL + i*MAGNIFICATION_LEVEL*CELLLENGTH);
    }

    /* draw col streaks */
    for (i = 0; i < currentPuzzle->Width; i++) {
        std::stringstream out;

        for (j = 0; j < currentPuzzle->ColStreaks[i].size(); j++)
            out << currentPuzzle->ColStreaks[i][j] << ' ';

        GB_DrawTextVert(out.str().c_str(),
                    PUZZLE_POSX*MAGNIFICATION_LEVEL + i*MAGNIFICATION_LEVEL*CELLLENGTH - 4,
                    PUZZLE_POSY*MAGNIFICATION_LEVEL - 10*out.str().length() - 5*MAGNIFICATION_LEVEL);
    }


    /* set movable object positions */
    Mattoc.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL,
                    PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL);
    HitMattoc.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL,
                       PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL);

    HorBar.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL - 8,
                    PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL - 1);
    VertBar.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL,
                     PUZZLE_POSY*MAGNIFICATION_LEVEL-8);

    Erase.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL - 5,
                   PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL + 10);
    EraseBlock.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL - 5,
                        PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL + 10);

    Check.GB_SetXY(PUZZLE_POSX*MAGNIFICATION_LEVEL + mapX*CELLLENGTH*MAGNIFICATION_LEVEL,
                   PUZZLE_POSY*MAGNIFICATION_LEVEL + mapY*CELLLENGTH*MAGNIFICATION_LEVEL+ 12);

    /* draw movable objects */

    Mattoc.GB_ShowSprite(0,(MattocShowFrame/2)%4);
    SDL_Delay(30);
    MattocShowFrame++;
}

int Game::HandleMouseEvent(int x, int y, int btn) {
    int _mapX, _mapY;

    _mapX = (x - PUZZLE_POSX * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL);
    _mapY = (y - PUZZLE_POSY * MAGNIFICATION_LEVEL) / (CELLLENGTH * MAGNIFICATION_LEVEL);

    if (_mapX < 0 || _mapX >= currentPuzzle->Width ||
        _mapY < 0 || _mapY >= currentPuzzle->Height)
        return OP_NONE;

    mapX = _mapX;
    mapY = _mapY;

    if (btn == SDL_BUTTON_LEFT)
        return OP_HIT;
    else if (btn == SDL_BUTTON_RIGHT)
        return OP_MARK;

    return OP_NONE;
}

void Game::ProcessLogic() {
    int	dx = 0,
        dy = 0,
        op = OP_NONE;


    /* process input */

    SDL_Event ev;

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
            op = HandleMouseEvent(ev.button.x, ev.button.y, ev.button.button);
            break;
        case SDL_MOUSEMOTION:
            if (ev.motion.state & SDL_BUTTON(1))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_LEFT);
            else if (ev.motion.state & SDL_BUTTON(3))
                op = HandleMouseEvent(ev.motion.x, ev.motion.y, SDL_BUTTON_RIGHT);
            break;
         default:
            break;
        }
    }

    /* movement logic */
    if (mapX + dx < currentPuzzle->Width &&
        mapX + dx >= 0)
        mapX += dx;
    if (mapY + dy < currentPuzzle->Height &&
        mapY + dy >= 0)
        mapY += dy;

    /* hit/mark logic */
    if (currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] == MAP_HIT) {}    /* we cannot mark spots that are already hit */
    else if (op == OP_MARK) {
        if (currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] == MAP_MARKED)
            currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] = MAP_CLEAN;
        else
            currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] = MAP_MARKED;
    }
    else if (op == OP_HIT) {                                 /* HIT */
        if (currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] == MAP_MARKED)             /* was marked -> unmarked */
            currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] = MAP_CLEAN;
        else if (currentPuzzle->Map[mapY*currentPuzzle->Width + mapX] == MAP_TRUE)      /* if correct -> hit */
            currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] = MAP_HIT;
        else if (currentPuzzle->Map[mapY*currentPuzzle->Width + mapX] == MAP_FALSE)      /* if incorrect -> marked */
            currentPuzzle->BoardState[mapY*currentPuzzle->Width + mapX] = MAP_MARKED;
    }

    /* ANIMATIONS

    if(hit == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);   // %5
    }
    if(erase == 1) {
        if(tempMap[mapY][mapX] == ' ') {
            EraseBlock.GB_ShowSprite(0,EraseBlockShowFrame);   // %4
        } else {
            //	Erase.GB_ShowSprite(0,EraseShowFrame);   // %4
        }
    }
    if(hitcheck == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);   // %7
    }
    if(check == 1) {
        Check.GB_ShowSprite(0,CheckShowFrame);  // %6
    }

    */
}

void Game::Initialize() {

    /* Initiate audio, video and the text */

    GB_Init(GB_INIT_VIDEO_AND_AUDIO, RESX * MAGNIFICATION_LEVEL, RESY * MAGNIFICATION_LEVEL);
    GB_LoadTextBitmap();

    FIFTEEN.GB_LoadSprite("gfx/FIFTEEN-grid.bmp", 1, 1, MAGNIFICATION_LEVEL);
    FIFTEEN.GB_SetColorKey(255,0,255);

    PushedBlock.GB_LoadSprite("gfx/pushed_block.bmp", 1, 1, MAGNIFICATION_LEVEL);
    CheckedBlock.GB_LoadSprite("gfx/checked_block.bmp", 1, 1, MAGNIFICATION_LEVEL);

    HorBar.GB_LoadSprite("gfx/horcursor.bmp", 1, 1, MAGNIFICATION_LEVEL);       // Load horizontal bar
    HorBar.GB_SetColorKey(255,0,255);

    VertBar.GB_LoadSprite("gfx/vertcursor.bmp", 1, 1, MAGNIFICATION_LEVEL);       // Load vertical bar
    VertBar.GB_SetColorKey(255,0,255);

    Mattoc.GB_LoadSprite("gfx/mattoc.bmp", 1, 4, MAGNIFICATION_LEVEL);
    Mattoc.GB_SetColorKey(255,0,255);

    HitMattoc.GB_LoadSprite("gfx/hitmattoc2.bmp", 1, 5, MAGNIFICATION_LEVEL);
    HitMattoc.GB_SetColorKey(255,0,255);

    Check.GB_LoadSprite("gfx/check.bmp", 1, 7, MAGNIFICATION_LEVEL);
    Check.GB_SetColorKey(255,0,255);

    Erase.GB_LoadSprite("gfx/erase.bmp", 1, 4, MAGNIFICATION_LEVEL);
    Erase.GB_SetColorKey(255,0,255);

    EraseBlock.GB_LoadSprite("gfx/erase_block.bmp", 1, 4, MAGNIFICATION_LEVEL);
    EraseBlock.GB_SetColorKey(255,0,255);

    BG.GB_LoadBackground("gfx/FIFTEEN.bmp", MAGNIFICATION_LEVEL);

    Quit.GB_LoadSprite("gfx/quit.bmp", 1, 5, MAGNIFICATION_LEVEL);
    Quit.GB_SetColorKey(255,0,255);
    Quit.GB_SetXY(486,400);
}

Game::Game() {

    std::stringstream puzzleInitializer;
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

    currentPuzzle = new Puzzle(15, 15, puzzleInitializer.str());

    mapX = 0;
    mapY = 0;

    MattocShowFrame = 0;
    HitMattocShowFrame = 0;
    EraseShowFrame = 0;
    CheckShowFrame = 0;
    EraseBlockShowFrame = 0;

    quit = false;
}
Game::~Game() {
    if (currentPuzzle)
        delete currentPuzzle;
}

void Game::DoMainLoop() {
    BG.GB_ShowBackground();
    ProcessLogic();
    ProcessDrawing();
}

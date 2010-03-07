/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GameBlade.h"
#include "Puzzle.h"
#include "Point.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <time.h>

#define CELLLENGTH 24
#define PUZZLE_POSX 234
#define PUZZLE_POSY 214
#define OP_NONE 0
#define OP_HIT 1
#define OP_MARK 2
#define MAGNIFICATION_LEVEL 1
#define DRAG_UNDEF -1
#define DRAG_HOR 0
#define DRAG_VER 1
#define PUZ_RAND 1
#define PUZ_STAT 0
#define FILEPREFIX ""

#define TIMERX 160
#define TIMERY 170

#define RESX 640
#define RESY 580

#define PUZSTATE(X,Y) curPuzzle->BoardState[Y*curPuzzle->Width + X]
#define PUZMAP(X,Y) curPuzzle->Map[Y*curPuzzle->Width + X]

#define PUZSTATEP(A) curPuzzle->BoardState[A.y*curPuzzle->Width + A.x]
#define PUZMAPP(A) curPuzzle->Map[A.y*curPuzzle->Width + A.x]


class Game {
public:

    Game();
    ~Game();

    void Initialize();
    void NewPuzzle(int type, unsigned int difficulty);
    void DoMainLoop();
    bool GetQuit();

private:

    void ProcessInput();
    void ProcessDrawing();
    void ProcessLogic(int dx, int dy, int op);

    int HandleMouseEvent(int x, int y, int btn, int event);

    Point
        currentLocation,
        lastClickLocation,
        lastDragLocation;

    int dragDirection;

    unsigned int
            startTime,
            penaltyTime,
            penaltyMultiplier;

    bool
        quit;

    GB_Sprite
        sprCellFrame,
        PushedBlock,
        CheckedBlock,
        Mattoc,
        HitMattoc,
        Erase,
        EraseBlock,
        Check,
        BG;

    Puzzle *curPuzzle;
};

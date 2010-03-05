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

#include <vector>
#include <sstream>
#include <iostream>

#define CELLLENGTH 12
#define PUZZLE_POSX 117
#define PUZZLE_POSY 107
#define OP_NONE 0
#define OP_HIT 1
#define OP_MARK 2
#define MAGNIFICATION_LEVEL 2
#define DRAG_UNDEF -1
#define DRAG_HOR 0
#define DRAG_VER 1
#define PUZ_RAND 1
#define PUZ_STAT 0

class Game {
public:

    Game();
    ~Game();

    void ProcessInput();
    void ProcessDrawing();
    void ProcessLogic(int dx, int dy, int op);
    void Initialize();
    void NewPuzzle(int type, unsigned int difficulty);
    void DoMainLoop();
    bool GetQuit();

private:

    int HandleMouseEvent(int x, int y, int btn, int event);

    unsigned int
        mapX,
        mapY,
        clickX,
        clickY,
        lastHandledMouseX,
        lastHandledMouseY;

    /* vars from original 2004 state of game */
    int MattocShowFrame,
        HitMattocShowFrame,
        EraseShowFrame,
        CheckShowFrame,
        EraseBlockShowFrame,
        dragDirection;

    bool
        quit;

    GB_Sprite
        FIFTEEN,
        PushedBlock,
        CheckedBlock,
        Mattoc,
        HitMattoc,
        Erase,
        EraseBlock,
        Check,
        BG;

    Puzzle *currentPuzzle;
};

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

class Game {
public:

    Game();
    ~Game();

    void ProcessInput();
    void ProcessDrawing();
    void ProcessLogic(int dx, int dy, int op);
    void Initialize();
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

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

class Game {
    public:

    Game();
    ~Game();

    void DrawStreaks();
    void ProcessDrawing();
    void ProcessLogic();
    void Initialize();
    void DoMainLoop();
    bool GetQuit();

    private:

    unsigned int
        level_size,         //the length of a level side (currently levels must be square)
        mapX,
        mapY;

    /* vars from original 2004 state of game */
    int level,
        hit,
        erase,
        hitcheck,
        check,
        MattocShowFrame,
        HitMattocShowFrame,
        EraseShowFrame,
        CheckShowFrame,
        EraseBlockShowFrame;

    bool quit;

    GB_Sprite
        FIFTEEN,
        PushedBlock,
        CheckedBlock,
        Mattoc,
        HitMattoc,
        Erase,
        EraseBlock,
        Check,
        HorBar,
        VertBar,
        Quit;

    GB_Background BG;

    Puzzle *currentPuzzle;
};

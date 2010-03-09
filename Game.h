/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <sstream>

#include "Globals.h"
#include "Streak.h"
#include "Puzzle.h"
#include "Point.h"
#include "Sprite.h"
#include "Text.h"

#define CELLLENGTH 24           // length of a single tile (width and height must be equal)
#define PUZZLE_POSX 234         // position of the board's left upper corner
#define PUZZLE_POSY 214
#define MAGNIFICATION_LEVEL 1   // zoom level, must be a whole number (1==100%, 2==200%, ...)
#define DRAG_UNDEF -1           // defines for drag locking
#define DRAG_HOR 0
#define DRAG_VER 1
#define PUZ_RAND 1              // defines for used puzzle type
#define PUZ_STAT 0
#define FILEPREFIX ""           // set the location of gfx/fonts
#define SDL_BUTTON_NONE -1      // used for handling mouse motion events with no buttons pressed

#define TIMERX 160              // location of the timer
#define TIMERY 170

#define RESX 640                // resolution of game window
#define RESY 580

#define GAMEBUILD "Tux Picross v.0.1"

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
        lastClickLocation,
        lastDragLocation;

    int dragDirection;

    bool
        quit;

    Sprite
        sprCellFrame,
        sprBoxTile,
        sprMarkTile,
        sprDividerR,
        sprDividerD,
        sprDividerL,
        sprDividerU,
        sprActiveTile,
        sprStreakAreaHorA,
        sprStreakAreaHorB,
        sprStreakAreaVerA,
        sprStreakAreaVerB,
        sprBackground;

    Text txt;

    Puzzle *curPuzzle;
};

#endif // GAME_H

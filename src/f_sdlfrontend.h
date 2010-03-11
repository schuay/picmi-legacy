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
#include <iomanip>

#include "b_picross.h"

#include "f_sdlglobals.h"
#include "f_sdlsprite.h"
#include "f_sdltext.h"

#define CELLLENGTH 24           // length of a single tile (width and height must be equal)
#define PUZZLE_POSX 200         // position of the board's left upper corner
#define PUZZLE_POSY 200
#define MAGNIFICATION_LEVEL 1   // zoom level, must be a whole number (1==100%, 2==200%, ...)
#define DRAG_UNDEF -1           // defines for drag locking
#define DRAG_HOR 0
#define DRAG_VER 1
#define FILEPREFIX ""           // set the location of gfx/fonts
#define SDL_BUTTON_NONE -1      // used for handling mouse motion events with no buttons pressed

#define TIMERX 10              // location of the timer
#define TIMERY 10

#define GAMEBUILD "Tux Picross v.0.1"

class SDLFrontend {
public:

    SDLFrontend();
    ~SDLFrontend();

    void NewPuzzle(PicSettings &s);
    void DoMainLoop();
    bool GetQuit();

private:

    void Initialize();

    void ProcessInput();
    void ProcessDrawing();
    void ProcessLogic(int dx, int dy, int op);

    void DrawBackground();
    void DrawInfoArea();
    void DrawStreakArea();
    void DrawBoardArea();

    void DebugKeyAction();

    int HandleMouseEvent(int x, int y, int btn, int event);

    PicPoint
        lastClickLocation,
        lastDragLocation;

    int dragDirection;

    bool
        quit;

    SDLSprite
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

    SDLText txt;

    Picross *curPuzzle;
};

#endif // GAME_H

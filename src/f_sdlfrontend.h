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

#include "f_sdldefines.h"
#include "f_sdlglobals.h"
#include "f_sdlsprite.h"
#include "f_sdltext.h"

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

    int dragDirection,
        dragOperation;

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
        sprBackground,
        sprIcon;

    SDLText txt;

    Picross *curPuzzle;
};

#endif // GAME_H

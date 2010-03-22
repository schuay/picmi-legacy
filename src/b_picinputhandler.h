/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_PICINPUTHANDLER_H
#define B_PICINPUTHANDLER_H

#include <SDL/SDL.h>

#include "b_picross.h"
#include "b_inputhandler.h"

#define DRAG_UNDEF -1           // defines for drag locking
#define DRAG_HOR 0
#define DRAG_VER 1

#define SDL_BUTTON_NONE -1      // used for handling mouse motion events with no buttons pressed
namespace BoardGame {
class PicInputHandler : public InputHandler
{
public:
    PicInputHandler(BoardGame* p);

    void HandleInput();

private:

    void InitSystems();

    void DebugKeyAction();

    int HandleMouseEvent(int x, int y, int btn, int event);

    Point
        lastClickLocation,
        lastDragLocation;

    int dragDirection,
        dragOperation;

    Picross* game;
};
}
#endif // B_PICINPUTHANDLER_H

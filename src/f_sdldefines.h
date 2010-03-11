/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef F_SDLDEFINES_H
#define F_SDLDEFINES_H



#define CELLLENGTH 24           // length of a single tile (width and height must be equal)
#define PUZZLE_POSX 200         // position of the board's left upper corner
#define PUZZLE_POSY 200
#define MAGNIFICATION_LEVEL 1   // zoom level, must be a whole number (1==100%, 2==200%, ...)

#define DRAG_UNDEF -1           // defines for drag locking
#define DRAG_HOR 0
#define DRAG_VER 1

#define DRAG_OP_UNDEF -1
#define DRAG_OP_MARK 0          // defines for drag op locking
#define DRAG_OP_CLEAR 1

#define FILEPREFIX ""           // set the location of gfx/fonts
#define SDL_BUTTON_NONE -1      // used for handling mouse motion events with no buttons pressed

#define GAMEBUILD "Tux Picross v.0.1"



#endif // F_SDLDEFINES_H

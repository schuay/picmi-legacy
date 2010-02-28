/***************************************************************************
                          GB_Globals.h  -  description
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/19 07:41:45 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.6 $
    filename             : $RCSfile: GB_Globals.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_GLOBALS_H_
#define _GB_GLOBALS_H_

// The screen surface the game blits the sprites and backgrounds to
extern SDL_Surface *Screen;

// The surface of the bitmap font. If you don't need it, uncomment it
extern SDL_Surface *GFXText;

// Whether audio output is enabled or not, set automatically by
// the sound engine
extern int AudioEnabled;

// Whether the screen is locked at the moment
extern int ScreenLocked;

#endif

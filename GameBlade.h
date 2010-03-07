/***************************************************************************
               GameBlade.h  - Main header file of the GameBlade
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 16:12:12 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.5 $
    filename             : $RCSfile: GameBlade.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef _GAMEBLADE_H_
#define _GAMEBLADE_H_

#include <stdlib.h>
#include <string.h>

// Section 0: SDL includes

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

// Section 1: Declaration headers

#include "GB_Definitions.h"

// Section 2: Globals

#include "GB_Globals.h"

// Section 3: The headers for the interfaces to SDL and the other libraries

#include "GB_VideoSystem.h"      // Setting video mode, freeing surfaces
#include "GB_TextEngine.h"       // Loading a bitmap font and displaying a text or a single character
#include "GB_System.h"           // Quitting the GameBlade

// Section 4: Custom

#include "PicrossException.h"

#endif

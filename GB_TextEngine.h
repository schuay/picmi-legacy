/***************************************************************************
                    GB_TextEngine.h  -  description
                             -------------------
    begin                :  Oct 5 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:25:38 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_TextEngine.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_TEXTENGINE_H_
#define _GB_TEXTENGINE_H_

// Load the standard font. Call this before drawing anything to the screen

void GB_LoadTextBitmap();

// Draw one single character to the screen

void GB_DrawCharacter( int Character, int X, int Y );

// Draw a string to the screen at the coordinates WXStart and WYStart

void GB_DrawText( const char *TextToDraw, int WXStart, int WYStart );

// Draw a string vertically to the screen at the coordinates WXStart and WYStart

void GB_DrawTextVert( const char *TextToDraw, int WXStart, int WYStart );

#endif


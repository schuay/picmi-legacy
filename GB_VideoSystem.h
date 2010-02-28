/***************************************************************************
                          GB_VideoSystem.h
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:31:27 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.4 $
    filename             : $RCSfile: GB_VideoSystem.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_VIDEOSYSTEM_H_
#define _GB_VIDEOSYSTEM_H_

// Set the video mode according to the values in the Definitions.h header
void GB_SetupSDL_Video();

// Free the surfaces if you are not using them anymore
void GB_FreeSurfaces();

// Hide the cursor to get rid of annoying blinking behaviour
void GB_HideMouseCursor();

// Hide the cursor to get rid of annoying blinking behaviour
void GB_ShowMouseCursor();

// Function for locking the screen. Please call this before you use GB_DrawPixel!!!
void GB_LockScreen();

// Call this after you finished the use of GB_DrawPixel!!!
void GB_UnlockScreen();

// Draws a pixel on the screen at coordinates x, y with the RGB value r, g, b
// Most code was taken from the SDL documents
void GB_DrawPixel( int GB_DPx, int GB_DPy, Uint8 GB_DPr, Uint8 GB_DPg, Uint8 GB_DPb );

// Function to get the RGB components of a pixel of the screen surface
// Lock the screen first!!!
// The biggest part of the code was taken from the SDL docs
void GB_GetPixel( int GB_GPx, int GB_GPy, Uint8 *GB_GPr, Uint8 *GB_GPg, Uint8 *GB_GPb );

// Fill the whole screen with a specific color
void GB_FillScreen( Uint8 GB_CSr, Uint8 GB_CSg, Uint8 GB_CSb );

// Clear the screen ( fill with the color black )
void GB_ClearScreen();

void GB_FillScreenRect( int GB_FSR_x, int GB_FSR_y, int GB_FSR_w, int GB_FSR_h,
                        Uint8 GB_FSR_r, Uint8 GB_FSR_g, Uint8 GB_FSR_b );

#endif

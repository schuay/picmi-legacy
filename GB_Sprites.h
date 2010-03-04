/***************************************************************************
        GB_Sprites.h  -  Class for loading and displaying sprites
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/21 21:20:23 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.14 $
    filename             : $RCSfile: GB_Sprites.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_SPRITES_H_
#define _GB_SPRITES_H_

#include "GameBlade.h"
#include <string>

// Class for loading a sprite from a file, setting it's color key and displaying it.
// This class also takes care of frames.

class GB_Sprite
{
  // Declare GB_Collision friend to allow access to the
  // private variables
  friend class GB_Collision;

  private:
    SDL_Surface *SpriteSurface;

    int Height, Width, HFrames, VFrames, FrameHeight, FrameWidth;
    int SpriteX, SpriteY;
    int HFrame, VFrame;

    // New members for collision detection
    int CollHeight, CollWidth, CollXOffset, CollYOffset;

    Uint8   Alpha;
    double  Angle;
    double  ZoomFactor;

    Uint8 ColorKeyRed, ColorKeyGreen, ColorKeyBlue;
    Uint32 ColorKey; 

    float CollWidthFactor, CollHeightFactor;

    int  RotZoomEnabled;
    int SmoothingEnabled;

  public:

    GB_Sprite();
    ~GB_Sprite();

    void GB_LoadSprite( std::string, int HFrameNr = 1, int VFrameNr = 1, int MagFactor = 1 );
    void GB_ShowSprite( int HFrameN, int VFrameN );

    void   GB_SetColorKey( Uint8, Uint8, Uint8 );
    void   GB_GetColorKey( Uint8 *, Uint8 *, Uint8 * );
    void   GB_SetAlpha( Uint8 );
    Uint8  GB_GetAlpha();

    void   GB_SetRotation( double );
    double GB_GetRotation();

    // This is set automatically since 20021016, so the user doesn't need to use it
    void GB_EnableRotZoom();
    void GB_DisableRotZoom();

    void   GB_SetZoom( double );
    double GB_GetZoom();

    void   GB_EnableSmoothing();
    void   GB_DisableSmoothing();

    void   GB_SetCollBox( float, float );

    void   GB_SetXY( int, int );
    int    GB_GetX();
    int    GB_GetY();
};

#endif

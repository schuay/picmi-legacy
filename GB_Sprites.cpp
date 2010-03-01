/***************************************************************************
        
	GB_Sprites.cpp  -  Class for loading and displaying sprites,
	                   manipulating them etc.
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/21 21:20:23 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.16 $
    filename             : $RCSfile: GB_Sprites.cpp,v $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GB_Sprites.h"
#include <cstdlib>
#include <string>

// Class for loading a sprite from a file, setting it's color key and displaying it.
// This class also takes care of frames.

// Set the Color Key, that means, which type of pixels will not be display on the screen

void GB_Sprite::GB_SetColorKey( Uint8 GB_SCKRed, Uint8 GB_SCKGreen, Uint8 GB_SCKBlue )
{
  ColorKey = SDL_MapRGB( SpriteSurface->format, GB_SCKRed, GB_SCKGreen, GB_SCKBlue );
  SDL_SetColorKey( SpriteSurface, SDL_SRCCOLORKEY, ColorKey); 
  ColorKeyRed = GB_SCKRed;
  ColorKeyGreen = GB_SCKGreen;
  ColorKeyBlue = GB_SCKBlue;
}

void GB_Sprite::GB_GetColorKey( Uint8 *GB_GCKRed, Uint8 *GB_GCKGreen, Uint8 *GB_GCKBlue )
{
  *GB_GCKRed = ColorKeyRed;
  *GB_GCKGreen = ColorKeyGreen;
  *GB_GCKBlue = ColorKeyBlue;
}

// Constructor to set some initial values

GB_Sprite::GB_Sprite()
{
  Angle = 0;
  RotZoomEnabled = 0;
  ZoomFactor = 1.0;
  SmoothingEnabled = 0;
  Alpha = 255;
  CollWidthFactor = CollHeightFactor = 1.0;
  SpriteX = SpriteY = 0;
}

// Destructor which frees the surface

GB_Sprite::~GB_Sprite()
{
  if( SpriteSurface != NULL ) SDL_FreeSurface( SpriteSurface );
}

// Load a sprite from a file. The second argument ( FrameNr ) tells the
// function how it should divide the bitmap into frames. If you have only
// one frame, pass 1 ( never pass 0! )

void GB_Sprite::GB_LoadSprite( std::string fileName, int HFrameNr /*= 1*/, int VFrameNr /*= 1*/ )
{
  const char* Filename = fileName.c_str();

  if( DEBUGMESSAGELEVEL > 2 ) printf("- Loading the sprite %s\n\r", &Filename[0]);

  if( HFrameNr == 0 || VFrameNr == 0 ) printf("!Error! Never pass 0 as the second or third argument of GB_Sprite::GB_LoadSprite!!!\n" );

  SpriteSurface = IMG_Load(Filename);

  if( SpriteSurface == NULL )
  {
    printf("!Error! Could not load the sprite %s!\n\r", &Filename[0]);
    GB_FreeSurfaces();
    SDL_Quit();
    exit(1);
  }

  Width = SpriteSurface->w;
  Height = SpriteSurface->h;

  VFrames = VFrameNr;
  HFrames = HFrameNr;
  FrameHeight = Height / VFrames;
  FrameWidth = Width / HFrames;
  VFrame=1;
  HFrame=1;

  CollWidth = (int)(FrameWidth * ZoomFactor * CollWidthFactor);
  CollHeight = (int)(FrameHeight * ZoomFactor * CollHeightFactor);
  CollXOffset = (FrameWidth - CollWidth)/2;
  CollYOffset = (FrameHeight - CollHeight)/2;

  if( DEBUGMESSAGELEVEL > 2 ) printf("- Successfully loaded the sprite %s.\n\r", &Filename[0]);
  if( DEBUGMESSAGELEVEL > 2 ) printf("-- Sprite info: width: %d, height: %d, frames: %dx%d, one frame is: %dx%d.\n\n", Width, Height, HFrames, VFrames, FrameHeight, FrameWidth );
}

// Blit one frame of the sprite to the screen
void GB_Sprite::GB_ShowSprite( int HFrameN, int VFrameN )
{
    SDL_Rect to,from;
    SDL_Surface *RotatedSprite;
    SDL_Surface *FrameSurface;
    Uint32 rmask, gmask, bmask, amask;

    if( RotZoomEnabled != 0 )
    {

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
      rmask = 0xff000000;
      gmask = 0x00ff0000;
      bmask = 0x0000ff00;
      amask = 0x000000ff;
    #else
      rmask = 0x000000ff;
      gmask = 0x0000ff00;
      bmask = 0x00ff0000;
      amask = 0xff000000;
    #endif

      from.x = (HFrameN * FrameWidth);
      from.y = (VFrameN * FrameHeight);
      from.w = FrameWidth;
      from.h = FrameHeight;

      FrameSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, FrameWidth,
                                          FrameHeight, 32, rmask, gmask, bmask, amask );
      if( FrameSurface == NULL )
      {
        printf("!Error! Couldn't create a new surface in GB_Sprite::GB_ShowSprite: %s.\n", SDL_GetError());
      }

      if( SDL_BlitSurface( SpriteSurface, &from, FrameSurface, NULL ) < 0 )
      printf("!Error! Blit Surface error: %s.\n", SDL_GetError());

      RotatedSprite = rotozoomSurface( FrameSurface, Angle, ZoomFactor, SmoothingEnabled );

      to.x = SpriteX + (int)((((double)FrameWidth*ZoomFactor) - (double)RotatedSprite->w)/2.0);
      to.y = SpriteX + (int)((((double)FrameHeight*ZoomFactor) - (double)RotatedSprite->h)/2.0);
      to.w = FrameWidth;
      to.h = FrameHeight;

      if( SDL_BlitSurface( RotatedSprite, NULL, Screen, &to) < 0 ) printf( "!Error! Blit Surface error: %s.\n", SDL_GetError() );

      if( RotatedSprite != NULL ) SDL_FreeSurface( RotatedSprite );
      if( FrameSurface != NULL ) SDL_FreeSurface( FrameSurface );
    }
    else
    {

      from.x = (HFrameN * FrameWidth);
      from.y = (VFrameN * FrameHeight);
      from.w = FrameWidth;
      from.h = FrameHeight;

      to.x = SpriteX;
      to.y = SpriteY;
      to.w = FrameWidth;
      to.h = FrameHeight;

      if( SDL_BlitSurface( SpriteSurface, &from, Screen, &to) < 0 ) printf( "!Error! Blit Surface error: %s.\n", SDL_GetError() );
    }
    HFrame=HFrameN;
    VFrame=VFrameN;
}

// Set the alpha value for the surface
void GB_Sprite::GB_SetAlpha( Uint8 GB_SAAlpha )
{
  SDL_SetAlpha( SpriteSurface, SDL_SRCALPHA, GB_SAAlpha );
  Alpha = GB_SAAlpha;
}

// Get the alpha value of the surface
Uint8 GB_Sprite::GB_GetAlpha()
{
  return Alpha;
}

void GB_Sprite::GB_SetRotation( double GBSR_Rotate )
{
  Angle = GBSR_Rotate;

  if( ZoomFactor == 1.0 && Angle == 0 ) GB_DisableRotZoom();
  else GB_EnableRotZoom();
}

double GB_Sprite::GB_GetRotation()
{
  return Angle;
}

void GB_Sprite::GB_EnableRotZoom()
{
  RotZoomEnabled = 1;
}

void GB_Sprite::GB_DisableRotZoom()
{
  RotZoomEnabled = 0;
}

void GB_Sprite::GB_EnableSmoothing()
{
  SmoothingEnabled = SMOOTHING_ON;
}

void GB_Sprite::GB_DisableSmoothing()
{
  SmoothingEnabled = SMOOTHING_OFF;
}

void GB_Sprite::GB_SetZoom( double Zoom )
{
  ZoomFactor = Zoom;

  if( ZoomFactor == 1.0 && Angle == 0 ) GB_DisableRotZoom();
  else GB_EnableRotZoom();

  if( FrameWidth == 0 || FrameHeight == 0 )
  printf("!WARNING! Width or Height was 0 when GB_SetCollBox was called!\nPlease call GB_LoadSprite before SetCollBox!");

  // Update the collision vars
  CollWidth = (int)(FrameWidth * ZoomFactor * CollWidthFactor);
  CollHeight = (int)(FrameHeight * ZoomFactor * CollHeightFactor);
  CollXOffset = ((int)(FrameWidth * ZoomFactor) - CollWidth)/2;
  CollYOffset = ((int)(FrameHeight * ZoomFactor) - CollHeight)/2;
}

double GB_Sprite::GB_GetZoom()
{
  return ZoomFactor;
}

void GB_Sprite::GB_SetCollBox( float WidthFactor, float HeightFactor )
{

  if( FrameWidth == 0 || FrameHeight == 0 )
  printf("!WARNING! Width or Height was 0 when GB_SetCollBox was called!\nPlease call GB_LoadSprite before SetCollBox!");

  CollWidthFactor = WidthFactor;
  CollHeightFactor = HeightFactor;

  // Update the collision vars
  CollWidth = (int)(FrameWidth * ZoomFactor * CollWidthFactor);
  CollHeight = (int)(FrameHeight * ZoomFactor * CollHeightFactor);
  CollXOffset = ((int)(FrameWidth * ZoomFactor) - CollWidth)/2;
  CollYOffset = ((int)(FrameHeight * ZoomFactor) - CollHeight)/2;
}

void GB_Sprite::GB_SetXY( int XPos, int YPos )
{
  SpriteX = XPos;
  SpriteY = YPos;
}

int GB_Sprite::GB_GetX()
{
  return SpriteX;
}

int GB_Sprite::GB_GetY()
{
  return SpriteY;
}

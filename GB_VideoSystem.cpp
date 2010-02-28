/***************************************************************************
                          GB_VideoSystem.cpp
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:31:27 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_VideoSystem.cpp,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GameBlade.h"
#include <cstdlib>

SDL_Surface *Screen;
SDL_Surface *GFXText;
int ScreenLocked = 0; 

// Set the video mode according to the values in the Definitions.h header
void GB_SetupSDL_Video()
{
  if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
  {
    printf("! SDL error: %s. \n", SDL_GetError() );
    SDL_Quit();
    exit( -1 );
  }

  Screen = SDL_SetVideoMode( RESX, RESY, 24, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF | (FULLSCREEN?SDL_FULLSCREEN:0) );

  if( Screen == NULL )
  {
    fprintf( stderr, "! SDL error with Screen surface: %s.\n", SDL_GetError() );
    printf("!Error! Cannot continue without video output.\n\n");
    SDL_Quit();
    exit(1);
  }

  SDL_WM_SetCaption( GAMEBUILD, NULL );

    if( DEBUGMESSAGELEVEL > 1 ) printf("- SDL initialized: %dx%dx%dbpp, %s\n\n", RESX, RESY, Screen->format->BitsPerPixel, FULLSCREEN?"Fullscreen":"Windowed");
}

// Free the surfaces if you are not using them anymore
void GB_FreeSurfaces()
{
  if( GFXText != NULL ) SDL_FreeSurface( GFXText );
}

// Hide the cursor to get rid of annoying blinking behaviour
void GB_HideMouseCursor()
{
  SDL_ShowCursor( SDL_DISABLE );
}

// Hide the cursor to get rid of annoying blinking behaviour
void GB_ShowMouseCursor()
{
  SDL_ShowCursor( SDL_ENABLE );
}

// Function for locking the screen. Please call this before you use GB_DrawPixel!!!
void GB_LockScreen()
{
   if ( SDL_MUSTLOCK(Screen) )
   {
     if ( SDL_LockSurface(Screen) < 0 )
     {
       fprintf(stderr, "!ERROR! Can't lock screen: %s\n", SDL_GetError());
     }
     else ScreenLocked = 1;
   }
   else ScreenLocked = 1;
}

// Call this after you finished the use of GB_DrawPixel!!!
void GB_UnlockScreen()
{
  if ( SDL_MUSTLOCK( Screen ) )
  {
    SDL_UnlockSurface( Screen );
    ScreenLocked = 0;
  }
}

// Draws a pixel on the screen at coordinates x, y with the RGB value r, g, b
// Most code was taken from the SDL documents
void GB_DrawPixel( int GB_DPx, int GB_DPy, Uint8 GB_DPr, Uint8 GB_DPg, Uint8 GB_DPb )
{

  if( ScreenLocked == 0 )
  {
    printf("!ERROR! Please lock the screen before using GB_DrawPixel!!!\n");
    GB_LockScreen();
  }

  Uint32 GB_DPpixel = SDL_MapRGB( Screen->format, GB_DPr, GB_DPg, GB_DPb );

  int GB_DPbpp = Screen->format->BytesPerPixel;
  Uint8 *GB_DPp = (Uint8 *)Screen->pixels + GB_DPy * Screen->pitch + GB_DPx * GB_DPbpp;

  switch(GB_DPbpp)
  {
     case 1:
         *GB_DPp = GB_DPpixel;
         break;

     case 2:
         *(Uint16 *)GB_DPp = GB_DPpixel;
         break;

     case 3:
         if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
         {
             GB_DPp[0] = (GB_DPpixel >> 16) & 0xff;
             GB_DPp[1] = (GB_DPpixel >> 8) & 0xff;
             GB_DPp[2] = GB_DPpixel & 0xff;
         }
         else
         {
             GB_DPp[0] = GB_DPpixel & 0xff;
             GB_DPp[1] = (GB_DPpixel >> 8) & 0xff;
             GB_DPp[2] = (GB_DPpixel >> 16) & 0xff;
         }
         break;

     case 4:
         *(Uint32 *)GB_DPp = GB_DPpixel;
         break;
  }
}

// Function to get the RGB components of a pixel of the screen surface
// Lock the screen first!!!
// The biggest part of the code was taken from the SDL docs
void GB_GetPixel( int GB_GPx, int GB_GPy, Uint8 *GB_GPr, Uint8 *GB_GPg, Uint8 *GB_GPb )
{
  if( ScreenLocked == 0 )
  {
    printf("!ERROR! Please lock the screen before using GB_DrawPixel!!!\n");
    GB_LockScreen();
  }

  Uint32 GB_GPpixel;

  int GB_GPbpp = Screen->format->BytesPerPixel;
  Uint8 *GB_GPp = (Uint8 *)Screen->pixels + GB_GPy * Screen->pitch + GB_GPx * GB_GPbpp;

  switch(GB_GPbpp)
  {
    case 1:
        GB_GPpixel = *GB_GPp;
	break;

    case 2:
        GB_GPpixel = *(Uint16 *)GB_GPp;
	break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            GB_GPpixel = GB_GPp[0] << 16 | GB_GPp[1] << 8 | GB_GPp[2];
        else
            GB_GPpixel = GB_GPp[0] | GB_GPp[1] << 8 | GB_GPp[2] << 16;
	break;

    case 4:
        GB_GPpixel = *(Uint32 *)GB_GPp;
	break;

    default:
        GB_GPpixel = 0;       /* shouldn't happen, but avoids warnings */
  }

  SDL_GetRGB( GB_GPpixel, Screen->format, GB_GPr, GB_GPg, GB_GPb );
}

// Fill the whole screen with a specific color
void GB_FillScreen( Uint8 GB_CSr, Uint8 GB_CSg, Uint8 GB_CSb )
{
  SDL_FillRect( Screen, NULL, SDL_MapRGB( Screen->format, GB_CSr, GB_CSg, GB_CSb ));
}

// Clear the screen ( fill with the color black )
void GB_ClearScreen()
{
  SDL_FillRect( Screen, NULL, SDL_MapRGB( Screen->format, 0, 0, 0 ));
}

void GB_FillScreenRect( int GB_FSR_x, int GB_FSR_y, int GB_FSR_w, int GB_FSR_h,
                        Uint8 GB_FSR_r, Uint8 GB_FSR_g, Uint8 GB_FSR_b )
{
  SDL_Rect GB_FSR_Rect;

  GB_FSR_Rect.x = GB_FSR_x;
  GB_FSR_Rect.y = GB_FSR_y;
  GB_FSR_Rect.w = GB_FSR_w;
  GB_FSR_Rect.h = GB_FSR_h;

  SDL_FillRect( Screen, &GB_FSR_Rect, SDL_MapRGB( Screen->format,
                GB_FSR_r, GB_FSR_g, GB_FSR_b ));
}

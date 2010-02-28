/***************************************************************************
 GB_Backgrounds.cpp  -  Header with functions and classes for handling fullscreen images.
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/15 20:36:23 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.2 $
    filename             : $RCSfile: GB_Backgrounds.cpp,v $

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

// The class background provides a clean interface eleminating the need of taking
// care for freeing surfaces, loading bitmaps etc.

GB_Background::~GB_Background()
{
  if( BackgroundSurface != NULL ) SDL_FreeSurface( BackgroundSurface );
}

void GB_Background::GB_LoadBackground( char *Filename )
{

  if( DEBUGMESSAGELEVEL > 2 ) printf("- Loading the background %s\n\r", &Filename[0]);

  BackgroundSurface = IMG_Load(Filename);

  if( BackgroundSurface == NULL )
  {
    printf("!Error! Could not load the background %s!\n\r", &Filename[0]);
    GB_FreeSurfaces();
    SDL_Quit();
    exit(1);
  }

  if( DEBUGMESSAGELEVEL > 2 ) printf("- Successfully loaded the background %s.\n\r", &Filename[0]);
  if( DEBUGMESSAGELEVEL > 2 ) printf("-- Background info: width: %d, height: %d.\n\n", BackgroundSurface->w, BackgroundSurface->h );

}

void GB_Background::GB_ShowBackground()
{
    if( SDL_BlitSurface( BackgroundSurface, NULL, Screen, NULL ) < 0 ) printf( "!Error! Blit Surface error: %s.\n", SDL_GetError() );
}

void GB_Background::GB_SetAlpha( Uint8 GB_SAAlpha )
{
  SDL_SetAlpha( BackgroundSurface, SDL_SRCALPHA, GB_SAAlpha );
  Alpha = GB_SAAlpha;
}

Uint8 GB_Background::GB_GetAlpha()
{
  return Alpha;
}

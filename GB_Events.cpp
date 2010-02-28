/***************************************************************************
 GB_Events.cpp  -  Put your event filtering routines into this file
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 17:04:01 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.4 $
    filename             : $RCSfile: GB_Events.cpp,v $

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

int GB_Events::GB_Keys[SDLK_LAST+1];
int GB_Events::GB_QuitEvent = 0;

void GB_Events::GB_ResetKeys()
{
  for( int i = 0; i < SDLK_LAST+1; i++ ) GB_Keys[i] = 0;
}

void GB_Events::GB_FilterEvents()
{
  SDL_Event event;

  for( int i = 0; i < SDLK_LAST+1; i++ )
    if( GB_Keys[i] != 0 ) GB_Keys[i]++;

  while( SDL_PollEvent( &event ) )
  {
    switch( event.type )
    {
      case SDL_QUIT:
        GB_QuitEvent = 1;
        break;

      case SDL_KEYDOWN:
        GB_Keys[event.key.keysym.sym] = 1;
	break;

      case SDL_KEYUP:
        GB_Keys[event.key.keysym.sym] = 0;
        break;

      default:
        break;
    }
  }
}

int GB_Events::GB_CheckKey( int KeyNumber )
{
  return GB_Keys[KeyNumber];
}

int GB_Events::GB_CheckQuitEvent()
{
 return GB_QuitEvent;
}

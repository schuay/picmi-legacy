/***************************************************************************
                          GB_System.cpp  -  description
                             -------------------
    begin                : Sun Oct 13 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/20 17:39:58 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.9 $
    filename             : $RCSfile: GB_System.cpp,v $

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


// Please use this function to quit the GameBlade and all components of SDL
void GB_System::Quit()
{
   GB_FreeSurfaces();
   SDL_Quit();
}

void GB_System::Init( int ResX, int ResY )
{
   GB_SetupSDL_Video(ResX, ResY);

   SDL_EnableUNICODE(1);
   SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}




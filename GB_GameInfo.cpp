/***************************************************************************
   GB_GameInfo.cpp  -  Print info about the game on start and quit
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/15 20:36:25 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.2 $
    filename             : $RCSfile: GB_GameInfo.cpp,v $

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

// Print info about your game when it starts and when it quits.
// This is always nice for the user.

void GB_PrintGameInfo()
{
  if( DEBUGMESSAGELEVEL > 0 ) printf("\n%s\n\n", GAMEBUILD );
}

void GB_PrintGameQuitInfo()
{
  if( DEBUGMESSAGELEVEL > 0 ) printf( "- Successfully quit. Thank you for playing!\n" );
}


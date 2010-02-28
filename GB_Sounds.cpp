/***************************************************************************
        GB_Sounds.cpp  -  Class for loading and playing sounds
                             -------------------
    begin                : Oct 4 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/15 20:36:27 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.2 $
    filename             : $RCSfile: GB_Sounds.cpp,v $

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

// Constructor

GB_Sound::GB_Sound()
{
  SoundChannel = -1;
}

// Load the sound from a file

void GB_Sound::GB_LoadSound( char *Filename )
{
  if( AudioEnabled == 1 )
  {
    SoundChunk = Mix_LoadWAV( Filename );
    if( SoundChunk == NULL ) printf("!Error! Unable to load the sound file %s!\n", &Filename[0] );
  }
}

// Play the sound one time

void GB_Sound::GB_PlaySound()
{
  if( AudioEnabled == 1 && SoundChunk != NULL )
  {
     SoundChannel = Mix_PlayChannel( -1, SoundChunk, 0 );
  }
}

// Loop the sound until it is stopped with GB_Sound::GB_StopSound()

void GB_Sound::GB_LoopSound()
{
  if( AudioEnabled == 1 && SoundChunk != NULL )
  {
     SoundChannel = Mix_PlayChannel( -1, SoundChunk, -1 );
  }
}

// Stop a sound which is being played. Use only if you know that the sound is still playing!

void GB_Sound::GB_StopSound()
{
  if( AudioEnabled == 1 && SoundChunk != NULL && SoundChannel != -1 )
  {
     Mix_HaltChannel( SoundChannel );
     SoundChannel = -1;
  }
}


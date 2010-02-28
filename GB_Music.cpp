/***************************************************************************
                      GB_Music.cpp  -  description
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/19 07:41:45 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_Music.cpp,v $

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

Mix_Music *GB_Music::BackgroundMusic = NULL;
bool GB_Music::GB_MusicIsFinished = true;


bool GB_Music::GB_MusicFinished_()
{
  return GB_MusicIsFinished;
}

// Stop the background music and free the music. Note, this is not "pause", but stop!
void GB_Music::GB_StopMusic_()
{
  if( BackgroundMusic != NULL && AudioEnabled == 1 )
  {
    Mix_HaltMusic();
    Mix_FreeMusic(BackgroundMusic);
    BackgroundMusic = NULL;
  }
}

// Function called if a song is finished. Put in functions which choose a next song or
// whatever you like. The default is: Stop the song.
void GB_Music::GB_MusicDone_()
{
  GB_StopMusic_();

}

// Load a song and play it. Set repetition to -1 if you want an infinite loop
// of this song ( note: GB_MusicDone will not be called ), use 0 if you
// want the song to be played one time

void GB_Music::GB_PlayMusic_( char *Filename, int Repetition )
{
  if( BackgroundMusic == NULL && AudioEnabled == 1)
  {

    BackgroundMusic = Mix_LoadMUS( Filename );

    if( BackgroundMusic == 0 ) printf("!Error! Couldn't load the music %s!\n", Filename );

    if( BackgroundMusic != NULL )
    {
      Mix_PlayMusic( BackgroundMusic, Repetition );
      Mix_HookMusicFinished( GB_MusicDone_ );
    }

  }
}




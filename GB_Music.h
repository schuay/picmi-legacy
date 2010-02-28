/***************************************************************************
                      GB_Music.h  -  description
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/19 07:41:45 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.4 $
    filename             : $RCSfile: GB_Music.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_MUSIC_H_
#define _GB_MUSIC_H_

class GB_Music
{
  private:
  static Mix_Music *BackgroundMusic;
  static bool GB_MusicIsFinished;

  // Function called if a song is finished. Put in functions which choose a next song or
  // whatever you like. The default is: Stop the song.
  static void GB_MusicDone_();

  public:
  // Stop the background music and free the music. Note, this is not "pause", but stop!
  static void GB_StopMusic_();

  // Load a song and play it. Set repetition to -1 if you want an infinite loop
  // of this song ( note: GB_MusicDone will not be called ), use 0 if you
  // want the song to be played one time
  static void GB_PlayMusic_( char *Filename, int Repetition );

  static bool GB_MusicFinished_();
};

#define GB_MusicFinished() GB_Music::GB_MusicFinished_()
#define GB_StopMusic() GB_Music::GB_StopMusic_()
#define GB_PlayMusic(A,B) GB_Music::GB_PlayMusic_(A,B)

#endif

/***************************************************************************
        GB_Sounds.h  -  Class for loading and playing sounds
                             -------------------
    begin                : Oct 4 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:25:38 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_Sounds.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_SOUNDS_H_
#define _GB_SOUNDS_H_

// Class for Playing and loading sounds

class GB_Sound
{
  private:
    Mix_Chunk *SoundChunk;
    int SoundChannel;

  public:
    GB_Sound();
    void GB_LoadSound( char * );
    void GB_PlaySound();
    void GB_LoopSound();
    void GB_StopSound();

};

#endif


/***************************************************************************
 GB_AudioSystem.cpp  -  Functions for opening and closing the audio device
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/15 20:36:22 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.2 $
    filename             : $RCSfile: GB_AudioSystem.cpp,v $

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

int AudioEnabled = 0;

// Setup the sound system using the values from the Definitions.h header. Also setup the mixer of SDL_mixer

void GB_SetupSDL_Audio()
{
  SDL_Init( SDL_INIT_AUDIO );

  if( Mix_OpenAudio( AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS ) )
  {
    printf("!Warning! Unable to open audio: %s \n-- Going to continue without audio output.\n\n", SDL_GetError() );
    AudioEnabled = 0;
  }
  else
  {
    AudioEnabled = 1;
    printf("- Successfully initialized the audio device.\n\n");
  }
}

// Close the mixer and the Sound subsystem of SDL

void GB_CloseMixer()
{
  if( AudioEnabled == 1 ) Mix_CloseAudio();
  if( AudioEnabled == 1 ) SDL_QuitSubSystem( SDL_INIT_AUDIO );
  AudioEnabled = 0;
}

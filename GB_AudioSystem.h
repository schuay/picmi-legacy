/***************************************************************************
 GB_AudioSystem.h  -  Functions for opening and closing the audio device
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:25:38 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_AudioSystem.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_AUDIOSYSTEM_H_
#define _GB_AUDIOSYSTEM_H_

// Setup the sound system using the values from the Definitions.h header. Also setup the mixer of SDL_mixer

void GB_SetupSDL_Audio();

// Close the mixer and the Sound subsystem of SDL

void GB_CloseMixer();

#endif

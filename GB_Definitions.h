/***************************************************************************
         GB_Definitions.h  -  Use this file for #define's
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 17:04:01 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.4 $
    filename             : $RCSfile: GB_Definitions.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_DEFINITIONS_H_
#define _GB_DEFINITIONS_H_

// Identify your game and build

#define GAMEBUILD "Tux Picross v.0.1"

// Definitions used for audio output

#define AUDIO_RATE 44100         // Change this to a lower number, for example 32000 if you don't need this quality
#define AUDIO_FORMAT AUDIO_S16    /* 16-bit stereo */
#define AUDIO_CHANNELS 2       // Stereo
#define AUDIO_BUFFERS 4096    // Change this to a lower number if you want lower latency

// Resolution of the game/application and whether it runs in fullscreen mode or not

#define RESX 320     // Horizontal resolution
#define RESY 290       // Vertical resolution
#define FULLSCREEN 0  // 1 for FULLSCREEN, 0 for WINDOWED

// Value which tells the compiler about how much info it should ouput about the execution of the game
// Add your own levels if you like

#define DEBUGMESSAGELEVEL 3
// LEVEL 0: No message output to console, exceptions are errors and warnings
// LEVEL 1: Start and end messages + errors and warnings
// LEVEL 2: Level 1 + Video and Soundsystem messages
// LEVEL 3: All messages

#define GB_INIT_VIDEO 1
#define GB_INIT_VIDEO_AND_AUDIO 2

#endif

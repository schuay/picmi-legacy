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

// Initialize and allocate mem for the static class variables.
float GB_System::FPSDelay = 0;
Uint32 GB_System::NextTime =0;
int GB_System::LostFrames = 0;
Uint32 GB_System::LastTime = 0;
int GB_System::FPS = 30;

float GB_System::getRealFrameRate()
{
  return (float)FPS/getLostFrames();
}

int GB_System::getFrameRate()
{
  return FPS;
}

// Please use this function to quit the GameBlade and all components of SDL
void GB_System::Quit()
{
   if( AudioEnabled == 1 )
   {
     GB_CloseMixer();
   }

   GB_FreeSurfaces();
   SDL_Quit();
}

void GB_System::Init( int InitSystems, int ResX, int ResY )
{
   GB_SetupSDL_Video(ResX, ResY);
   setFrameRate(30);
   if( InitSystems == GB_INIT_VIDEO_AND_AUDIO ) GB_SetupSDL_Audio();

   SDL_EnableUNICODE(1);
   SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

void GB_System::setFrameRate( int SetFPS )
{
   // Ideally, if we need for example, 30 FPS, we need to wait
   // 1000/30~=33 milisecons between each frame.
   FPSDelay = 1000.0 / (float)SetFPS;
   NextTime = SDL_GetTicks() + (Uint32)FPSDelay;
   LastTime = SDL_GetTicks();
   FPS = SetFPS;
}

void GB_System::WaitFrame()
{
   // Optimized for speed. Not thread safe, warning!
   static long Diff;

   Diff = NextTime - SDL_GetTicks();

//   Wait = FPSDelay + Diff;

   if ( Diff > 0)
   {
      // I'm too fast, wait...
   //   SDL_Delay( Diff );
   //   LostFrames = 0;
   }
   else
   {
      // I'm not enough fast, hurry up! :)
      //if (Wait>0)
      //SDL_Delay(Diff + FPSDelay);
      //LostFrames = (-Diff)/FPSDelay;
   }

   NextTime += (int)FPSDelay;
   LastTime = SDL_GetTicks();
}

float GB_System::getLostFrames()
{
   return ((float)(SDL_GetTicks()-LastTime)/FPSDelay) + 1.0;
}




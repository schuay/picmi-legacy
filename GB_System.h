/***************************************************************************
                          GB_System.h  -  description
                             -------------------
    begin                : Sun Oct 13 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/20 17:18:32 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.7 $
    filename             : $RCSfile: GB_System.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_SYSTEM_H_
#define _GB_SYSTEM_H_

class GB_System
{
 public:
   static void Quit();
   static void Init( int, int ResX = RESX, int ResY = RESY );
   
   // Set the desired frame rate for the game
   static void setFrameRate(int FPS);
   static int getFrameRate();
   
   static float getRealFrameRate();

   // Waits the needed time to reach the FPS settled with setFrameRate()
   static void WaitFrame();

   // Gets the number of lost frames in the last call to WaitFrame
   static float getLostFrames();

 private:
   static float FPSDelay;
   static Uint32 NextTime;
   static int LostFrames;
   static Uint32 LastTime;
   static int FPS;
};

// For ease of use
#define GB_Quit() GB_System::Quit()
#define GB_Init(A,B,C) GB_System::Init(A,B,C)
#define GB_SetFrameRate(A) GB_System::setFrameRate(A)
#define GB_WaitFrame() GB_System::WaitFrame()
#define GB_LostFrames() GB_System::getLostFrames()
#define GB_GetCurrentFPS() GB_System::getRealFrameRate()

#endif

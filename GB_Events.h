/***************************************************************************
 GB_Events.h  -  Filter events like Keys, Mouse and other signals
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 17:04:01 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_Events.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_EVENTS_H_
#define _GB_EVENTS_H_

class GB_Events
{
  private:

  static int GB_Keys[SDLK_LAST+1];

  static int GB_QuitEvent;

  public:

  GB_Events();
  ~GB_Events();

   // Detect collision between two sprites or boxes.
   static void GB_FilterEvents();

   static int GB_CheckKey( int );
   static int GB_CheckQuitEvent();
   
   static void GB_ResetKeys();
};

#define GB_GetEvents() GB_Events::GB_FilterEvents()
#define GB_GetKey(X) GB_Events::GB_CheckKey(X)
#define GB_QuitEvent() GB_Events::GB_CheckQuitEvent()

#endif

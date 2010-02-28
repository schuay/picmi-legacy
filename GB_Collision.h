/***************************************************************************
        GB_Collision.h  -  Class for detecting collisions into sprites
                             -------------------
    begin                : Wed Oct 15 2002
    copyright            : (C) 2002 by Pedro Pablo Esteve
    email                : nimgil@grupo-neo.com
    last change          : $Date: 2002/10/18 08:16:48 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.7 $
    filename             : $RCSfile: GB_Collision.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// This class is for detection of collisions between sprites.
// This clas is mainly a static set of funtions, it doesn't need
// to be instantiated in any manner.

#ifndef _GB_COLLISION_H_
#define _GB_COLLISION_H_

#include "GameBlade.h"

// Types of collision algorithms
enum collision_type { BOX, PERFECT };

class GB_Sprite;

class GB_Collision
{
  public:

   GB_Collision();
   ~GB_Collision();

   // Detect collision between two sprites or boxes.
   static int Collide( GB_Sprite *Sprite1, GB_Sprite *Sprite2, int CDAlgorythm = BOX );
};

// Macro for ease of use
#define GB_Collide(A, B, C) GB_Collision::Collide(A, B, C)

#endif

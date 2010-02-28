/***************************************************************************
        GB_Collision.h  -  Class for detecting collisions into sprites
                             -------------------
    begin                : Wed Oct 15 2002
    copyright            : (C) 2002 by Pedro Pablo Esteve
    email                : nimgil@grupo-neo.com
    last change          : $Date: 2002/10/22 16:41:00 $
    last change by       : $Author: nimgil $
    revision nr.         : $Revision: 1.14 $
    filename             : $RCSfile: GB_Collision.cpp,v $

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

#include "GB_Collision.h"

// Construtor and Destructor.
// Not needed but defined anyway for anyone who wants to
// instantiate the class.
GB_Collision::GB_Collision(){ };
GB_Collision::~GB_Collision() { };

// Detect collision between two sprites or boxes.
int GB_Collision::Collide( GB_Sprite *Sprite1, GB_Sprite *Sprite2, int
		CDAlgorythm /*= BOX*/ )
{
   if (( Sprite1 == NULL) || ( Sprite2 == NULL))
   {
     // Nothing never collides with nothing... :)
     printf("!WARNING! One of the sprites passed as argument to GB_Collision::Collide was NULL!\n");
     return(0);
   }

   if ( CDAlgorythm == BOX )
   {
       // Best for balance performance/realism.
       // Assumes that a percentage of the box surrounding the sprite
       // is the actual sprite.

       // See if the reduced sprites collide.
       if ( (Sprite1->SpriteX + Sprite1->CollWidth + Sprite1->CollXOffset) <
	    (Sprite2->SpriteX + Sprite2->CollXOffset) ) return 0;

       if ( (Sprite2->SpriteX + Sprite2->CollWidth + Sprite2->CollXOffset) <
	    (Sprite1->SpriteX + Sprite1->CollXOffset) ) return 0;

       if ( (Sprite1->SpriteY + Sprite1->CollHeight + Sprite1->CollYOffset) <
	    (Sprite2->SpriteY + Sprite2->CollYOffset) ) return 0;

       if ( (Sprite2->SpriteY + Sprite2->CollHeight + Sprite2->CollYOffset) <
	    (Sprite1->SpriteY + Sprite1->CollYOffset) ) return 0;

       return(1);
   }
   
   if( CDAlgorythm == PERFECT )
   {
     // First of all, we reject non-colliding BOXES.
     if ( (Sprite1->SpriteX + Sprite1->FrameWidth)  < Sprite2->SpriteX) return 0;
     if ( (Sprite2->SpriteX + Sprite2->FrameWidth)  < Sprite1->SpriteX) return 0;
     if ( (Sprite1->SpriteY + Sprite1->FrameHeight) < Sprite2->SpriteY) return 0;
     if ( (Sprite2->SpriteY + Sprite2->FrameHeight) < Sprite1->SpriteY) return 0;

     // So there is a portion of the sprites that intersect. Let's calculate
     // it and see if them really collide.
     int Sp1XOffset,Sp2XOffset, Sp1YOffset, Sp2YOffset;
     int BoxWidth, BoxHeight;
     if ( Sprite1->SpriteX < Sprite2->SpriteX )
     {	 
	Sp1XOffset=Sprite2->SpriteX-Sprite1->SpriteX;
	Sp2XOffset=0;
	BoxWidth= Sprite1->SpriteX + Sprite1->FrameWidth - Sprite2->SpriteX;
     }
     else 
     {	 
	Sp2XOffset=Sprite1->SpriteX-Sprite2->SpriteX;
	Sp1XOffset=0;
	BoxWidth= Sprite2->SpriteX + Sprite2->FrameWidth - Sprite1->SpriteX;
     }      
      
     if ( Sprite1->SpriteY < Sprite2->SpriteY )
     {	 
	Sp1YOffset=Sprite2->SpriteY-Sprite1->SpriteY;
	Sp2YOffset=0;
	BoxHeight=Sprite1->SpriteY + Sprite1->FrameHeight - Sprite2->SpriteY;
     }
     else
     {	 
	Sp2YOffset=Sprite1->SpriteY-Sprite2->SpriteY;
	Sp1YOffset=0;
	BoxHeight=Sprite2->SpriteY + Sprite2->FrameHeight - Sprite1->SpriteY;
     }
	
     int FrameHeight1, FrameWidth1;
     int FrameHeight2, FrameWidth2;
     FrameHeight1= Sprite1->Height/Sprite1->VFrames; 
     FrameHeight2= Sprite2->Height/Sprite2->VFrames; 
     FrameWidth1= Sprite1->Width/Sprite2->HFrames; 
     FrameWidth2= Sprite2->Width/Sprite2->HFrames; 
     // Now we need to compute the offsets of the sprites where 
     // the overlapped box is.
     Uint8* s1= (Uint8*)Sprite1->SpriteSurface->pixels + 
      (Sprite1->HFrame * FrameWidth1 + Sp1XOffset) * Sprite1->SpriteSurface->format->BytesPerPixel +
      (Sprite1->VFrame * FrameHeight1 + Sp1YOffset) * Sprite1->SpriteSurface->pitch;

     Uint8* s2= (Uint8*)Sprite2->SpriteSurface->pixels + 
      (Sprite2->HFrame * Sprite2->FrameWidth + Sp2XOffset) * Sprite2->SpriteSurface->format->BytesPerPixel +
      (Sprite2->VFrame * Sprite2->FrameHeight + Sp2YOffset) * Sprite2->SpriteSurface->pitch;
     
     int i,j;
     switch ( Sprite1->SpriteSurface->format->BytesPerPixel)
     {
      case 1:
	for (i=1; i<=BoxHeight; i++)
	{
	  for (j=1; j<=BoxWidth; j++)
	  {
	     if ((*s1 != Sprite1->ColorKey) && (*s2 != Sprite2->ColorKey))
	       return 1;
	     s1++; s2++;
	  }
          s1= (Uint8*)Sprite1->SpriteSurface->pixels + 
              (Sprite1->HFrame * FrameWidth1 + Sp1XOffset) +
	      (Sprite1->VFrame * FrameHeight1 + Sp1YOffset + i ) * 
	       Sprite1->SpriteSurface->pitch;
          s2= (Uint8*)Sprite2->SpriteSurface->pixels + 
              (Sprite2->HFrame * FrameWidth2 + Sp2XOffset) +
	      (Sprite2->VFrame * FrameHeight2 + Sp2YOffset + i ) * 
	       Sprite2->SpriteSurface->pitch;
	}	
	break;
      case 2:
	for (i=1; i<=BoxHeight; i++)
	{
	  for (j=1; j<=BoxWidth; j++)
	  {
	     if ((*(Uint16 *)s1 != Sprite1->ColorKey) && 
		 (*(Uint16 *)s2 != Sprite2->ColorKey))
	       return 1;
	     s1+=2; s2+=2;
	  }
          s1= (Uint8*)Sprite1->SpriteSurface->pixels + 
              (Sprite1->HFrame * FrameWidth1 + Sp1XOffset) * 2 +
	      (Sprite1->VFrame * FrameHeight1 + Sp1YOffset + i ) * 
	       Sprite1->SpriteSurface->pitch;
          s2= (Uint8*)Sprite2->SpriteSurface->pixels + 
              (Sprite2->HFrame * FrameWidth2 + Sp2XOffset) * 2 +
	      (Sprite2->VFrame * FrameHeight2 + Sp2YOffset + i ) * 
	       Sprite2->SpriteSurface->pitch;
	}	
	break;
      case 3:
	for (i=1; i<=BoxHeight; i++)
	{
	  for (j=1; j<=BoxWidth; j++)
	  {
	     if ((*(Uint16 *)s1 != Sprite1->ColorKey) && 
		 (*(Uint16 *)s2 != Sprite2->ColorKey))
	       return 1;
	     s1+=3; s2+=3;
	  }
          s1= (Uint8*)Sprite1->SpriteSurface->pixels + 
              (Sprite1->HFrame * FrameWidth1 + Sp1XOffset) * 3 +
	      (Sprite1->VFrame * FrameHeight1 + Sp1YOffset + i ) * 
	       Sprite1->SpriteSurface->pitch;
          s2= (Uint8*)Sprite2->SpriteSurface->pixels + 
              (Sprite2->HFrame * FrameWidth2 + Sp2XOffset) * 3 +
	      (Sprite2->VFrame * FrameHeight2 + Sp2YOffset + i ) * 
	       Sprite2->SpriteSurface->pitch;
	}	
	break;
      case 4:
	for (i=1; i<=BoxHeight; i++)
	{
	  for (j=1; j<=BoxWidth; j++)
	  {
	     if ((*(Uint32 *)s1 != Sprite1->ColorKey) && 
		 (*(Uint32 *)s2 != Sprite2->ColorKey))
	       return 1;
	     s1+=4; s2+=4;
	  }
          s1= (Uint8*)Sprite1->SpriteSurface->pixels + 
              (Sprite1->HFrame * FrameWidth1 + Sp1XOffset) * 4 +
	      (Sprite1->VFrame * FrameHeight1 + Sp1YOffset + i ) * 
	       Sprite1->SpriteSurface->pitch;
          s2= (Uint8*)Sprite2->SpriteSurface->pixels + 
              (Sprite2->HFrame * FrameWidth2 + Sp2XOffset) * 4 +
	      (Sprite2->VFrame * FrameHeight2 + Sp2YOffset + i ) *
	       Sprite2->SpriteSurface->pitch;
	}	
	break;
     }
      
     return 0;
   }

   return 0;
};

/***************************************************************************
 GB_Backgrounds.h  -  Header with functions and classes for handling fullscreen images.
                             -------------------
    begin                : Thu Oct 3 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/18 08:25:38 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.3 $
    filename             : $RCSfile: GB_Backgrounds.h,v $

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _GB_BACKGROUNDS_H_
#define _GB_BACKGROUNDS_H_

// The class background provides a clean interface eleminating the need of taking
// care for freeing surfaces, loading bitmaps etc.

class GB_Background
{
  private:
    SDL_Surface *BackgroundSurface;     // The surface the bitmap is copied to after loading it
    Uint8 Alpha;
  public:
    ~GB_Background();
    void GB_LoadBackground( char * );
    void GB_ShowBackground();
    void GB_SetAlpha( Uint8 );
    Uint8 GB_GetAlpha();
};

#endif


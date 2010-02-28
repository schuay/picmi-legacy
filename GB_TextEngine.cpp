/***************************************************************************
                    GB_TextEngine.cpp  -  description
                             -------------------
    begin                :  Oct 5 2002
    copyright            : (C) 2002 by Jarek Ilski
    email                : Nokturn32@poczta.onet.pl
    last change          : $Date: 2002/10/15 20:36:28 $
    last change by       : $Author: nokturn $
    revision nr.         : $Revision: 1.2 $
    filename             : $RCSfile: GB_TextEngine.cpp,v $

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
#include <cstdlib>
#include <cstring>

// Load the standard font. Call this before drawing anything to the screen

void GB_LoadTextBitmap()
{
  if( DEBUGMESSAGELEVEL > 2 ) printf("- Loading the text bitmap (GFXText).\n\r");

  GFXText = SDL_LoadBMP("gfx/8x8font.bmp");

  if( GFXText == NULL )
  {
    printf("! Error with loading surface GFXText: Graphics/Text.bmp cannot be loaded.");
    GB_FreeSurfaces();
    SDL_Quit();
    exit(1);
  }

  SDL_SetColorKey(GFXText, SDL_SRCCOLORKEY, SDL_MapRGB( GFXText->format, 0, 0, 0 ) );

  if( DEBUGMESSAGELEVEL > 2 ) printf("- Successfully loaded the text bitmap (GFXText).\n\r");
}

// Draw one single character to the screen

void GB_DrawCharacter( int Character, int X, int Y )
{
  SDL_Rect to,from;

  if( GFXText == NULL ) printf("!Error! Call GB_LoadTextBitmap before drawing characters!\n" );

  to.x = X;
  to.y = Y;
  to.w = 16;
  to.h = 16;

  from.x = (Character % 16) * 16;
  from.y = (Character / 16) * 16;
  from.h = 16;
  from.w = 16;

  if( SDL_BlitSurface(GFXText, &from, Screen, &to) < 0 ) printf( "! Blit Surface error: %s.\n", SDL_GetError() );
}

// Draw a string to the screen at the coordinates WXStart and WYStart

void GB_DrawText( char *TextToDraw, int WXStart, int WYStart )
{

  int GB_DTX, GB_DTCharacter;

  GB_DTX = 0;

  for( unsigned int i = 0; i < strlen(TextToDraw); i++ )
  {
    GB_DTCharacter = TextToDraw[i];

    if( GB_DTCharacter == '?' ) GB_DTCharacter = 196;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 228;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 214;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 246;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 220;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 252;
    if( GB_DTCharacter == '?' ) GB_DTCharacter = 223;

    GB_DrawCharacter( GB_DTCharacter, ((GB_DTX*10)+WXStart), WYStart );
    GB_DTX++;
  }
}

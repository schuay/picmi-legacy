/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Puzzle.h"

Puzzle::Puzzle(unsigned int w, unsigned int h, std::string map)
{
    Width = w;
    Height = h;

    Map = new char[w*h];
    BoardState = new char[w*h];

    for (unsigned int i=0;i<w*h;i++)
        BoardState[i]='.';

    for (unsigned int i=0;i<w*h;i++)
        Map[i]=map[i];
}

Puzzle::~Puzzle() {
    if (Map)
        delete[] Map;
    if (BoardState)
        delete[] BoardState;
}

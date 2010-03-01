/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>

class Puzzle
{
public:
    Puzzle(unsigned int, unsigned int, std::string);
    ~Puzzle();

    char
            *Map,
            *BoardState;

    unsigned int
            Width,
            Height;
};

#endif // PUZZLE_H

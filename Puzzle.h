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
#include <cstring>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "PicrossException.h"

#define MAP_FALSE '.'
#define MAP_TRUE '#'
#define MAP_CLEAN '.'
#define MAP_MARKED 'X'
#define MAP_HIT 'H'

class Puzzle
{
public:
    Puzzle(unsigned int, unsigned int, std::string);
    ~Puzzle();

    static Puzzle *RandomPuzzle(unsigned int w, unsigned int h, unsigned int percentageFilled);

    bool GameWon();

    std::vector<int>
            *ColStreaks,
            *RowStreaks;

    char
            *Map,
            *BoardState;

    unsigned int
            Width,
            Height;

private:
    void CalculateStreaks();
};

#endif // PUZZLE_H

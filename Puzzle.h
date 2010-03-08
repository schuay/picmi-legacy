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

#include <vector>
#include <cstring>
#include <cstdlib>

#include "Point.h"
#include "PicrossException.h"

#define MAP_FALSE       0
#define MAP_TRUE        1
#define BOARD_CLEAN     0
#define BOARD_MARKED    1
#define BOARD_HIT       2

class Puzzle
{
public:
    Puzzle(unsigned int, unsigned int, std::string);
    ~Puzzle();

    static Puzzle *RandomPuzzle(    /* returns a random puzzle with given dimensions */
            unsigned int w, unsigned int h, unsigned int percentageFilled);

    bool GameWon(); /* returns true if the puzzle has been completely solved  */

    int GetStateAt(Point p);    /* returns the state of game board at p */
    int GetMapAt(Point p);      /* returns the state of map at p */

    void SetStateAt(Point p, int state); /* set state of board at p */

    std::vector<int>
            *ColStreaks,    /* stores streaks */
            *RowStreaks;

    const unsigned int
            Width,
            Height;

private:
    void CalculateStreaks();

    static const char
            mapFalse = '.',
            mapTrue = '#',
            boardClean = '.',
            boardMarked = 'X',
            boardHit = 'H';
    
    char
            *Map,   /* stores the puzzle map (which fields are empty, which fields are boxes) */
            *BoardState;    /* stores current state of game board (uncovered, marked, clean) */
};

#endif // PUZZLE_H

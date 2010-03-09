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

#define OP_NONE         0  // defines for game actions, NONE, HIT (uncover a tile), MARK (mark a tile as empty)
#define OP_HIT          1
#define OP_MARK         2

class Puzzle
{
public:
    Puzzle(unsigned int, unsigned int, std::string);
    ~Puzzle();

    static Puzzle *RandomPuzzle(    /* returns a random puzzle with given dimensions */
            unsigned int w, unsigned int h, unsigned int percentageFilled);

    bool GameWon(); /* returns true if the puzzle has been completely solved  */

    bool IsInBounds(unsigned int x, unsigned int y);    /* returns true if coordinate is in puzzle limits */
    bool IsInBounds(Point &p);

    int GetStateAt(Point &p);    /* returns the state of game board at p */
    int GetMapAt(Point &p);      /* returns the state of map at p */

    void SetStateAt(Point &p, int state); /* set state of board at p */

    Point GetLocation();    /* get / set current location */
    bool TrySetLocation(Point &p);  /* try setting absolute / relative current location; returns true on success, false on failure*/
    bool TrySetLocationRel(int dx, int dy);

    void DoOpAt(Point &p, int op);  /* perform operation (HIT/MARK) at p */
    void DoOp(int op);              /* or at current location */

    unsigned int GetElapsedTime();
    unsigned int GetElapsedRealTime();
    unsigned int GetElapsedPenaltyTime();

    std::vector<int>
            *ColStreaks,    /* stores streaks */
            *RowStreaks;

    const unsigned int
            Width,
            Height;

private:
    void CalculateStreaks();

    Point Location; /* stores current location on board */

    unsigned int
            startTime,          /* game start time (s)*/
            penaltyTime,        /* base penalty time */
            penaltyMultiplier;  /* current penalty multiplier (applied to penaltyTime) */

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

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

#include "b_boardgame.h"
#include "b_picsettings.h"
#include "b_picstreak.h"
#include "b_picpoint.h"
#include "b_picexception.h"
#include "b_picdefines.h"
#include "b_picpngloader.h"
#include "b_pictimer.h"

class Picross : public BoardGame
{
public:
    Picross(PicSettings &s);
    ~Picross();

    bool GameWon(); /* returns true if the puzzle has been completely solved  */

    int GetStateAt(PicPoint &p);                    /* returns the state of game board at p */
    int GetStateAt(unsigned int x, unsigned int y);
    int GetMapAt(PicPoint &p);                      /* returns the state of map at p */
    int GetMapAt(unsigned int x, unsigned int y);

    void SetStateAt(PicPoint &p, int state); /* set state of board at p */

    void DoOpAt(PicPoint &p, int op);   /* perform operation (HIT/MARK) at p */
    void DoOp(int op);                  /* or at current location */

    void CalculateStreakSolvedState();  /* call this to update streak.Solved states - ideally once before drawing each frame */

    unsigned int GetElapsedRealTime();
    unsigned int GetElapsedPenaltyTime();

    float GetCompletedPercentageBoxes();

    std::vector<PicStreak>
            *ColStreaks,    /* stores streaks */
            *RowStreaks;

private:
    std::vector<PicStreak>* CalculateStreaksFromMap(bool horizontal); /* horizontal: true == row streaks, false == column streaks */
    std::vector<PicStreak> CalculateStreaksFromState(              /* startFromEnd: when true, starts calculation from end of row.*/
            bool horizontal, int lineIndex, bool startFromEnd); /* this matters because streaks from state need to be contigous*/
                                                                /* lineIndex: which row/column to calc streaks for */

    bool NoHintsMode;   /* in this mode, allow incorrectly marking a tile as BOARD_HIT */

    void Load(PicSettings &s);            /* generate / load a map before initializing class */
    void Initialize(PicSettings &s);      /* check integrity and initialize class */
    void RandomPuzzle(PicSettings &s);    /* generates random puzzle with given dimensions and sets map in settings */

    unsigned int nrOfBoxes;          /* number of boxes in map - set only once in constructor */;

    static const char
            mapFalse = '.',
            mapTrue = '#',
            boardMarked = 'X',
            boardHit = 'H';
};

#endif // PUZZLE_H

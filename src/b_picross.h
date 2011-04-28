/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <cstring>
#include <cstdlib>
#include <boost/shared_array.hpp>

#include "b_boardgame.h"
#include "b_boardsettings.h"
#include "b_picstreak.h"
#include "b_point.h"
#include "b_exception.h"
#include "b_picdefines.h"
#include "b_timer.h"
#include "b_picstatselement.h"

using boost::shared_ptr;
using boost::shared_array;
using std::vector;

namespace BoardGame {
class Picross : public BoardGame
{
public:
    Picross(BoardSettings &s);
    ~Picross();

    bool DetectAndHandleGameOver();

    int GetStateAt(Point &p) const;                    /* returns the state of game board at p */
    int GetStateAt(unsigned int x, unsigned int y) const;

    void DoOpAt(Point &p, int op);   /* perform operation (HIT/MARK) at p */
    void DoOp(int op);                  /* or at current location */

    void CalculateStreakSolvedState();  /* call this to update streak.Solved states - ideally once before drawing each frame */

    unsigned int GetElapsedRealTime() const;
    unsigned int GetElapsedPenaltyTime() const;

    float GetCompletedPercentageBoxes() const;

    shared_ptr<StatsElement> GetStats() const;

    vector<PicStreak>
            *ColStreaks,    /* stores streaks */
            *RowStreaks;

private:

    void SetStateAt(Point &p, int state); /* set state of board at p */

    int GetMapAt(Point &p) const;                      /* returns the state of map at p */
    int GetMapAt(unsigned int x, unsigned int y) const;

    vector<PicStreak>* CalculateStreaksFromMap(bool horizontal); /* horizontal: true == row streaks, false == column streaks */
    vector<PicStreak> CalculateStreaksFromState(                 /* startFromEnd: when true, starts calculation from end of row.*/
            bool horizontal, int lineIndex, bool startFromEnd); /* this matters because streaks from state need to be contigous*/
                                                                /* lineIndex: which row/column to calc streaks for */

    bool NoHintsMode;                       /* in this mode, allow incorrectly marking a tile as BOARD_HIT */

    void Initialize(BoardSettings &s);      /* check integrity and initialize class */
    void RandomPuzzle(BoardSettings &s);    /* generates random puzzle with given dimensions and sets map in settings */

    unsigned int nrOfBoxes;                 /* number of boxes in map - set only once in constructor */;


    /* stores the actual solved state of the puzzle */
    shared_array<char> map;

    /* stores the current state of the board visible to user */
    shared_array<char> boardState;

    void popUndoQueue();
    void pushUndoQueue();
    vector<shared_array<char> > undoQueue;

    static const char
            mapFalse = '.',
            mapTrue = '#',
            boardClean = '.',
            boardMarked = 'X',
            boardHit = 'H';
};
}
#endif // PUZZLE_H

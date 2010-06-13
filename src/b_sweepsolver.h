/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPSOLVER_H
#define B_SWEEPSOLVER_H

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <set>
#include <vector>
#include <iostream>

#include "b_exception.h"
#include "b_point.h"

using boost::shared_array;
using boost::shared_ptr;

namespace BoardGame {

class Set;

/* SweepSolver stores all temporary objects needed to solve a Sweeper grid. */
class SweepSolver
{
public:
    SweepSolver(int width, int height);
    ~SweepSolver();

    int
            *BoardState,    /* our working copy of the current board state */
            *OldState;      /* and a snapshot of the boardstate during the previous solver
                               loop iteration. used to detect all changes to board state. */

    std::set<int>
            TodoSets;       /* list of tiles to be processed in main solver loop */

    shared_array<Set>
            Sets;           /* our base for solver deductions */


    std::set<int>
            GetSetWing(Set &base, Set &subtractor) const;

    std::vector<int>        /* return coordinates to all (Exposed && !Done) sets overlapping x,y */
            GetOverlappingSets(Set &s) const;

    std::vector<int>        /* returns list of changed coordinates by comparing {Board,Old}State, then resets OldState */
            GetStateChanges();

    int
            GetRandomUnfinishedSet(Point &except_here) const;
    int
            GetRandomUntouchedSet(Point &except_here, Point &and_here) const;
    int
            GetRandomMediumPerturbSet(Point &except_here, Point &and_here) const;

    void                    /* called from perturb functions.  */
            UpdateNrOfNeighbors(int x, int y);

    bool    Done;

private:    

    void                    /* copies BoardState to OldState */
            ResetOldState();

    int
            _width,
            _height;
};


/* A set stores information about a tile and its surroundings */
class Set {
    friend class SweepSolver;
public:

    Set() {
        Reset();
    }
    void Reset() {
        _x = 0;
        _y = 0;
        _unknownNeighbors = 8;
        _neighbors = 8;
        _knownMines = 0;
        _totalMines = 0;
        _exposed = false;
        _marked = false;
        _done = false;
    }

    void SetMarked() {
        if (_exposed || _done)
            throw Exception("Tried to mark a (Exposed || Done) set.");

        _marked = true;
        _done = true;
    }

    void SetExposed(unsigned int knownMines, unsigned int totalMines) {
        if (_marked || _done)
            throw Exception("Tried to expose a (Marked || Done) set.");

        if (knownMines > 8 || knownMines > totalMines)
            throw Exception("Tried to set invalid knownMines value.");

        _knownMines = knownMines;
        _totalMines = totalMines;
        _exposed = true;

        if (_unknownNeighbors == 0)
            _done = true;
    }

    void DecrMines() {
        if (_done)
            throw Exception("Tried to decrement mines on a (Done) set.");

        if (_knownMines == _totalMines)
            throw Exception("Tried to decrement mines on a set with UnknownMines == 0.");

        _knownMines++;
    }
    void DecrNeighbors() {
        if (_marked)
            return;

        if (_done)
            throw Exception("Tried to decrement neighbors on a (Done) set.");

        if (_unknownNeighbors == 0)
            throw Exception("Tried to decrement neighbors on a set with UnknownNeighbors == 0.");

        _unknownNeighbors--;

        if (_unknownNeighbors == 0 && _exposed)
            _done = true;
    }

    unsigned int X() const { return _x; }
    unsigned int Y() const { return _y; }
    unsigned int UnknownNeighbors() const { return _unknownNeighbors; }

    /* Nr of unknown mines surrounding current set.
       (= Nr of mines - Nr of marked neighbors */
    unsigned int UnknownMines() const { return _totalMines - _knownMines; }
    bool Exposed() const { return _exposed; }
    bool Marked() const { return _marked; }
    bool Done() const { return _done; }

    void Initialize(int x, int y, int width, int height) {

        int neighbors = 8;

        if ((x == 0 && y == 0) ||
            (x == width - 1 && y == height - 1))
            neighbors -= 5;
        else if (x == 0 || y == 0 ||
                 x == width - 1 || y == height - 1)
            neighbors -= 3;

        _x = x;
        _y = y;
        _neighbors = neighbors;
        _unknownNeighbors = neighbors;
    }

private:

    unsigned int
            _x,                  /* Position of current set */
            _y,
            _neighbors,
            _unknownNeighbors,   /* Nr of unknown neighbor tiles surrounding current set.
                                   (= Nr of neighbors ::3 in corner, 5 at side, 8 everywhere else::
                                       - Nr of marked or exposed neighbors ) */
            _totalMines,         /* Nr of mines around current tile */
            _knownMines;         /* Nr of known tiles around current tile */

    bool
            _exposed,            /* Current tile exposed? */
            _marked,             /* Current tile marked? */
            _done;               /* Set when no unknown neighbors remain.
                                   Done sets are skipped in processing list */
};


}
#endif // B_SWEEPSOLVER_H

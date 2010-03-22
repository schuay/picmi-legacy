/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPER_H
#define B_SWEEPER_H

#include <cstdlib>
#include <cstdio>

#include "b_sweepdefines.h"
#include "b_picsettings.h"
#include "b_boardgame.h"

class Sweeper : public BoardGame
{
public:
    Sweeper(PicSettings &s);
    ~Sweeper();

    bool GameWon();

    int GetStateAt(PicPoint &p);
    int GetStateAt(unsigned int x, unsigned int y);

    int GetMapAt(PicPoint &p);
    int GetMapAt(unsigned int x, unsigned int y);

    void SetStateAt(PicPoint &p, int state);

    void DoOpAt(PicPoint &p, int op);
    void DoOp(int op);

private:

    void RandomPuzzle(PicSettings &s);
    int CalcBombCount(unsigned int x, unsigned int y);
    int GetMapInternal(unsigned int x, unsigned int y);
    int GetStateInternal(unsigned int x, unsigned int y);

    static const int
            mapNone = 0,
            mapBomb = 9,
            boardClean = 0,
            boardExposed = 1,
            boardMarked = 2,
            boardTentative = 3;

    int *map,
        *boardState;
};

#endif // B_SWEEPER_H

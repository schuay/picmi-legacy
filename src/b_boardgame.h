/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_BOARDGAME_H
#define B_BOARDGAME_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "b_exception.h"
#include "b_timer.h"
#include "b_point.h"
#include "b_enums.h"
#include "b_statselement.h"

using boost::shared_ptr;

namespace BoardGame {

class BoardGame
{
public:
    BoardGame();
    virtual ~BoardGame();

    /* returns true if the puzzle has been completely solved  */
    virtual bool GameWon() = 0;

    /* returns true if the puzzle has been lost  */
    virtual bool GameLost() = 0;

    /* returns true if coordinate is in puzzle limits */
    bool IsInBounds(unsigned int x, unsigned int y) const;
    bool IsInBounds(Point &p) const;


    /* returns the state of game board at p */
    virtual int GetStateAt(Point &p) const = 0;
    virtual int GetStateAt(unsigned int x, unsigned int y) const = 0;

    /* returns the state of map at p */
    virtual int GetMapAt(Point &p) const = 0;
    virtual int GetMapAt(unsigned int x, unsigned int y) const = 0;

    /* get / set current location */
    Point GetLocation() const;

    /* try setting absolute / relative current location;
       returns true on success, false on failure */
    bool TrySetLocation(Point &p);
    bool TrySetLocationRel(int dx, int dy);


    /* perform operation (HIT/MARK) at p */
    virtual void DoOpAt(Point &p, int op) = 0;

    /* or at current location */
    virtual void DoOp(int op) = 0;

    /* returns elapsed time since gamestart in seconds */
    unsigned int GetElapsedTime() const;

    /* returns stats element (information about game, like dimensions, difficulty, time played) */
    virtual shared_ptr<StatsElement> GetStats() const = 0;

    /* sets game resolution (aborted/won/lost) and stops timer */
    virtual void SetResolution(GameResolutionEnum r) { resolution = r; timer.Stop(); quit = true; }

    unsigned int Width() const { return width; }
    unsigned int Height() const { return height; }

    unsigned int PixOffsetX() const { return puzzleLocation.x; }
    unsigned int PixOffsetY() const { return puzzleLocation.y; }
    unsigned int CellLength() const { return celllength; }
    unsigned int Zoom() const { return zoom; }

    bool GetQuit() { return quit; }

protected:

    /* convert coordinate to index */
    int CToI(Point &p) const { return CToI(p.x, p.y); }
    int CToI(unsigned int x, unsigned int y) const { return y*width + x; }

    /* set state of board at p */
    virtual void SetStateAt(Point &p, int state) = 0;

    /* stores current location on board */
    Point location;

    /* game timer */
    Timer timer;

    unsigned int
            width,
            height;


    /* puzzleLocation, celllength, zoom must be stored in game
       painter + inputhandler need access to them */

    /* left upper corner of puzzle (in pixels) */
    Point puzzleLocation;

    /* size of tiles in pixels */
    unsigned int celllength;

    /* zoom */
    unsigned int zoom;

    /* game state - in progress, aborted, won, lost */
    GameResolutionEnum resolution;    

    bool quit;
};
}
#endif // B_BOARDGAME_H

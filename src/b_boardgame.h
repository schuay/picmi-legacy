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

#include "b_picexception.h"
#include "b_pictimer.h"
#include "b_picpoint.h"

class BoardGame
{
public:
    BoardGame();
    ~BoardGame();

    /* returns true if the puzzle has been completely solved  */
    virtual bool GameWon() = 0;


    /* returns true if coordinate is in puzzle limits */
    bool IsInBounds(unsigned int x, unsigned int y);
    bool IsInBounds(PicPoint &p);


    /* returns the state of game board at p */
    virtual int GetStateAt(PicPoint &p) = 0;
    virtual int GetStateAt(unsigned int x, unsigned int y) = 0;

    /* returns the state of map at p */
    virtual int GetMapAt(PicPoint &p) = 0;
    virtual int GetMapAt(unsigned int x, unsigned int y) = 0;

    /* get / set current location */
    PicPoint GetLocation();

    /* try setting absolute / relative current location;
       returns true on success, false on failure */
    bool TrySetLocation(PicPoint &p);
    bool TrySetLocationRel(int dx, int dy);


    /* perform operation (HIT/MARK) at p */
    virtual void DoOpAt(PicPoint &p, int op) = 0;

    /* or at current location */
    virtual void DoOp(int op) = 0;

    /* returns elapsed time since gamestart in seconds */
    unsigned int GetElapsedTime();


    unsigned int Width() { return width; }
    unsigned int Height() { return height; }

    unsigned int PixOffsetX() { return puzzleLocation.x; }
    unsigned int PixOffsetY() { return puzzleLocation.y; }
    unsigned int CellLength() { return celllength; }
    unsigned int Zoom() { return zoom; }

    bool Quit;

protected:

    /* convert coordinate to index */
    int CToI(PicPoint &p) { return CToI(p.x, p.y); }
    int CToI(unsigned int x, unsigned int y) { return y*width + x; }

    /* set state of board at p */
    virtual void SetStateAt(PicPoint &p, int state) = 0;

    /* stores current location on board */
    PicPoint location;

    /* game timer */
    PicTimer timer;

    unsigned int
            width,
            height;


    /* puzzleLocation, celllength, zoom must be stored in game
       painter + inputhandler need access to them */

    /* left upper corner of puzzle (in pixels) */
    PicPoint puzzleLocation;

    /* size of tiles in pixels */
    unsigned int celllength;

    /* zoom */
    unsigned int zoom;
};

#endif // B_BOARDGAME_H

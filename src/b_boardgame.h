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

#ifndef B_BOARDGAME_H
#define B_BOARDGAME_H

#include <string>
#include <boost/shared_ptr.hpp>
#include <SFML/System/Vector2.hpp>

#include "b_exception.h"
#include "b_timer.h"
#include "b_enums.h"
#include "b_statselement.h"

using boost::shared_ptr;

namespace BoardGame {

class BoardGame
{
public:
    BoardGame();
    virtual ~BoardGame();

    /* returns true if coordinate is in puzzle limits */
    bool IsInBounds(unsigned int x, unsigned int y) const;
    bool IsInBounds(sf::Vector2i &p) const;

    virtual bool DetectAndHandleGameOver() = 0;

    /* returns the state of game board at p */
    virtual int GetStateAt(sf::Vector2i &p) const = 0;
    virtual int GetStateAt(unsigned int x, unsigned int y) const = 0;

    /* returns the state of map at p */
    virtual int GetMapAt(sf::Vector2i &p) const = 0;
    virtual int GetMapAt(unsigned int x, unsigned int y) const = 0;

    /* get / set current location */
    sf::Vector2i GetLocation() const;

    /* try setting absolute / relative current location;
       returns true on success, false on failure */
    bool TrySetLocation(sf::Vector2i &p);
    bool TrySetLocationRel(int dx, int dy);


    /* perform operation (HIT/MARK) at p */
    virtual void DoOpAt(sf::Vector2i &p, int op) = 0;

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

    bool GetQuit() const { return quit; }

    bool GetPaused() const { return paused; }
    void SetPaused(bool isPaused) { paused = isPaused; timer.Pause(isPaused); }

protected:

    /* convert coordinate to index */
    int CToI(sf::Vector2i &p) const { return CToI(p.x, p.y); }
    int CToI(unsigned int x, unsigned int y) const { return y*width + x; }

    /* set state of board at p */
    virtual void SetStateAt(sf::Vector2i &p, int state) = 0;

    /* stores current location on board */
    sf::Vector2i
            location;

    /* game timer */
    Timer
            timer;

    unsigned int
            width,
            height;


    /* puzzleLocation, celllength, zoom must be stored in game
       painter + inputhandler need access to them */

    /* left upper corner of puzzle (in pixels) */
    sf::Vector2i
            puzzleLocation;

    /* size of tiles in pixels */
    unsigned int
            celllength;

    /* game state - in progress, aborted, won, lost */
    GameResolutionEnum
            resolution;

    bool
            quit,
            paused;
};
}
#endif // B_BOARDGAME_H

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

#ifndef B_SWEEPER_H
#define B_SWEEPER_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <boost/shared_array.hpp>
#include <boost/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>

#include "b_sweepdefines.h"
#include "b_boardsettings.h"
#include "b_boardgame.h"
#include "b_sweepstatselement.h"
#include "b_sweepsolver.h"

using boost::shared_ptr;
using boost::shared_array;
using boost::thread;
using boost::unique_lock;
using boost::mutex;

namespace BoardGame {
class Sweeper : public BoardGame
{
public:
    Sweeper(BoardSettings &s);
    ~Sweeper();

    bool DetectAndHandleGameOver();

    int GetStateAt(sf::Vector2i &p) const;
    int GetStateAt(unsigned int x, unsigned int y) const;

    int GetMapAt(sf::Vector2i &p) const;
    int GetMapAt(unsigned int x, unsigned int y) const;

    void SetStateAt(sf::Vector2i &p, int state);

    void DoOpAt(sf::Vector2i &p, int op);
    void DoOp(int op);

    unsigned int MarkedBombCount() const;
    unsigned int TotalBombCount() const { return bombCount; }

    shared_ptr<StatsElement> GetStats() const;

    bool IsStarted() const { unique_lock<mutex> lock(mutexGameStarted); return gameStarted; }
    bool IsWorking() const { unique_lock<mutex> lock(mutexSolverWorking); return solverWorking; }

    void SetResolution(GameResolutionEnum r) {
        solverThread.interrupt(); solverThread.join(); BoardGame::SetResolution(r); }

private:

    /* generates a random board based on starting point clicked_location */
    /* places mines randomly except on clicked_location and all neighbors */
    void RandomPuzzle(const sf::Vector2i &clicked_location);

    int CalcBombCount(sf::Vector2i &p) const;

    /* creates an array of all target points in targetArray and returns nr of neighbors */
    /* the caller is responsible for freeing the array */
    /* if noDiagonals is true, diagonal neighbors are not returned */
    std::vector<int> GetNeighborCoords(sf::Vector2i &p, bool noDiagonals) const;

    /* exposing tiles is a recursive operation. expose all clear tiles connected to original tile. */
    void ExposeTile(sf::Vector2i &p, int *state);
    void ExposeTile(sf::Vector2i &p);

    /* this is called when clicking on an exposed tile. if the amount of marks matches the mapCount, start exposing all neighbors */
    void ExposeNeighborTiles();

    /* reveales the entire board - this is called once the game is won */
    void RevealBoard();

    void StartGame();

    static const int
            mapNone = 0,
            mapBomb = 9,
            boardClean = 0,
            boardExposed = 1,
            boardMarked = 2,
            boardTentative = 3;

    bool
            gameStarted,
            solverWorking,
            solverEnabled;

    mutable mutex
            mutexSolverWorking,
            mutexGameStarted;

    unsigned int bombCount;

    int *map,
        *boardState;

    /* BEGIN Solver members */

    void SlvSolve(sf::Vector2i clickedLocation);
    bool SlvTrySolve(sf::Vector2i clickedLocation, bool perturbsAllowed);
    void SlvUpdateSet(int x, int y);
    void SlvMarkAllUnknownInSet(Set &s, int mark);
    void SlvMark(int coord, int mark);
    void SlvUpdateSolverState();
    void SlvHandleChangeMarked(int x, int y);
    void SlvHandleChangeExposed(int x, int y);
    bool SlvGlobalDeductions();
    bool SlvWingDeductions(Set &s);
    bool SlvPerturbSet(sf::Vector2i& clicked_location);
    void SlvPerturbRotate(sf::Vector2i &mainP, bool unknownOnly);
    void SlvPerturbTransfer(sf::Vector2i &mainP, sf::Vector2i &partnerP);
    void SlvFinalizePerturbs(std::vector<int> &toReset);
    void SlvVisualizeStates() const;
    void SlvAssertCorrectState() const;

    /* does the actual work, sets gameStarted = true, solverWorking = false when done */
    thread solverThread;

    /* solver stores our temporary objects (board state, todo list, etc */
    shared_ptr<SweepSolver> solver;

    /* END Solver members */
};

}
#endif // B_SWEEPER_H

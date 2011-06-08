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

#include "b_sweepsolver.h"

namespace BoardGame {
SweepSolver::SweepSolver(int width, int height) :
        Sets(new Set[width * height])
{
    _width = width;
    _height = height;
    Done = false;

    BoardState = new int[width * height];
    OldState = new int[width * height];

    /* initialize Sets: position, unknown neighbors */
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++)
            Sets[y * width + x].Initialize(x, y, width, height);
    }

}
SweepSolver::~SweepSolver() {
    delete[] BoardState;
    delete[] OldState;
}

void SweepSolver::UpdateNrOfNeighbors(int x, int y) {

    int
            nrOfUnknownNeighbors = 0,
            nrOfKnownMines = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (x + dx < 0 || y + dy < 0 ||  /* skip OutOfBounds */
                x + dx >= _width || y + dy >= _height )
                continue;

            if (dx == 0 && dy == 0) /* skip self */
                continue;

            int coord = (y + dy) * _width + (x + dx);

            if (!Sets[coord].Marked() && !Sets[coord].Exposed())   /* skip done and unexposed sets */
                nrOfUnknownNeighbors++;
            else if (Sets[coord].Marked())
                nrOfKnownMines++;
        }
    }

    int coord = y * _width + x;

    Sets[coord]._unknownNeighbors = nrOfUnknownNeighbors;

    if (Sets[coord].Exposed()) {
        Sets[coord]._done = false;
        Sets[coord]._knownMines = nrOfKnownMines;
    }
}
std::vector<int> SweepSolver::GetOverlappingSets(Set &s) const {

    int
            x = s.X(),
            y = s.Y();

    std::vector<int> overlaps;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (x + dx < 0 || y + dy < 0 ||  /* skip OutOfBounds */
                x + dx >= _width || y + dy >= _height )
                continue;

            if (dx == 0 && dy == 0) /* skip self */
                continue;

            int coord = (y + dy) * _width + (x + dx);

            if (Sets[coord].Done() || !Sets[coord].Exposed())   /* done and unexposed sets */
                continue;

            overlaps.push_back(coord);
        }
    }

    return overlaps;
}
std::set<int> SweepSolver::GetSetWing(Set &base, Set &subtractor) const {
    /* the wing concept is taken from simon tathams solver
       with set A and set B as follows:

       A,B: set centers
       a,b: wings of A and B
       x: overlapping area of A,B

       .........    .aaa.....
       ..A...... -> .aAxb....
       ...B.....    .axBb....
       .........    ..bbb....

       Resulting in 5 A wingtiles and 5 B wingtiles.


       Only clean (== unmarked and unexposed) tiles are taken into the wingset.
       The following situation:

       e: exposed
       m: marked

       ..me.....    .ame.....
       ..Am..... -> .aAmb....
       ...B.....    .axBb....
       .........    ..bbb....

       results in 3 A wingtiles and 5 B wingtiles.
     */

    std::set<int> wingTiles;
    int x, y, coord;

    /* insert all valid tiles from base into wingTiles */
    x = base.X();
    y = base.Y();

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (x + dx < 0 || y + dy < 0 ||  /* skip OutOfBounds */
                x + dx >= _width|| y + dy >= _height )
                continue;

            coord = (y + dy) * _width + (x + dx);

            if (Sets[coord].Exposed() || Sets[coord].Marked()) /* skip exposed and marked*/
                continue;

            wingTiles.insert(coord);
        }
    }

    /* now remove all tiles contained in subtractor */
    x = subtractor.X();
    y = subtractor.Y();

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

            if (x + dx < 0 || y + dy < 0 ||  /* skip OutOfBounds */
                x + dx >= _width|| y + dy >= _height )
                continue;

            coord = (y + dy) * _width + (x + dx);
            wingTiles.erase(coord);
        }
    }

    return wingTiles;
}

std::vector<int> SweepSolver::GetStateChanges() {

    std::vector<int> changes;

    for (int i = 0; i < _width * _height; i++)
        if (OldState[i] != BoardState[i])
            changes.push_back(i);

    ResetOldState();

    return changes;
}
void SweepSolver::ResetOldState() {
    for (int i = 0; i < _width * _height; i++)
        OldState[i] = BoardState[i];
}
int SweepSolver::GetRandomUnfinishedSet(sf::Vector2i &except_here) const {

    std::vector<int> unfinishedSets;

    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            int coord = y * _width + x;
            if (Sets[coord].Exposed() && !Sets[coord].Done() &&
                (abs(except_here.x - x) > 2 || abs(except_here.y - y) > 2))
                unfinishedSets.push_back(coord);
        }
    }

    if (unfinishedSets.size() == 0)
        return -1;

    int r = rand() % unfinishedSets.size();

    return unfinishedSets[r];
}
int SweepSolver::GetRandomMediumPerturbSet(sf::Vector2i &except_here, sf::Vector2i &and_here) const {

    std::vector<int> potentialSets;

    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            int coord = y * _width + x;
            if (Sets[coord].Exposed() && !Sets[coord].Done() &&
                (abs(except_here.x - x) > 2 || abs(except_here.y - y) > 2) &&
                (abs(and_here.x - x) > 2 || abs(and_here.y - y) > 2) &&
                Sets[coord].UnknownMines() > 0)
                potentialSets.push_back(coord);
        }
    }

    if (potentialSets.size() == 0)
        return -1;

    int r = rand() % potentialSets.size();

    return potentialSets[r];
}
int SweepSolver::GetRandomUntouchedSet(sf::Vector2i &except_here, sf::Vector2i &and_here) const {

    /* eligible: the set and all of its neighbors are unexposed and unmarked */

    std::vector<int> untouchedSets;

    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            int coord = y * _width + x;
            Set &s = Sets[coord];
            if (!s.Exposed() && !s.Marked() && // s._neighbors == s._unknownNeighbors &&
                (abs(except_here.x - x) > 2 || abs(except_here.y - y) > 2) &&
                (abs(and_here.x - x) > 2 || abs(and_here.y - y) > 2))
                untouchedSets.push_back(coord);
        }
    }

    if (untouchedSets.size() == 0)
        return -1;

    /* more than 30% untouched, not a valid base for going into untouched sets. */
    if ((untouchedSets.size() * 100) / (_width * _height) > 30)
        return -1;

    int r = rand() % untouchedSets.size();

    return untouchedSets[r];
}

}


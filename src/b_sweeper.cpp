/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweeper.h"
namespace BoardGame {
Sweeper::Sweeper(BoardSettings &s) : BoardGame(), map(NULL), boardState(NULL)
{
    width = s.x;
    height = s.y;

    puzzleLocation.x = 0;
    puzzleLocation.y = 0;

    RandomPuzzle(s);
}
Sweeper::~Sweeper() {
    if (map)
        delete[] map;
    if (boardState)
        delete[] boardState;
}

void Sweeper::RandomPuzzle(BoardSettings &s) {
    int randX, randY, mineCount;

    mineCount = width*height*s.Difficulty/100;

    map = new int[width*height];
    boardState = new int[width*height];

    for (unsigned int i=0; i < width*height; i++) {
        map[i] = mapNone;
        boardState[i] = boardClean;
    }

    srand(time(NULL));

    for (int i=0; i<mineCount; i++) {

        do {
            randX = rand() % width;
            randY = rand() % height;
        }
        while (map[randY*width + randX] != mapNone);

        map[randY*width + randX] = mapBomb;
    }

    Point p;
    for (p.x=0; p.x<width; p.x++)
        for (p.y=0; p.y<height; p.y++)
            if (map[CToI(p)] != mapBomb)
                map[p.y*width + p.x] = CalcBombCount(p);
}
int Sweeper::CalcBombCount(Point &p) {
    unsigned int bombCount = 0;
    Point *neighbors = NULL;
    int neighborCount = 0;

    neighbors = GetNeighborCoords(p, neighborCount, false);

    for (int i=0; i<neighborCount; i++) {
        if (map[CToI(neighbors[i].x, neighbors[i].y)] == mapBomb)
            bombCount++;
    }

    if (neighbors)
        delete[] neighbors;

    return bombCount;
}

bool Sweeper::GameWon() {
    for (unsigned int x = 0; x<width; x++)
        for (unsigned int y = 0; y<height; y++)
            if (map[CToI(x,y)] == mapBomb && boardState[CToI(x,y)] != boardMarked)
                return false;
    return true;
}

int Sweeper::GetStateAt(Point &p) {
    return GetStateAt(p.x, p.y);
}
int Sweeper::GetStateAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw Exception("GetStateAt failed: Point not within puzzle dimensions.");

    switch (boardState[y*width + x]) {
    case boardClean:
        return S_BOARD_CLEAN;
        break;
    case boardExposed:
        return S_BOARD_EXPOSED;
        break;
    case boardMarked:
        return S_BOARD_MARKED;
        break;
    case boardTentative:
        return S_BOARD_TENTATIVE;
        break;
    default:
        throw Exception("Boardstate in invalid state");
    }
}

int Sweeper::GetMapAt(Point &p) {
    return GetMapAt(p.x, p.y);
}
int Sweeper::GetMapAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw Exception("GetMapAt failed: Point not within puzzle dimensions.");

    int i = map[y*width + x];
    if (i != mapNone && i != mapBomb &&
        !(i>=1 && i <= 8))
        throw Exception("Map in invalid state");

    switch (i) {
    case mapNone:
        return S_MAP_NONE;
        break;
    case mapBomb:
        return S_MAP_BOMB;
        break;
    default:
        return i;
    }
}

void Sweeper::SetStateAt(Point &p, int state) {
    if (!IsInBounds(p.x, p.y))
        throw Exception("SetStateAt failed: Point not within puzzle dimensions.");

    if (state != boardClean && state != boardExposed &&
        state != boardMarked && state != boardTentative)
        throw Exception("Invalid state passed");

    boardState[p.y*width + p.x] = state;
}

void Sweeper::DoOpAt(Point &p, int op) {
    if (op == S_OP_NONE)
        return;

    if (op != S_OP_EXPOSE && op != S_OP_MARK && op != S_OP_TENTATIVE)
        throw Exception("DoOpAt failed: Incorrect operation passed.");

    int
            state = boardState[CToI(p)];

    if (state == boardExposed)  /* exposed tiles cannot be altered */
        return;

    switch (op) {
    case S_OP_EXPOSE:       /* recursive expose */
        ExposeTile(p);
        break;
    case S_OP_MARK:         /* mark tile as bomb */
        if (state == boardClean)
            SetStateAt(p, boardMarked);
        else if (state == boardTentative)
            SetStateAt(p, boardClean);
        break;
    case S_OP_TENTATIVE:    /* mark tile as tentative */
        if (state == boardClean)
            SetStateAt(p, boardTentative);
        else if (state == boardTentative)
            SetStateAt(p, boardClean);
        break;
    }
}
void Sweeper::DoOp(int op) {
    DoOpAt(location, op);
}

Point *Sweeper::GetNeighborCoords(Point &p, int &targetCount, bool noDiagonals) {
    bool pos[3][3];
    int nrOfNeighborTiles = 0,
        i,j;
    Point *targetArray;

    targetCount = 0;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            pos[i][j]=true;

    if (noDiagonals)
        pos[0][0]=pos[2][2]=pos[0][2]=pos[2][0]=false;

    pos[1][1] = false;  /* self */

    if (p.x == 0)
        pos[0][0]=pos[0][1]=pos[0][2]=false;
    if (p.y == 0)
        pos[0][0]=pos[1][0]=pos[2][0]=false;
    if (p.x == width-1)
        pos[2][0]=pos[2][1]=pos[2][2]=false;
    if (p.y == height-1)
        pos[0][2]=pos[1][2]=pos[2][2]=false;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            if (pos[i][j])
                nrOfNeighborTiles++;

    targetArray = new Point[nrOfNeighborTiles];

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            if (pos[i][j]) {
                targetArray[targetCount++] = Point(p.x + i - 1, p.y + j - 1);
            }

    return targetArray;
}

void Sweeper::ExposeTile(Point &p) {

    boardState[CToI(p)] = boardExposed;

    /* if maptile is NOT empty, stop recursion */

    if (map[CToI(p)] != mapNone)
        return;

    /* recurse over all nondiagonal neighbor tiles */

    Point *neighbors = NULL;
    int neighborCount;

    neighbors = GetNeighborCoords(p, neighborCount, true);

    for (int i=0; i<neighborCount; i++)
        ExposeTile(neighbors[i]);

    if (neighbors)
        delete[] neighbors;
}
}

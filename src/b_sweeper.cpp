/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweeper.h"

Sweeper::Sweeper(PicSettings &s) : BoardGame(), map(NULL), boardState(NULL)
{
    width = s.x;
    height = s.y;

    RandomPuzzle(s);
}
Sweeper::~Sweeper() {
    if (map)
        delete[] map;
    if (boardState)
        delete[] boardState;
}

void Sweeper::RandomPuzzle(PicSettings &s) {
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

    for (unsigned int i=0; i<width; i++)
        for (unsigned int j=0; j<height; j++)
            if (GetMapInternal(i,j) != mapBomb)
                map[j*width + i] = CalcBombCount(i,j);
}
int Sweeper::CalcBombCount(unsigned int x, unsigned int y) {
    unsigned int bombCount = 0;

    if (x != 0 && y != 0)
        if (GetMapInternal(x-1, y-1) == mapBomb)
            bombCount++;

    if (y != 0)
        if (GetMapInternal(x, y-1) == mapBomb)
            bombCount++;

    if (y != 0 && x != width-1)
        if (GetMapInternal(x+1, y-1) == mapBomb)
            bombCount++;

    if (x != 0)
        if (GetMapInternal(x-1, y) == mapBomb)
            bombCount++;

    if (x != width-1)
        if (GetMapInternal(x+1, y) == mapBomb)
            bombCount++;

    if (x != 0 && y != height-1)
        if (GetMapInternal(x-1, y+1) == mapBomb)
            bombCount++;

    if (y != height-1)
        if (GetMapInternal(x, y+1) == mapBomb)
            bombCount++;

    if (y != height-1 && x != width-1)
        if (GetMapInternal(x+1, y+1) == mapBomb)
            bombCount++;

    return bombCount;
}

bool Sweeper::GameWon() {
    for (unsigned int x = 0; x<width; x++)
        for (unsigned int y = 0; y<height; y++)
            if (GetMapInternal(x,y) == mapBomb && GetStateInternal(x,y) != boardMarked)
                return false;
    return true;
}

int Sweeper::GetMapInternal(unsigned int x, unsigned int y) {
    return map[y*width + x];
}
int Sweeper::GetStateInternal(unsigned int x, unsigned int y) {
    return boardState[y*width + x];
}

int Sweeper::GetStateAt(PicPoint &p) {
    return GetStateAt(p.x, p.y);
}
int Sweeper::GetStateAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicException("GetStateAt failed: Point not within puzzle dimensions.");

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
        throw PicException("Boardstate in invalid state");
    }
}

int Sweeper::GetMapAt(PicPoint &p) {
    return GetMapAt(p.x, p.y);
}
int Sweeper::GetMapAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicException("GetMapAt failed: Point not within puzzle dimensions.");

    int i = map[y*width + x];
    if (i != mapNone && i != mapBomb &&
        !(i>=1 && i <= 8))
        throw PicException("Map in invalid state");

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

void Sweeper::SetStateAt(PicPoint &p, int state) {
    if (!IsInBounds(p.x, p.y))
        throw PicException("SetStateAt failed: Point not within puzzle dimensions.");

    if (state != boardClean && state != boardExposed &&
        state != boardMarked && state != boardTentative)
        throw PicException("Invalid state passed");

    boardState[p.y*width + p.x] = state;
}

void Sweeper::DoOpAt(PicPoint &p, int op) {
    if (op == S_OP_NONE)
        return;

    if (op != S_OP_EXPOSE && op != S_OP_MARK && op != S_OP_TENTATIVE)
        throw PicException("DoOpAt failed: Incorrect operation passed.");

    int
            state = GetStateInternal(p.x, p.y),
            map = GetMapInternal(p.x, p.y);

    if (state == boardExposed)  /* exposed tiles cannot be altered */
        return;

    switch (op) {
    case S_OP_EXPOSE:       /* recursive expose */
        /* TODO */
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

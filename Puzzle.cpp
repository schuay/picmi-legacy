/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "Puzzle.h"

Puzzle::Puzzle(unsigned int w, unsigned int h, std::string map) :
        ColStreaks(NULL), RowStreaks(NULL), Width(w), Height(h), Map(NULL), BoardState(NULL)
{
    if (map.length() < w*h)
        throw PicrossException("Input map has incorrect size");

    Map = new char[w*h];
    BoardState = new char[w*h];

    for (unsigned int i=0; i < w*h; i++)
        BoardState[i] = boardClean;

    for (unsigned int i=0; i < w*h; i++)
        if (map[i] == mapTrue || map[i] == mapFalse)
            Map[i] = map[i];
        else throw PicrossException("Illegal character in input map");

    CalculateStreaks();
}

Puzzle::~Puzzle() {
    if (Map)
        delete[] Map;
    if (BoardState)
        delete[] BoardState;

    if (ColStreaks)
        delete[] ColStreaks;
    if (RowStreaks)
        delete[] RowStreaks;
}

bool Puzzle::GameWon() {
    int mapFilled = 0, stateFilled = 0;

    for (unsigned int i = 0; i < strlen(Map); i++)
        if (Map[i] == mapTrue)
            mapFilled++;

    for (unsigned int i = 0; i<strlen(BoardState); i++)
        if (BoardState[i] == boardHit)
            stateFilled++;

    return (mapFilled == stateFilled);
}
bool Puzzle::IsInBounds(Point &p) {
    return IsInBounds(p.x, p.y);
}
bool Puzzle::IsInBounds(unsigned int x, unsigned int y) {
    return (x < Width && y < Height);
}

void Puzzle::CalculateStreaks() {
    unsigned int
            i, j,
            lenOfCurrRowStreak,
            lenOfCurrColStreak;

    RowStreaks = new std::vector<int>[Height];
    ColStreaks = new std::vector<int>[Width];

    /* calculate the numbers to show in rows */
    for(i = 0; i < Height; i++) {
        lenOfCurrRowStreak = 0;

        for(j = 0; j < Width; j++) {
            if (Map[i*Width + j] == mapTrue)
                lenOfCurrRowStreak++;
            else if (lenOfCurrRowStreak > 0) {
                RowStreaks[i].push_back(lenOfCurrRowStreak);
                lenOfCurrRowStreak = 0;
            }
        }

        if (lenOfCurrRowStreak > 0)
            RowStreaks[i].push_back(lenOfCurrRowStreak);
    }

    /* calculate the numbers to show in columns */
    for(i = 0; i < Width; i++) {
        lenOfCurrColStreak = 0;

        for(j = 0; j < Height; j++) {
            if (Map[j*Width + i] == mapTrue)
                lenOfCurrColStreak++;
            else if (lenOfCurrColStreak > 0) {
                ColStreaks[i].push_back(lenOfCurrColStreak);
                lenOfCurrColStreak = 0;
            }
        }

        if (lenOfCurrColStreak > 0)
            ColStreaks[i].push_back(lenOfCurrColStreak);
    }
}

Puzzle* Puzzle::RandomPuzzle(unsigned int w, unsigned int h, unsigned int percentageFilled) {

    if (percentageFilled > 99)
        return new Puzzle(w, h, std::string(w*h, mapTrue));

    std::string map(w*h, '.');
    int cellsToFill = w*h*percentageFilled/100,
        randX, randY;

    srand(time(NULL));

    for (int i=0; i<cellsToFill; i++) {

        do {
            randX = rand() % w;
            randY = rand() % h;
        }
        while (map[randY*w + randX] != mapFalse);

        map[randY*w + randX] = mapTrue;
    }

    return new Puzzle(w, h, map);
}

int Puzzle::GetMapAt(Point &p) {
    if (!IsInBounds(p))
        throw PicrossException("GetMapAt failed: Point not within puzzle dimensions.");

    if (Map[p.y*Width + p.x] == mapTrue)
        return MAP_TRUE;
    else
        return MAP_FALSE;
}
int Puzzle::GetStateAt(Point &p) {
    if (!IsInBounds(p))
        throw PicrossException("GetStateAt failed: Point not within puzzle dimensions.");

    if (BoardState[p.y*Width + p.x] == boardClean)
        return BOARD_CLEAN;
    else if (BoardState[p.y*Width + p.x] == boardHit)
        return BOARD_HIT;
    else
        return BOARD_MARKED;
}
void Puzzle::SetStateAt(Point &p, int state) {
    if (state != BOARD_CLEAN && state != BOARD_HIT && state != BOARD_MARKED)
        throw PicrossException("SetStateAt failed: invalid state passed");
    if (!IsInBounds(p))
        throw PicrossException("SetStateAt failed: Point not within puzzle dimensions.");

    char c;

    switch (state) {
    case BOARD_CLEAN:
        c = boardClean;
        break;
    case BOARD_HIT:
        c = boardHit;
        break;
    case BOARD_MARKED:
        c = boardMarked;
        break;
    }

    BoardState[p.y*Width + p.x] = c;
}

Point Puzzle::GetLocation() {
    return Point(&Location);
}
void Puzzle::SetLocation(Point &p) {
    if (!IsInBounds(p))
        throw PicrossException("SetLocation failed: Point not within puzzle dimensions.");

    Location.x = p.x;
    Location.y = p.y;
}

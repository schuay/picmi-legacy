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
        ColStreaks(NULL), RowStreaks(NULL), Width(w), Height(h),
        Map(NULL), BoardState(NULL)
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

    ColStreaks = CalculateStreaksFromMap(false);
    RowStreaks = CalculateStreaksFromMap(true);

    penaltyTime = 0;
    penaltyMultiplier = 1;
    startTime = time(NULL);
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

std::vector<Streak>* Puzzle::CalculateStreaksFromMap(bool horizontal) {
    /* note:    CalculateStreaksFromMap / CalculateStreaksFromState functions are very similar
                when changing one, don't forget to change the other */

    unsigned int i, j, lenOfCurrStreak;

    unsigned int iMax = horizontal ? Height : Width; /* loop bounds differ for cols / rows */
    unsigned int jMax = horizontal ? Width : Height;

    std::vector<Streak> *s = new std::vector<Streak>[iMax];

    for(i = 0; i < iMax; i++) {
        lenOfCurrStreak = 0;

        for(j = 0; j < jMax; j++) {
            int posIndex = horizontal ? i*Width + j : j*Width + i; /* index calc differs for cols / rows */

            if (Map[posIndex] == mapTrue)
                lenOfCurrStreak++;
            else if (lenOfCurrStreak > 0) {
                s[i].push_back(Streak(lenOfCurrStreak));
                lenOfCurrStreak = 0;
            }
        }

        if (lenOfCurrStreak > 0)
            s[i].push_back(Streak(lenOfCurrStreak));
    }

    return s;
}
std::vector<Streak> Puzzle::CalculateStreaksFromState(bool horizontal, int lineIndex, bool startFromEnd) {
    /* note:    CalculateStreaksFromMap / CalculateStreaksFromState functions are very similar
                when changing one, don't forget to change the other */

    unsigned int j, jCalc, lenOfCurrStreak = 0;

    unsigned int jMax = horizontal ? Width : Height; /* loop bounds differ for cols / rows */

    std::vector<Streak> s;

    for(j = 0; j < jMax; j++) {

        jCalc = startFromEnd ? jMax - 1 - j : j;    /* reverse direction of loop if startFromEnd == true */
        int posIndex = horizontal ?     /* index calc differs for cols / rows */
                       lineIndex*Width + jCalc :
                       jCalc*Width + lineIndex;

        if (BoardState[posIndex] == boardClean) {
            break;              /* return only contigous streaks for solved calculation */
        }
        else if (BoardState[posIndex] == boardHit)
            lenOfCurrStreak++;
        else if (lenOfCurrStreak > 0) {
            s.push_back(Streak(lenOfCurrStreak));
            lenOfCurrStreak = 0;
        }
    }

    if (lenOfCurrStreak > 0)
        s.push_back(Streak(lenOfCurrStreak));

    return s;
}
void Puzzle::CalculateStreakSolvedState() {
    /* when is a streak solved?
       * either if all streaks in a row/col are marked completely == whole row/col is solved
       * or - coming from the edge of a puzzle - every tile must be either HIT or MARKED
         note that this means streak.Solved does not necessarily reflect the true state:
         with board map: ..X..X.... (X == box) and board state: XXXXXHX... (X == marked, H = hit),
         the first streak would be marked as solved even though the row is NOT solved correctly
     */

    unsigned int i, j, sumFromStreak, sumFromBoard, sumFromBoardIncludingMarked;

    /* col streaks */
    for (i = 0; i < Width; i++) {

        /* entire col solved? */
        sumFromBoard = sumFromStreak = sumFromBoardIncludingMarked = 0;
        for (j = 0; j < ColStreaks[i].size(); j++)
            sumFromStreak += ColStreaks[i][j].GetLength();
        for (j = 0; j < Height; j++) {
            int state = GetStateAt(i, j);
            if (state == BOARD_HIT)
                sumFromBoard++;
            if (state == BOARD_HIT || state == BOARD_MARKED)
                sumFromBoardIncludingMarked++;
        }

        if (sumFromBoard == sumFromStreak)
            for (j = 0; j < ColStreaks[i].size(); j++)
                ColStreaks[i][j].Solved = true;

        /* entire line marked but not correctly */
        else if (sumFromBoardIncludingMarked == Height)
            for (j = 0; j < ColStreaks[i].size(); j++)
                ColStreaks[i][j].Solved = false;

        /* if not entire col solved and tiles are checked in col (to prevent unnecessary work), do detailed check */
        else if (sumFromBoard > 0) {
            std::vector<Streak> vFromStart = CalculateStreaksFromState(false, i, false);
            std::vector<Streak> vFromEnd = CalculateStreaksFromState(false, i, true);

            for (j = 0; j < vFromStart.size(); j++) /* from beginning */
                ColStreaks[i][j].Solved = (vFromStart[j].GetLength() == ColStreaks[i][j].GetLength());

            for (j = 0; j < vFromEnd.size(); j++) { /* from end */
                int posIndex = ColStreaks[i].size() - 1 - j;
                ColStreaks[i][posIndex].Solved = (vFromEnd[j].GetLength() == ColStreaks[i][posIndex].GetLength());
            }
        }

    }

    /* row streaks */
    for (i = 0; i < Height; i++) {

        /* entire row solved? */
        sumFromBoard = sumFromStreak = sumFromBoardIncludingMarked = 0;
        for (j = 0; j < RowStreaks[i].size(); j++)
            sumFromStreak += RowStreaks[i][j].GetLength();
        for (j = 0; j < Width; j++) {
            int state = GetStateAt(j, i); /* note reversed state of i/j */
            if (state == BOARD_HIT)
                sumFromBoard++;
            if (state == BOARD_HIT || state == BOARD_MARKED)
                sumFromBoardIncludingMarked++;
        }

        if (sumFromBoard == sumFromStreak)
            for (j = 0; j < RowStreaks[i].size(); j++)
                RowStreaks[i][j].Solved = true;

        /* entire line marked but not correctly */
        else if (sumFromBoardIncludingMarked == Width)
            for (j = 0; j < RowStreaks[i].size(); j++)
                RowStreaks[i][j].Solved = false;

        /* if not entire row solved and tiles are checked in row (to prevent unnecessary work), do detailed check */
        else if (sumFromBoard > 0) {
            std::vector<Streak> vFromStart = CalculateStreaksFromState(true, i, false);
            std::vector<Streak> vFromEnd = CalculateStreaksFromState(true, i, true);

            for (j = 0; j < vFromStart.size(); j++) /* from beginning */
                RowStreaks[i][j].Solved = (vFromStart[j].GetLength() == RowStreaks[i][j].GetLength());

            for (j = 0; j < vFromEnd.size(); j++) { /* from end */
                int posIndex = RowStreaks[i].size() - 1 - j;
                RowStreaks[i][posIndex].Solved = (vFromEnd[j].GetLength() == RowStreaks[i][posIndex].GetLength());
            }
        }
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
    return GetMapAt(p.x, p.y);
}
int Puzzle::GetMapAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicrossException("GetMapAt failed: Point not within puzzle dimensions.");

    if (Map[y*Width + x] == mapTrue)
        return MAP_TRUE;
    else
        return MAP_FALSE;
}
int Puzzle::GetStateAt(Point &p) {
    return GetStateAt(p.x, p.y);
}
int Puzzle::GetStateAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicrossException("GetStateAt failed: Point not within puzzle dimensions.");

    if (BoardState[y*Width + x] == boardClean)
        return BOARD_CLEAN;
    else if (BoardState[y*Width + x] == boardHit)
        return BOARD_HIT;
    else
        return BOARD_MARKED;
}

void Puzzle::SetStateAt(Point &p, int state) {
    if (state != BOARD_CLEAN && state != BOARD_HIT && state != BOARD_MARKED)
        throw PicrossException("SetStateAt failed: invalid state passed");
    if (!IsInBounds(p))
        throw PicrossException("SetStateAt failed: Point not within puzzle dimensions.");
    if (GetStateAt(p) == BOARD_HIT)
        throw PicrossException("SetStateAt failed: cannot modify tile set to BOARD_HIT");
    if (state == BOARD_HIT && GetMapAt(p) == MAP_FALSE)
        throw PicrossException("SetStateAt failed: incorrect state BOARD_HIT requested");

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
bool Puzzle::TrySetLocation(Point &p) {
    if (!IsInBounds(p))
        return false;

    Location = p;

    return true;
}
bool Puzzle::TrySetLocationRel(int dx, int dy) {
    Point p(Location.x + dx, Location.y + dy);

    if (!IsInBounds(Location.x + dx, Location.y + dy))
        return false;

    Location.x += dx;
    Location.y += dy;

    return true;
}

void Puzzle::DoOpAt(Point &p, int op) {

    /* hit/mark logic */
    if (GetStateAt(p) == BOARD_HIT) {}    /* we cannot mark spots that are already hit */
    else if (op == OP_MARK) {
        if (GetStateAt(p) == BOARD_MARKED)
            SetStateAt(p, BOARD_CLEAN);
        else
            SetStateAt(p, BOARD_MARKED);
    }
    else if (op == OP_HIT) {                                 /* HIT */
        if (GetStateAt(p) == BOARD_MARKED)             /* was marked -> unmarked */
            SetStateAt(p, BOARD_CLEAN);
        else if (GetMapAt(p) == MAP_TRUE)      /* if correct -> hit */
            SetStateAt(p, BOARD_HIT);
        else if (GetMapAt(p) == MAP_FALSE) {     /* if incorrect -> marked and add to penaltyTime*/
            SetStateAt(p, BOARD_MARKED);
            penaltyTime += 120 * penaltyMultiplier++;
        }
    }
}
void Puzzle::DoOp(int op) {
    DoOpAt(Location, op);
}

unsigned int Puzzle::GetElapsedPenaltyTime() {
    return penaltyTime;
}
unsigned int Puzzle::GetElapsedRealTime() {
    return time(NULL) - startTime;
}
unsigned int Puzzle::GetElapsedTime() {
    return GetElapsedPenaltyTime() + GetElapsedRealTime();
}

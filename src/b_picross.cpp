/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picross.h"

Picross::Picross(PicSettings &s) :
        ColStreaks(NULL), RowStreaks(NULL),
        Map(NULL), BoardState(NULL)
{
    Load(s);
    Initialize(s);
}
Picross::~Picross() {
    if (Map)
        delete[] Map;
    if (BoardState)
        delete[] BoardState;

    if (ColStreaks)
        delete[] ColStreaks;
    if (RowStreaks)
        delete[] RowStreaks;
}

bool Picross::GameWon() {
    for (unsigned int i = 0; i < width * height; i++) {
        if (Map[i] == mapTrue && BoardState[i] != boardHit)
            return false;
        else if (Map[i] == mapFalse && BoardState[i] == boardHit)
            return false;
    }

    return true;
}
bool Picross::IsInBounds(PicPoint &p) {
    return IsInBounds(p.x, p.y);
}
bool Picross::IsInBounds(unsigned int x, unsigned int y) {
    return (x < width && y < height);
}

std::vector<PicStreak>* Picross::CalculateStreaksFromMap(bool horizontal) {
    /* note:    CalculateStreaksFromMap / CalculateStreaksFromState functions are very similar
                when changing one, don't forget to change the other */

    unsigned int i, j, lenOfCurrStreak;

    unsigned int iMax = horizontal ? height : width; /* loop bounds differ for cols / rows */
    unsigned int jMax = horizontal ? width : height;

    std::vector<PicStreak> *s = new std::vector<PicStreak>[iMax];

    for(i = 0; i < iMax; i++) {
        lenOfCurrStreak = 0;

        for(j = 0; j < jMax; j++) {
            int posIndex = horizontal ? i*width + j : j*width + i; /* index calc differs for cols / rows */

            if (Map[posIndex] == mapTrue)
                lenOfCurrStreak++;
            else if (lenOfCurrStreak > 0) {
                s[i].push_back(PicStreak(lenOfCurrStreak));
                lenOfCurrStreak = 0;
            }
        }

        if (lenOfCurrStreak > 0)
            s[i].push_back(PicStreak(lenOfCurrStreak));
    }

    return s;
}
std::vector<PicStreak> Picross::CalculateStreaksFromState(bool horizontal, int lineIndex, bool startFromEnd) {
    /* note:    CalculateStreaksFromMap / CalculateStreaksFromState functions are very similar
                when changing one, don't forget to change the other */

    unsigned int j, jCalc, lenOfCurrStreak = 0;

    unsigned int jMax = horizontal ? width : height; /* loop bounds differ for cols / rows */

    std::vector<PicStreak> s;

    for(j = 0; j < jMax; j++) {

        jCalc = startFromEnd ? jMax - 1 - j : j;    /* reverse direction of loop if startFromEnd == true */
        int posIndex = horizontal ?     /* index calc differs for cols / rows */
                       lineIndex*width + jCalc :
                       jCalc*width + lineIndex;

        if (BoardState[posIndex] == boardClean) {
            break;              /* return only contigous streaks for solved calculation */
        }
        else if (BoardState[posIndex] == boardHit)
            lenOfCurrStreak++;
        else if (lenOfCurrStreak > 0) {
            s.push_back(PicStreak(lenOfCurrStreak));
            lenOfCurrStreak = 0;
        }
    }

    if (lenOfCurrStreak > 0)
        s.push_back(PicStreak(lenOfCurrStreak));

    return s;
}
void Picross::CalculateStreakSolvedState() {
    /* when is a streak solved?
       * either if all streaks in a row/col are marked completely == whole row/col is solved
       * or - coming from the edge of a puzzle - every tile must be either HIT or MARKED
         note that this means streak.Solved does not necessarily reflect the true state:
         with board map: ..X..X.... (X == box) and board state: XXXXXHX... (X == marked, H = hit),
         the first streak would be marked as solved even though the row is NOT solved correctly
     */

    unsigned int i, j, sumFromStreak, sumFromBoard, sumFromBoardIncludingMarked;

    /* col streaks */
    for (i = 0; i < width; i++) {

        /* entire col solved? */
        sumFromBoard = sumFromStreak = sumFromBoardIncludingMarked = 0;
        for (j = 0; j < ColStreaks[i].size(); j++)
            sumFromStreak += ColStreaks[i][j].GetLength();
        for (j = 0; j < height; j++) {
            int state = GetStateAt(i, j);
            if (state == BOARD_HIT)
                sumFromBoard++;
            if (state == BOARD_HIT || state == BOARD_MARKED)
                sumFromBoardIncludingMarked++;
        }

        for (j = 0; j < ColStreaks[i].size(); j++)  /* reset state of all streaks to false */
            ColStreaks[i][j].Solved = false;

        if (!NoHintsMode && sumFromBoard == sumFromStreak)  /* test only valid if !NoHintsMode */
            for (j = 0; j < ColStreaks[i].size(); j++)
                ColStreaks[i][j].Solved = true;

        /* if not entire col solved and tiles are checked in col (to prevent unnecessary work), do detailed check */
        else if (sumFromBoard > 0) {
            std::vector<PicStreak> vFromStart = CalculateStreaksFromState(false, i, false);
            std::vector<PicStreak> vFromEnd = CalculateStreaksFromState(false, i, true);

            for (j = 0; j < vFromStart.size(); j++) /* from beginning */
                if (vFromStart[j].GetLength() == ColStreaks[i][j].GetLength())
                    ColStreaks[i][j].Solved = true;
                else
                    break;

            for (j = 0; j < vFromEnd.size(); j++) { /* from end */
                int posIndex = ColStreaks[i].size() - 1 - j;
                if (vFromEnd[j].GetLength() == ColStreaks[i][posIndex].GetLength())
                    ColStreaks[i][posIndex].Solved = true;
                else
                    break;
            }
        }

    }

    /* row streaks */
    for (i = 0; i < height; i++) {

        /* entire row solved? */
        sumFromBoard = sumFromStreak = sumFromBoardIncludingMarked = 0;
        for (j = 0; j < RowStreaks[i].size(); j++)
            sumFromStreak += RowStreaks[i][j].GetLength();
        for (j = 0; j < width; j++) {
            int state = GetStateAt(j, i); /* note reversed state of i/j */
            if (state == BOARD_HIT)
                sumFromBoard++;
            if (state == BOARD_HIT || state == BOARD_MARKED)
                sumFromBoardIncludingMarked++;
        }

        for (j = 0; j < RowStreaks[i].size(); j++)  /* reset state of all streaks to false */
            RowStreaks[i][j].Solved = false;

        if (!NoHintsMode && sumFromBoard == sumFromStreak)  /* test only valid if !NoHintsMode */
            for (j = 0; j < RowStreaks[i].size(); j++)
                RowStreaks[i][j].Solved = true;

        /* if not entire row solved and tiles are checked in row (to prevent unnecessary work), do detailed check */
        else if (sumFromBoard > 0) {
            std::vector<PicStreak> vFromStart = CalculateStreaksFromState(true, i, false);
            std::vector<PicStreak> vFromEnd = CalculateStreaksFromState(true, i, true);

            for (j = 0; j < vFromStart.size(); j++) /* from beginning */
                if (vFromStart[j].GetLength() == RowStreaks[i][j].GetLength())
                    RowStreaks[i][j].Solved = true;
                else
                    break;

            for (j = 0; j < vFromEnd.size(); j++) { /* from end */
                int posIndex = RowStreaks[i].size() - 1 - j;
                if (vFromEnd[j].GetLength() == RowStreaks[i][posIndex].GetLength())
                    RowStreaks[i][posIndex].Solved = true;
                else
                    break;
            }
        }
    }
}

void Picross::Load(PicSettings &s) {
    if (s.Type == PUZ_RAND) {
        RandomPuzzle(s);
    }
    else if (s.Type == PUZ_STAT) {
        PicPngLoader loader;
        if (s.LoadRandomFromPath)
            loader.LoadRandom(s);
        else
            loader.Load(s);
    }
    else
        throw PicException("Invalid puzzle type passed");
}
void Picross::Initialize(PicSettings &s) {
    if (!s.Validate())
        throw PicException("Settings validation failed");

    width = s.x;
    height = s.y;

    Map = new char[width * height];
    BoardState = new char[width * height];

    NrOfBoxes = 0;
    for (unsigned int i = 0; i < width * height; i++) {
        BoardState[i] = boardClean;
        if (s.Map[i] == mapTrue)
            NrOfBoxes++;
        if (s.Map[i] == mapTrue || s.Map[i] == mapFalse)
            Map[i] = s.Map[i];
        else throw PicException("Illegal character in input map");
    }

    ColStreaks = CalculateStreaksFromMap(false);
    RowStreaks = CalculateStreaksFromMap(true);

    /* if any rows/cols contain no boxes, mark entire row */
    for (unsigned int i = 0; i < width; i++)
        if (ColStreaks[i].size() == 0)
            for (unsigned int j = 0; j < height; j++)
                BoardState[j * width + i] = boardMarked;
    for (unsigned int i = 0; i < height; i++)
        if (RowStreaks[i].size() == 0)
            for (unsigned int j = 0; j < width; j++)
                BoardState[i * width + j] = boardMarked;


    NoHintsMode = s.NoHintsMode;
    timer.Start();
}
void Picross::RandomPuzzle(PicSettings &s) {

    if (s.Difficulty > 99) {
        s.Map = std::string(s.x * s.y, mapTrue);
        return;
    }

    std::string map(s.x*s.y, '.');
    int cellsToFill = s.x * s.y * (float)s.Difficulty /100,
        randX, randY;

    srand(time(NULL));

    for (int i=0; i<cellsToFill; i++) {

        do {
            randX = rand() % s.x;
            randY = rand() % s.y;
        }
        while (map[randY*s.x + randX] != mapFalse);

        map[randY*s.x + randX] = mapTrue;
    }

    s.Map = map;
}

int Picross::GetMapAt(PicPoint &p) {
    return GetMapAt(p.x, p.y);
}
int Picross::GetMapAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicException("GetMapAt failed: Point not within puzzle dimensions.");

    if (Map[y*width + x] == mapTrue)
        return MAP_TRUE;
    else
        return MAP_FALSE;
}
int Picross::GetStateAt(PicPoint &p) {
    return GetStateAt(p.x, p.y);
}
int Picross::GetStateAt(unsigned int x, unsigned int y) {
    if (!IsInBounds(x, y))
        throw PicException("GetStateAt failed: Point not within puzzle dimensions.");

    if (BoardState[y*width + x] == boardClean)
        return BOARD_CLEAN;
    else if (BoardState[y*width + x] == boardHit)
        return BOARD_HIT;
    else
        return BOARD_MARKED;
}

void Picross::SetStateAt(PicPoint &p, int state) {
    if (state != BOARD_CLEAN && state != BOARD_HIT && state != BOARD_MARKED)
        throw PicException("SetStateAt failed: invalid state passed");
    if (!IsInBounds(p))
        throw PicException("SetStateAt failed: Point not within puzzle dimensions.");

    char c;

    switch (state) {
    case BOARD_CLEAN:
        c = boardClean;
        break;
    case BOARD_HIT:
        c = boardHit;
        break;
    case BOARD_MARKED:
    default:
        c = boardMarked;
        break;
    }

    BoardState[p.y*width + p.x] = c;
}

PicPoint Picross::GetLocation() {
    return PicPoint(&Location);
}
bool Picross::TrySetLocation(PicPoint &p) {
    if (!IsInBounds(p))
        return false;

    Location = p;

    return true;
}
bool Picross::TrySetLocationRel(int dx, int dy) {
    PicPoint p(Location.x + dx, Location.y + dy);

    if (!IsInBounds(Location.x + dx, Location.y + dy))
        return false;

    Location.x += dx;
    Location.y += dy;

    return true;
}

void Picross::DoOpAt(PicPoint &p, int op) {    
    if (op == OP_NONE)
        return;

    if (op != OP_MARK && op != OP_HIT && op != OP_FORCE_CLEAR && op != OP_FORCE_MARK)
        throw PicException("DoOpAt failed: Incorrect operation passed.");

    int
            state = GetStateAt(p),
            map = GetMapAt(p);

    switch (NoHintsMode) {
    case false:                 /* NoHintsMode DISABLED */
        switch (op) {
        case OP_FORCE_CLEAR:            /* OP_FORCE_CLEAR requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_FORCE_MARK:            /* OP_FORCE_MARK requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                SetStateAt(p, BOARD_MARKED);
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_MARK:               /* OP_MARK requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                SetStateAt(p, BOARD_MARKED);
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_HIT:                /* OP_HIT requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                if (map == MAP_TRUE)
                    SetStateAt(p, BOARD_HIT);
                else if (map == MAP_FALSE) {
                    SetStateAt(p, BOARD_MARKED);
                    timer.AddPenalty();
                }
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        }
        break;
    case true:                  /* NoHintsMode ENABLED */
        switch (op) {
        case OP_FORCE_CLEAR:            /* OP_FORCE_CLEAR requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_FORCE_MARK:            /* OP_FORCE_MARK requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                SetStateAt(p, BOARD_MARKED);
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_MARK:               /* OP_MARK requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                SetStateAt(p, BOARD_MARKED);
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            case BOARD_HIT:             /* on HIT tile */
                break;
            }
            break;
        case OP_HIT:                /* OP_HIT requested */
            switch (state) {
            case BOARD_CLEAN:           /* on CLEAN tile */
                SetStateAt(p, BOARD_HIT);
                break;
            case BOARD_MARKED:          /* on MARKED tile */
                break;
            case BOARD_HIT:             /* on HIT tile */
                SetStateAt(p, BOARD_CLEAN);
                break;
            }
            break;
        }
        break;
    }
}
void Picross::DoOp(int op) {
    DoOpAt(Location, op);
}

unsigned int Picross::GetElapsedPenaltyTime() {
    return timer.GetPenaltyTime();
}
unsigned int Picross::GetElapsedRealTime() {
    return timer.GetRealTime();
}
unsigned int Picross::GetElapsedTime() {
    return timer.GetTime();
}

float Picross::GetCompletedPercentageBoxes() {
    int NrOfHitTiles = 0;

    for (unsigned int i = 0; i < width*height; i++)
        if (BoardState[i] == boardHit)
            NrOfHitTiles++;

    return ((float)NrOfHitTiles * 100.0f) / (float)NrOfBoxes;
}

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

#include "b_picross.h"
namespace BoardGame {
Picross::Picross(BoardSettings &s) : BoardGame(),
        ColStreaks(NULL), RowStreaks(NULL), map(NULL), boardState(NULL)
{
    RandomPuzzle(s);
    Initialize(s);
}
Picross::~Picross() {
    if (map)
        delete[] map;
    if (boardState)
        delete[] boardState;
    if (ColStreaks)
        delete[] ColStreaks;
    if (RowStreaks)
        delete[] RowStreaks;
}

bool Picross::GameWon() {
    for (unsigned int i = 0; i < width * height; i++) {
        if (map[i] == mapTrue && boardState[i] != boardHit)
            return false;
        else if (map[i] == mapFalse && boardState[i] == boardHit)
            return false;
    }

    SetResolution(GR_WON);
    return true;
}

shared_ptr<StatsElement> Picross::GetStats() const {
    shared_ptr<PicStatsElement> stats(new PicStatsElement);

    stats->nrOfBoxes = nrOfBoxes;
    stats->height = height;
    stats->width = width;
    stats->playedTime = timer.GetTime();
    stats->resolution = resolution;

    return stats;
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

            if (map[posIndex] == mapTrue)
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

        if (boardState[posIndex] == boardClean) {
            break;              /* return only contigous streaks for solved calculation */
        }
        else if (boardState[posIndex] == boardHit)
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

        if (sumFromBoardIncludingMarked == Height() && sumFromBoard != sumFromStreak)
        { } /* entire row/col is filled with either hits or marks but hitcount does not equal count generated from streaks */

        else if (!NoHintsMode && sumFromBoard == sumFromStreak)  /* when not in NoHintsMode, only correct hits are allowed */
            for (j = 0; j < ColStreaks[i].size(); j++)           /* so we can simply test by count and save calculation effort */
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


        if (sumFromBoardIncludingMarked == Width() && sumFromBoard != sumFromStreak)
        { } /* entire row/col is filled with either hits or marks but hitcount does not equal count generated from streaks */

        else if (!NoHintsMode && sumFromBoard == sumFromStreak)  /* when not in NoHintsMode, only correct hits are allowed */
            for (j = 0; j < RowStreaks[i].size(); j++)           /* so we can simply test by count and save calculation effort */
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

void Picross::Initialize(BoardSettings &s) {
    if (!s.Validate())
        throw Exception("Settings validation failed");

    width = s.x;
    height = s.y;

    map = new char[width * height];
    boardState = new char[width * height];

    nrOfBoxes = 0;
    for (unsigned int i = 0; i < width * height; i++) {
        boardState[i] = boardClean;
        if (s.Map[i] == mapTrue)
            nrOfBoxes++;
        if (s.Map[i] == mapTrue || s.Map[i] == mapFalse)
            map[i] = s.Map[i];
        else throw Exception("Illegal character in input map");
    }

    ColStreaks = CalculateStreaksFromMap(false);
    RowStreaks = CalculateStreaksFromMap(true);

    /* if any rows/cols contain no boxes, mark entire row */
    for (unsigned int i = 0; i < width; i++)
        if (ColStreaks[i].size() == 0)
            for (unsigned int j = 0; j < height; j++)
                boardState[j * width + i] = boardMarked;
    for (unsigned int i = 0; i < height; i++)
        if (RowStreaks[i].size() == 0)
            for (unsigned int j = 0; j < width; j++)
                boardState[i * width + j] = boardMarked;


    NoHintsMode = s.NoHintsMode;
    timer.Start();
}
void Picross::RandomPuzzle(BoardSettings &s) {

    if (s.Difficulty > 99) {
        s.Map = std::string(s.x * s.y, mapTrue);
        return;
    }

    std::string map(s.x*s.y, mapFalse);
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

int Picross::GetMapAt(Point &p) const {
    return GetMapAt(p.x, p.y);
}
int Picross::GetMapAt(unsigned int x, unsigned int y) const {
    if (!IsInBounds(x, y))
        throw Exception("GetMapAt failed: Point not within puzzle dimensions.");

    if (map[y*width + x] == mapTrue)
        return MAP_TRUE;
    else
        return MAP_FALSE;
}
int Picross::GetStateAt(Point &p) const {
    return GetStateAt(p.x, p.y);
}
int Picross::GetStateAt(unsigned int x, unsigned int y) const {
    if (!IsInBounds(x, y))
        throw Exception("GetStateAt failed: Point not within puzzle dimensions.");

    if (boardState[y*width + x] == boardClean)
        return BOARD_CLEAN;
    else if (boardState[y*width + x] == boardHit)
        return BOARD_HIT;
    else
        return BOARD_MARKED;
}

void Picross::SetStateAt(Point &p, int state) {
    if (state != BOARD_CLEAN && state != BOARD_HIT && state != BOARD_MARKED)
        throw Exception("SetStateAt failed: invalid state passed");
    if (!IsInBounds(p))
        throw Exception("SetStateAt failed: Point not within puzzle dimensions.");

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

    boardState[p.y*width + p.x] = c;
}

void Picross::DoOpAt(Point &p, int op) {
    if (paused)
        return;

    if (op == OP_NONE)
        return;

    if (op != OP_MARK && op != OP_HIT && op != OP_FORCE_CLEAR && op != OP_FORCE_MARK)
        throw Exception("DoOpAt failed: Incorrect operation passed.");

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
    DoOpAt(location, op);
}

unsigned int Picross::GetElapsedPenaltyTime() const {
    return timer.GetPenaltyTime();
}
unsigned int Picross::GetElapsedRealTime() const {
    return timer.GetRealTime();
}

float Picross::GetCompletedPercentageBoxes() const {
    int NrOfHitTiles = 0;

    for (unsigned int i = 0; i < width*height; i++)
        if (boardState[i] == boardHit)
            NrOfHitTiles++;

    return ((float)NrOfHitTiles * 100.0f) / (float)nrOfBoxes;
}
}

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
    puzzleLocation.y = 30;

    bombCount = width*height*s.Difficulty/100;

    gameStarted = false;

    /* initialize map and board state */

    map = new int[width*height];
    boardState = new int[width*height];

    for (unsigned int i = 0; i < width * height; i++) {
        map[i] = mapNone;
        boardState[i] = boardClean;
    }
}
Sweeper::~Sweeper() {
    if (map)
        delete[] map;
    if (boardState)
        delete[] boardState;
}

unsigned int Sweeper::MarkedBombCount() const {
    unsigned int markedCount = 0;
    for (unsigned int i = 0; i < width*height; i++)
        if (boardState[i] == boardMarked)
            markedCount++;

    return markedCount;
}

void Sweeper::RandomPuzzle(const Point &clicked_location) {

    /* fill list with all possible bomb locations, excluding click
       location and all neighboring tiles */

    std::vector<int> tentative_bomb_locations;
    for (unsigned int i = 0; i < width; i++)
        for (unsigned int j = 0; j < height; j++)
            if (!(abs(i - clicked_location.x) <= 1 && abs(j - clicked_location.y) <= 1))
                tentative_bomb_locations.push_back(j * width + i);

    /* place bombs in random locations */

    srand(time(NULL));

    for (unsigned int i = 0; i < bombCount; i++) {
        int pos = rand() % tentative_bomb_locations.size();

        map[tentative_bomb_locations[pos]] = mapBomb;
        tentative_bomb_locations.erase(tentative_bomb_locations.begin() + pos);
    }

    /* calculate and set hints */

    Point p;
    for (p.x=0; p.x<width; p.x++)
        for (p.y=0; p.y<height; p.y++)
            if (map[CToI(p)] != mapBomb)
                map[p.y*width + p.x] = CalcBombCount(p);

    /* start game */
    gameStarted = true;
    timer.Start();
}
int Sweeper::CalcBombCount(Point &p) const {
    unsigned int bombCount = 0;

    int neighborCount = 0;
    boost::shared_array<Point> neighbors =
            GetNeighborCoords(p, neighborCount, false);

    for (int i=0; i<neighborCount; i++) {
        if (map[CToI(neighbors[i].x, neighbors[i].y)] == mapBomb)
            bombCount++;
    }

    return bombCount;
}

bool Sweeper::GameWon() {
    /* the game is won by exposing all tiles without bombs */

    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++)
            if (map[CToI(x,y)] != mapBomb && boardState[CToI(x,y)] != boardExposed)
                return false;

    SolveBoard();
    SetResolution(GR_WON);

    return true;
}
bool Sweeper::GameLost() {
    for (unsigned int x = 0; x<width; x++)
        for (unsigned int y = 0; y<height; y++)
            if (map[CToI(x,y)] == mapBomb && boardState[CToI(x,y)] == boardExposed) {
                SetResolution(GR_LOST);
                return true;
            }

    return false;
}

shared_ptr<StatsElement> Sweeper::GetStats() const {
    shared_ptr<SweepStatsElement> stats(new SweepStatsElement);

    stats->height = height;
    stats->width = width;
    stats->playedTime = timer.GetTime();
    stats->resolution = resolution;

    stats->totalBombCount = bombCount;
    stats->markedBombCount = MarkedBombCount();

    return stats;
}

int Sweeper::GetStateAt(Point &p) const {
    return GetStateAt(p.x, p.y);
}
int Sweeper::GetStateAt(unsigned int x, unsigned int y) const {
    if (!IsInBounds(x, y))
        throw Exception("GetStateAt failed: Point not within puzzle dimensions.");

    switch (boardState[y*width + x]) {
    case boardClean:
        return S_BOARD_CLEAN;
        break;
    case boardExposed:
        switch (map[CToI(x,y)]) {
        case mapBomb:
            return S_BOARD_BOMB;
            break;
        case 1:
            return S_BOARD_EXPOSED_1;
            break;
        case 2:
            return S_BOARD_EXPOSED_2;
            break;
        case 3:
            return S_BOARD_EXPOSED_3;
            break;
        case 4:
            return S_BOARD_EXPOSED_4;
            break;
        case 5:
            return S_BOARD_EXPOSED_5;
            break;
        case 6:
            return S_BOARD_EXPOSED_6;
            break;
        case 7:
            return S_BOARD_EXPOSED_7;
            break;
        case 8:
            return S_BOARD_EXPOSED_8;
            break;
        default:
            return S_BOARD_EXPOSED;
        }
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

int Sweeper::GetMapAt(Point &p) const {
    return GetMapAt(p.x, p.y);
}
int Sweeper::GetMapAt(unsigned int x, unsigned int y) const {
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
    if (paused)
        return;

    if (op == S_OP_NONE)
        return;

    if (op != S_OP_EXPOSE && op != S_OP_MARK && op != S_OP_TENTATIVE)
        throw Exception("DoOpAt failed: Incorrect operation passed.");

    /* initialize game state depending on click location */
    if (!gameStarted)
        RandomPuzzle(p);

    int
            state = boardState[CToI(p)];

    /* exposed tiles can only be used to expose neighbors*/
    if (state == boardExposed && op != S_OP_EXPOSE)
        return;

    switch (op) {
    case S_OP_EXPOSE:       /* recursive expose */
        if (state == boardTentative)
            SetStateAt(p, boardClean);
        else if (state == boardExposed)
            ExposeNeighborTiles();
        else if (state == boardClean)
            ExposeTile(p);
        break;
    case S_OP_MARK:         /* mark tile as bomb */
        if (state == boardClean)
            SetStateAt(p, boardMarked);
        else if (state == boardMarked)
            SetStateAt(p, boardClean);
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

boost::shared_array<Point> Sweeper::GetNeighborCoords(Point &p, int &targetCount, bool noDiagonals) const {
    bool pos[3][3];
    int nrOfNeighborTiles = 0,
        i,j;

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

    boost::shared_array<Point> targetArray(
            new Point[nrOfNeighborTiles]);

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            if (pos[i][j]) {
                targetArray[targetCount++] = Point(p.x + i - 1, p.y + j - 1);
            }

    return targetArray;
}

void Sweeper::ExposeNeighborTiles() {
    int markCount = 0;

    int currentTile = map[CToI(location)];

    if (currentTile == mapBomb || currentTile == mapNone)
        return;

    int neighborCount = 0;
    boost::shared_array<Point> neighbors =
            GetNeighborCoords(location, neighborCount, false);

    for (int i=0; i<neighborCount; i++) {
        if (boardState[CToI(neighbors[i].x, neighbors[i].y)] == boardMarked)
            markCount++;
    }

    if (markCount == currentTile)
        for (int i = 0; i < neighborCount; i++)
            if (boardState[CToI(neighbors[i].x, neighbors[i].y)] != boardMarked)
                ExposeTile(neighbors[i]);
}
void Sweeper::ExposeTile(Point &p) {

    boardState[CToI(p)] = boardExposed;

    /* if maptile is NOT empty, stop recursion */

    if (map[CToI(p)] != mapNone)
        return;

    /* recurse over all nondiagonal neighbor tiles */

    int neighborCount = 0;
    boost::shared_array<Point> neighbors =
            GetNeighborCoords(p, neighborCount, false);

    for (int i=0; i<neighborCount; i++)
        if (boardState[CToI(neighbors[i])] != boardExposed)
            ExposeTile(neighbors[i]);
}

void Sweeper::SolveBoard() {
    for (unsigned int i = 0; i < width * height; i++) {
        if (boardState[i] != boardClean && boardState[i] != boardTentative)
            continue;

        switch (map[i]) {
        case mapNone:
            boardState[i] = boardExposed;
        case mapBomb:
            boardState[i] = boardMarked;
        }
    }
}
}

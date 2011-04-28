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

#include "b_sweeper.h"
namespace BoardGame {
Sweeper::Sweeper(BoardSettings &s) : BoardGame(), map(NULL), boardState(NULL)
{
    width = s.x;
    height = s.y;

    solverEnabled = s.EnableSolver;

    puzzleLocation.x = 0;
    puzzleLocation.y = 30;

    bombCount = width*height*s.Difficulty/100;

    gameStarted = false;
    solverWorking = false;

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

    for (unsigned int i = 0; i < width * height; i++)
        map[i] = mapNone;

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
}
int Sweeper::CalcBombCount(Point &p) const {
    unsigned int bombCount = 0;

    std::vector<int> neighbors =
            GetNeighborCoords(p, false);

    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (map[neighbors[i]] == mapBomb)
            bombCount++;
    }

    return bombCount;
}

bool Sweeper::DetectAndHandleGameOver() {

    /* the game is won by exposing all tiles without bombs */

    bool won = true;
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            if (map[CToI(x,y)] != mapBomb && boardState[CToI(x,y)] != boardExposed) {
                won = false;
            }
        }
    }

    if (won) {
        RevealBoard();
        SetResolution(GR_WON);

        return true;
    }

    /* and lost if any bombs have been exposed */

    for (unsigned int x = 0; x<width; x++) {
        for (unsigned int y = 0; y<height; y++) {
            if (map[CToI(x,y)] == mapBomb && boardState[CToI(x,y)] == boardExposed) {
                SetResolution(GR_LOST);
                return true;
            }
        }
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

    /* while the solver is working, return 'clean state' to prevent simultaneous access to
       boardState[] from main thread and solver thread. */
    if (solverWorking)
        return S_BOARD_CLEAN;

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

    if (solverWorking)
        return;

    if (op == S_OP_NONE)
        return;

    if (op != S_OP_EXPOSE && op != S_OP_MARK && op != S_OP_TENTATIVE)
        throw Exception("DoOpAt failed: Incorrect operation passed.");

    /* initialize game state depending on click location */
    if (!gameStarted) {
        if (solverEnabled) {
            solverThread = thread(&Sweeper::SlvSolve, this, p);
            return;
        }
        else {
            RandomPuzzle(p);
            StartGame();
        }
    }

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

std::vector<int> Sweeper::GetNeighborCoords(Point &p, bool noDiagonals) const {
    int
            i,j,
            dx,dy;
    std::vector<int>
            neighbors;

    for (dx = -1, i = 0; dx <= 1; dx++, i++) {
        for (dy = -1, j = 0; dy <= 1; dy++, j++) {

            if (dx == 0 && dy == 0)
                /* skip self */;

            else if (!IsInBounds(p.x + dx, p.y + dy))
                /* skip out of bounds */;

            else if (noDiagonals && abs(dx) == 1 && abs(dy) == 1)
                /* optionally skip diagonals */;

            else
                neighbors.push_back(CToI(p.x + dx, p.y + dy));
        }
    }

    return neighbors;
}

void Sweeper::ExposeNeighborTiles() {
    int markCount = 0;

    int currentTile = map[CToI(location)];

    if (currentTile == mapBomb || currentTile == mapNone)
        return;

    std::vector<int> neighbors =
            GetNeighborCoords(location, false);

    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (boardState[neighbors[i]] == boardMarked)
            markCount++;
    }

    if (markCount != currentTile)
        return;

    Point p;
    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (boardState[neighbors[i]] != boardMarked) {
            p.x = neighbors[i] % width;
            p.y = neighbors[i] / width;
            ExposeTile(p);
        }
    }
}
void Sweeper::ExposeTile(Point &p, int *state) {
    state[CToI(p)] = boardExposed;

    /* if maptile is NOT empty, stop recursion */

    if (map[CToI(p)] != mapNone)
        return;

    /* recurse over all neighbor tiles */

    std::vector<int> neighbors =
            GetNeighborCoords(p, false);

    Point q;
    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (state[neighbors[i]] != boardExposed) {
            q.x = neighbors[i] % width;
            q.y = neighbors[i] / width;
            ExposeTile(q, state);
        }
    }
}
void Sweeper::ExposeTile(Point &p) {
    ExposeTile(p, boardState);
}

void Sweeper::RevealBoard() {
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
void Sweeper::StartGame() {
    unique_lock<mutex> lockG(mutexGameStarted);
    unique_lock<mutex> lockS(mutexSolverWorking);

    solverWorking = false;
    gameStarted = true;
    timer.Start();
}

void Sweeper::SlvSolve(Point clickedLocation) {
    do {
        RandomPuzzle(clickedLocation);
    }
    while (!SlvTrySolve(clickedLocation, true));

    /* start game */
    ExposeTile(clickedLocation);
    StartGame();
}

bool Sweeper::SlvTrySolve(Point clickedLocation, bool perturbsAllowed) {

    /* this solver is ported from simon tathams 'mines' */

    /* return values: true on success ( == fully solvable puzzle ),
                      false on failure */

    unique_lock<mutex> lockS(mutexSolverWorking);
    solverWorking = true;
    lockS.unlock();


    int perturbs = 0;

    /* initialize our solver object */
    solver.reset(new SweepSolver(width, height));
    for (unsigned int i = 0; i < width * height; i++)
        solver->OldState[i] = solver->BoardState[i] = boardClean;

    /* recursively expose our initial area */
    ExposeTile(clickedLocation, solver->BoardState);

#ifdef SOLVERDEBUG
    int
            loopCount = 0,
            randomCount = 0,
            perturbCount = 0;
    SlvVisualizeStates();
#endif

    /* Main deductive loop. */
    while (1) {

        boost::this_thread::interruption_point();

#ifdef SOLVERDEBUG
        loopCount++;
#endif

        /* update solver state -> create and update sets, fill todo list */
        SlvUpdateSolverState();
#ifdef SOLVERDEBUG
        SlvAssertCorrectState();
#endif


        /* pick the first set off the todo list and run deductions based on it */
        if (!solver->TodoSets.empty()) {

            std::set<int>::iterator it = solver->TodoSets.begin();
            Set &s = solver->Sets[*it];
            solver->TodoSets.erase(it);


            /* skip unexposed sets */
            if (!s.Exposed())
                continue;

            /* skip completed sets */
            if (s.Done())
                continue;

#ifdef SOLVERDEBUG
            std::cout << std::endl << "POP set x,y: " << *it % width << "," << *it / width << ", mines:" << s.UnknownMines() << ", neighbors: "
                    << s.UnknownNeighbors();
#endif

            /* begin with the easiest case: either no mines exist around set or all unknown
               fields are mines. */
            if (s.UnknownMines() == 0 || s.UnknownMines() == s.UnknownNeighbors()) {

                int mark;
                if (s.UnknownMines() == 0)
                    mark = boardExposed;
                else mark = boardMarked;

                SlvMarkAllUnknownInSet(s, mark);

#ifdef SOLVERDEBUG
                std::cout << std::endl << "ACTION mark all around x,y " << s.X() << "," << s.Y() << " as " << mark;
                SlvVisualizeStates();
#endif

                continue;
            }
            /* no deductions based on our set alone are possible.
               get all overlapping sets and see if we can get results based on our set + an overlapping set. */

            if (SlvWingDeductions(s))
                continue;
        }
        else {

            /* We've run out of sets on our todo list.
               Check if any global deductions are possible */

            if (SlvGlobalDeductions())
                continue;

            /* Terminate conditions */
            if (!perturbsAllowed) {
                /* we are in sanity checking mode, no second changes.
                   if we can't fully solve the board in one try, return false == failure */
                if (solver->Done)
                    return true;
                else return false;  /* this should never happen! */
            }

            else if (solver->Done)
                /* we are in regular mode. if the board is reported to be solved,
                   perform a sanity check if we can fully solve the board with no perturbs.
                   we do this because i'm not sure if perturbs sometimes generate an illogical board:
                   in turn X, area A is opened because deductions from set 1. in turn Y, set 1 is perturbed
                   in a way that would have prevented area A being opened in turn X. however, since we don't start
                   deductions over from the beginning, area A is still opened and we use deductions from area A to
                   solve the board -> unsolvable puzzle */
                return SlvTrySolve(clickedLocation, false);



            /* Otherwise, try making changes to the board (without changing the minecount).
               After x tries, give up and create a new random puzzle */

            if (perturbs < 250) {

#ifdef SOLVERDEBUG
                perturbCount++;
#endif
                perturbs++;

                /* perform the actual perturbation on a random unfinished set */

                bool perturbSuccessful = SlvPerturbSet(clickedLocation);

                /* no usable set found, stop perturbation and generate a new random board */
                if (!perturbSuccessful)
                    perturbs = 250;
            }
            else return false;
        }
    }

#ifdef SOLVERDEBUG
    std::cout << std::endl << "LOOPS: " << loopCount << " PERTURBS: " << perturbCount << " RANDOMS: " << randomCount
              << std::endl;
#endif

    return false;
}
bool Sweeper::SlvWingDeductions(Set &s) {

    std::vector<int> overlaps = solver->GetOverlappingSets(s);

#ifdef SOLVERDEBUG
    std::cout << std::endl << "FETCH sets around x,y: " << s.X() << "," << s.Y()
            << " COUNT: " << overlaps.size();
#endif

    for (unsigned int i = 0; i < overlaps.size(); i++) {

        Set &s2 = solver->Sets[overlaps[i]];

        std::set<int> swing = solver->GetSetWing(s, s2);
        std::set<int> s2wing = solver->GetSetWing(s2, s);

#ifdef SOLVERDEBUG
        std::cout << std::endl << "COMPARE  1) x,y " << s.X() << "," << s.Y()
                << " unknown mines " << s.UnknownMines() << " wing size " << swing.size();
        std::cout << std::endl << "    with 2) x,y " << s2.X() << "," << s2.Y()
                << " unknown mines " << s2.UnknownMines() << " wing size " << s2wing.size();
#endif
        /* Again we start with the easiest case:
           Size of Wing A = Unknown Mines A - Unknown Mines B
           -> mark all tiles in Wing A and expose all in Wing B

           or vice versa

           For example:
           A has 3 unknown mines
           B has 1 unknown mine
           . are exposed tiles
           x are clear (unmarked and unexposed) tiles
           O are the marks we can set as result of this deduction

           ......    ......
           ...Ax. -> ...AO.
           ..Bxx.    ..BxO.
           .xxx..    ......

         */
        if (swing.size() == s.UnknownMines() - s2.UnknownMines() ||
            s2wing.size() == s2.UnknownMines() - s.UnknownMines()) {

            std::set<int>::iterator wingIt;
            std::set<int> *wToMark, *wToExpose;

            wToMark =   ((swing.size() == s.UnknownMines() - s2.UnknownMines()) ? &swing : &s2wing);
            wToExpose = ((swing.size() == s.UnknownMines() - s2.UnknownMines()) ? &s2wing : &swing);

            for (wingIt = wToMark->begin(); wingIt != wToMark->end(); wingIt++)
                SlvMark(*wingIt, boardMarked);

            for (wingIt = wToExpose->begin(); wingIt != wToExpose->end(); wingIt++)
                SlvMark(*wingIt, boardExposed);

#ifdef SOLVERDEBUG
        std::cout << std::endl << "ACTION mark wings 1) x,y " << s.X() << "," << s.Y()
                << ", 2) x,y " << s2.X() << "," << s2.Y();
        SlvVisualizeStates();
#endif

            return true;
        }
    }
    return false;
}

bool Sweeper::SlvPerturbSet(Point& clickedLocation) {

    int
            mainSetIndex,
            partnerSetIndex;
    Point
            mainP,
            partnerP;


    /* store the coordinates of sets we have changed so we can reset boardstate at the end */
    std::vector<int> toReset;


    /* perturb initialization - find out which kind of perturbs to perform and get all
       necessary coordinates */

    mainSetIndex = solver->GetRandomUnfinishedSet(clickedLocation);

    if (mainSetIndex != -1) {

        mainP.x = solver->Sets[mainSetIndex].X();
        mainP.y = solver->Sets[mainSetIndex].Y();

        partnerSetIndex = solver->GetRandomMediumPerturbSet(clickedLocation, mainP);
        if (partnerSetIndex != -1) { /* perturb var #2; do work and exit */
            partnerP.x = solver->Sets[partnerSetIndex].X();
            partnerP.y = solver->Sets[partnerSetIndex].Y();
            toReset.push_back(CToI(mainP));
            toReset.push_back(CToI(partnerP));
            SlvPerturbTransfer(mainP, partnerP);
            SlvFinalizePerturbs(toReset);
#ifdef SOLVERDEBUG
            SlvVisualizeStates();
#endif
            return true;
        }

//        if (s.UnknownNeighbors() > 1) { /* perturb var #1; do work and exit*/
//            toReset.push_back(CToI(mainP));
//            SlvPerturbRotate(mainP);
//            SlvFinalizePerturbs(toReset);
//#ifdef SOLVERDEBUG
//            SlvVisualizeStates();
//#endif
//            return true;
//        }
    }

    mainSetIndex = solver->GetRandomUntouchedSet(clickedLocation, clickedLocation);
    if (mainSetIndex != -1) { /* perturb var #3; do work and exit */
        mainP.x = solver->Sets[mainSetIndex].X();
        mainP.y = solver->Sets[mainSetIndex].Y();
        toReset.push_back(CToI(mainP));
        SlvPerturbRotate(mainP, false);
        SlvFinalizePerturbs(toReset);
#ifdef SOLVERDEBUG
        SlvVisualizeStates();
#endif
        return true;
    }

    return false;
}
void Sweeper::SlvPerturbRotate(Point &mainP, bool unknownOnly) {

    std::vector<int> neighbors =
            GetNeighborCoords(mainP, false);

    for (std::vector<int>::iterator it = neighbors.begin(); it != neighbors.end(); it++)
        if (solver->BoardState[*it] != boardClean && unknownOnly)
            neighbors.erase(it);

    /* rotate the state of all unknown neighbors in current set */

    int
            firstValue = -1,
            coord,
            nextCoord;

    for (unsigned int j = 0; j < neighbors.size(); j++) {
        coord = neighbors[j];
        nextCoord = neighbors[(j + 1) % neighbors.size()];

        if (j == 0)
            firstValue = map[coord];

        if (j == neighbors.size() - 1)
            map[coord] = firstValue;
        else
            map[coord] = map[nextCoord];
    }


#ifdef SOLVERDEBUG
        std::cout << std::endl << "PERTURB ROTATE: " << mainP.y * width + mainP.x << std::endl;
#endif
}
void Sweeper::SlvPerturbTransfer(Point &mainP, Point &partnerP) {

    std::vector<int> neighbors =
            GetNeighborCoords(mainP, false);

    std::vector<int> unknownNeighbors;
    for (unsigned int j = 0; j < neighbors.size(); j++)
        if (solver->BoardState[neighbors[j]] == boardClean)
            unknownNeighbors.push_back(neighbors[j]);

    /* move 1 mine between 2 exposed but unfinished sets */

    std::vector<int> partnerNeighbors =
            GetNeighborCoords(partnerP, false);

    for (unsigned int j = 0; j < partnerNeighbors.size(); j++) {
        int coord = partnerNeighbors[j];
        if (solver->BoardState[coord] == boardClean &&
            map[coord] == mapBomb) {
            map[coord] = mapNone;
#ifdef SOLVERDEBUG
            std::cout << std::endl << "PERTURB TRANSFER FROM: " << coord;
#endif
            break;
        }
    }

    for (unsigned int j = 0; j < unknownNeighbors.size(); j++) {
        int coord = unknownNeighbors[j];

        if (map[coord] != mapBomb) {
            map[coord] = mapBomb;
#ifdef SOLVERDEBUG
            std::cout << " TO: " << coord;
#endif
            break;
        }
    }
}
void Sweeper::SlvFinalizePerturbs(std::vector<int> &toReset) {

    /* update the map hints */
    Point q;
    for (q.x = 0; q.x < width; q.x++)
        for (q.y = 0; q.y < height; q.y++)
            if (map[CToI(q)] != mapBomb)
                map[q.y*width + q.x] = CalcBombCount(q);


    for (unsigned int i = 0; i < toReset.size(); i++) {


#ifdef SOLVERDEBUG
        std::cout << std::endl << "PERTURB FINALIZE : " << toReset[i] << std::endl;
#endif

        /* Reset the board state of all tiles affected by the set. This will be all tiles within 2 spaces of
           the set's center tile:

           ssat.    S: Set center
           Ssat.    s: set neighbor
           ssat.    a: affected tile
           aaat.    t: todo tile

           'S', 's', and 'a' tiles need to be: cleared in BoardState[] and reset in Sets[]
           't' tiles can keep their Exposed/Marked/Clean state, need to be reinitialized,
               added to the todo list, and have their UnknownNeighbors property updated.

        */

        int x = toReset[i] % width;
        int y = toReset[i] / width;

        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {

                if (!IsInBounds(x + dx, y + dy))
                    continue;

                int coord = CToI(x + dx, y + dy);


                /* 'S', 's', 'a' tiles */
                solver->BoardState[coord] = boardClean;
                solver->Sets[coord].Reset();
                solver->Sets[coord].Initialize(x + dx, y + dy, width, height);
            }
        }
        for (int dx = -3; dx <= 3; dx++) {
            for (int dy = -3; dy <= 3; dy++) {

                if (!IsInBounds(x + dx, y + dy))
                    continue;

                int coord = CToI(x + dx, y + dy);

                /* update known mines, unknown neighbors, done state */
                solver->UpdateNrOfNeighbors(x + dx, y + dy);

                /* and add 't' tiles to todo list */
                if (abs(dx) == 3 || abs(dy) == 3)
                    solver->TodoSets.insert(coord);
            }
        }

    }
}

#ifdef SOLVERDEBUG
void Sweeper::SlvAssertCorrectState() const {

    Point p;

    for (p.y = 0; p.y < height; p.y++) {
        for (p.x = 0; p.x < width; p.x++) {


            Set &s = solver->Sets[CToI(p.x, p.y)];
            std::vector<int> neighbors =
                    GetNeighborCoords(p, false);

            if (s.Marked()) continue;

            unsigned int
                    unknownNeighbors = neighbors.size(),
                    unknownMines = map[CToI(p.x, p.y)];

            if (unknownMines > 8 || unknownMines < 0) unknownMines = 0;

            for (unsigned int i = 0; i < neighbors.size(); i++) {
                int coord = neighbors[i];

                if (solver->Sets[coord].Exposed())
                    unknownNeighbors--;
                else if (solver->Sets[coord].Marked()) {
                    unknownMines--;
                    unknownNeighbors--;
                }
            }

            if (!s.Exposed()) unknownMines = 0;

            if (unknownMines != s.UnknownMines() ||
                unknownNeighbors != s.UnknownNeighbors())
                std::cout << std::endl << "ERROR: incorrect stats at " << p.x << "," << p.y;
        }
    }
}
void Sweeper::SlvVisualizeStates() const {

    int state;

    std::cout << std::endl << std::endl << "Map  -  State:" << std::endl << std::endl;

    //std::cout << "01234567890123456789  -  01234567890123456789" << std::endl << std::endl;
    std::cout << "0123456789  -  0123456789" << std::endl << std::endl;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            state = map[CToI(x, y)];
            if (state == mapBomb)
                std::cout << 'O';
            else std::cout << '.';
        }

        std::cout << "  -  ";

        for (unsigned int x = 0; x < width; x++) {
            state = solver->BoardState[CToI(x, y)];
            std::cout << ((state == boardClean) ? 'X' : (state == boardMarked) ? 'O' : '.');
        }

        std::cout << " " << y;

        std::cout << std::endl;
    }
}
#endif
bool Sweeper::SlvGlobalDeductions() {
    /* returns true if we did anything */

    int cleanTiles = 0;
    int markedTiles = 0;

    for (unsigned int i = 0; i < width * height; i++) {
        if (solver->BoardState[i] == boardClean)
            cleanTiles++;
        else if (solver->BoardState[i] == boardMarked)
            markedTiles++;
    }

    /* all tiles either marked or exposed -> all done! */
    if (cleanTiles == 0) {
        solver->Done = true;
        return false;
    }

    int remainingMines = bombCount - markedTiles;

    /* all remaining tiles are mined or all remaining tiles are clear */
    if (cleanTiles == remainingMines ||
        remainingMines == 0) {

        for (unsigned int i = 0; i < width * height; i++) {
            if (solver->BoardState[i] == boardClean) {
                if (remainingMines == 0)
                    solver->BoardState[i] = boardExposed;
                else
                    solver->BoardState[i] = boardMarked;
            }
        }

        return true;
    }

    return false;
}
void Sweeper::SlvUpdateSolverState() {
    /* to be run each iteration of the main solving loop

       goes through entire state and checks for changes
       all changed tiles are added to todo list

       possible changes:
        * clean -> marked: update all existing neighbor sets
        * clean -> exposed: create new set and update all neighbors
     */

    std::vector<int> changes = solver->GetStateChanges();
    int x, y;

    for (unsigned int i = 0; i < changes.size(); i++) {

        int coord = changes[i];
        Point p(coord % width, coord / width);


        /* first, update state of all neighboring sets */

        std::vector<int> neighbors =
                GetNeighborCoords(p, false);

        for (unsigned int j = 0; j < neighbors.size(); j++) {

            x = neighbors[j] % width;
            y = neighbors[j] / width;

            if (solver->BoardState[coord] == boardMarked)
                SlvHandleChangeMarked(x, y);
            else if (solver->BoardState[coord] == boardExposed)
                SlvHandleChangeExposed(x, y);
        }


        /* finally, update changed set itself */

        SlvUpdateSet(p.x, p.y);
    }
}
void Sweeper::SlvHandleChangeExposed(int x, int y) {
    int neighborCoord = CToI(x, y);

    /* tile has been exposed, so each neighboring tile has one less unknown neighbor */
    solver->Sets[neighborCoord].DecrNeighbors();


    /* if neighboring tile is exposed itself, add it to the todo list */
    if (solver->Sets[neighborCoord].Exposed()) {
        solver->TodoSets.insert(neighborCoord);
#ifdef SOLVERDEBUG
        std::cout << "b. TODO x,y: " << x << "," << y << std::endl;
#endif
    }
}
void Sweeper::SlvHandleChangeMarked(int x, int y) {
    int neighborCoord = CToI(x, y);

    /* tile has been marked, so each neighboring tile has one less unknown mine
       and needs to be added to the todo list.
       only set this if the neighboring tile is exposed. */
    if (solver->Sets[neighborCoord].Exposed()) {
        solver->Sets[neighborCoord].DecrMines();
        solver->TodoSets.insert(neighborCoord);
#ifdef SOLVERDEBUG
        std::cout << "a. TODO x,y: " << x << "," << y << std::endl;
#endif
    }

    /* of course marking the tile also decrements unknown neighbors in all neighboring tiles.
       this needs to be done AFTER decrementing mines, because a Set is marked 'Done' if unknown neighbors reaches 0. */
    solver->Sets[neighborCoord].DecrNeighbors();
}
void Sweeper::SlvUpdateSet(int x, int y) {

    /* dont change anything for already finalized sets.
       if this is true, there is probably a bug somewhere */
    if (solver->Sets[CToI(x,y)].Done())
        throw Exception("Tried to update a finalized set.");

    if (solver->BoardState[CToI(x,y)] == boardClean)
        return;

    /* a mine set - dont do anything except mark it as Marked and Done */
    if (solver->BoardState[CToI(x,y)] == boardMarked) {
        solver->Sets[CToI(x,y)].SetMarked();
    }
    /* an exposed set - initialize UnknownMines, mark it as Exposed, add to TodoSets */
    else {
        Point p(x,y);

        std::vector<int> neighbors =
                GetNeighborCoords(p, false);

        int
                totalMines,
                knownMines = 0;

        /* get the tile's minecount */
        totalMines = CalcBombCount(p);

        /* and decrement it for every marked neighbor tile */
        /* important: we calculate knownMines by looking at *SETS*.
           using boardState leads to inconsistencies in the following situation:

           Sets A, B. B has been marked as a mine and A has been exposed (in the same loop iteration).
           We are now in SlvUpdateSolverState. A is processed first - since it is initialized, the minecount is calculated.
           Using BoardState, the actual current minecount is set.
           B is processed next. Since it is marked, all neighboring Sets.Minecount are decremented. Decrementing A.Minecount
           is INCORRECT in this situation.

           Solution: Use Sets.Marked to calc Minecount.
         */
        for (unsigned int i = 0; i < neighbors.size(); i++)
            if (solver->Sets[neighbors[i]].Marked())
                knownMines++;

        solver->Sets[CToI(x,y)].SetExposed(knownMines, totalMines);

        solver->TodoSets.insert(CToI(x,y));
#ifdef SOLVERDEBUG
        std::cout << std::endl << "c. TODO x,y: " << x << "," << y << std::endl;
#endif
    }
}
void Sweeper::SlvMarkAllUnknownInSet(Set &s, int mark) {

    // mark all unknown tiles around set s with mark

    Point p(s.X(), s.Y());

    std::vector<int> neighbors =
            GetNeighborCoords(p, false);

    for (unsigned int i = 0; i < neighbors.size(); i++)
        SlvMark(neighbors[i], mark);
}
void Sweeper::SlvMark(int coord, int mark) {

    int state = solver->BoardState[coord];
    Point p(coord % width, coord / width);

    if (state == boardClean) {
        if (mark == boardMarked) {
            if (map[coord] != mapBomb)
                throw Exception("Incorrect deduction! Boom.");
            solver->BoardState[coord] = mark;
        }
        else if (mark == boardExposed) {
            if (map[coord] == mapBomb)
                throw Exception("Incorrect deduction! Boom.");
            ExposeTile(p, solver->BoardState);
        }
    }
}

}

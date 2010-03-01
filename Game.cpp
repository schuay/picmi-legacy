#include "Game.h"
#include <vector>
#include <sstream>
#include <iostream>

#define CELLLENGTH 12
#define PUZZLE_POSX 117
#define PUZZLE_POSY 107

void Game::DrawStreaks() {
    unsigned int i, j,
        lenOfCurrRowStreak, lenOfCurrColStreak;
    
    std::vector<int>
        rowStreaks[level_size],
        colStreaks[level_size];
    
    /* calculate the numbers to show in rows and columns*/
    for(i=0;i<level_size;i++) {
        lenOfCurrRowStreak = 0;
        lenOfCurrColStreak = 0;
        
        for(j=0;j<level_size;j++) {

            /* rows */
            if (currentPuzzle->Map[j*currentPuzzle->Width + i]=='#')
                lenOfCurrRowStreak++;
            else if (lenOfCurrRowStreak > 0) {
                rowStreaks[i].push_back(lenOfCurrRowStreak);
                lenOfCurrRowStreak=0;
            }

            /* cols */
            if (currentPuzzle->Map[i*currentPuzzle->Width + j]=='#')
                lenOfCurrColStreak++;
            else if (lenOfCurrColStreak > 0) {
                colStreaks[i].push_back(lenOfCurrColStreak);
                lenOfCurrColStreak=0;
            }
        }

        if (lenOfCurrRowStreak > 0)
            rowStreaks[i].push_back(lenOfCurrRowStreak);

        if (lenOfCurrColStreak > 0)
            colStreaks[i].push_back(lenOfCurrColStreak);
    }

    /* draw row streaks */
    for (i=0;i<level_size;i++) {
        std::stringstream out;

        for (j=0;j<rowStreaks[i].size();j++)
            out << rowStreaks[i][j] << ' ';

        GB_DrawText(out.str().c_str(),
                    PUZZLE_POSX-10*out.str().length()-5,
                    PUZZLE_POSY+i*CELLLENGTH-3);
    }

    /* draw col streaks */
    for (i=0;i<level_size;i++) {
        std::stringstream out;

        for (j=0;j<colStreaks[i].size();j++)
            out << colStreaks[i][j] << ' ';

        GB_DrawTextVert(out.str().c_str(),
                    PUZZLE_POSX+i*CELLLENGTH-4,
                    PUZZLE_POSY-10*out.str().length()-5);
    }
}

void Game::ProcessDrawing() {

    /* game board */

    FIFTEEN.GB_SetXY(PUZZLE_POSX,PUZZLE_POSY);
    FIFTEEN.GB_ShowSprite(0,0);

    for (unsigned int j=0;j<level_size;j++) {
        for (unsigned int i=0;i<level_size;i++) {
            if (currentPuzzle->BoardState[i*currentPuzzle->Width + j] == 'H') {
                PushedBlock.GB_SetXY(PUZZLE_POSX+i*CELLLENGTH,PUZZLE_POSY+j*CELLLENGTH);
                PushedBlock.GB_ShowSprite(0,0);
            } else if (currentPuzzle->BoardState[i*currentPuzzle->Width + j] == 'X') {
                CheckedBlock.GB_SetXY(PUZZLE_POSX+i*CELLLENGTH,PUZZLE_POSY+j*CELLLENGTH);
                CheckedBlock.GB_ShowSprite(0,0);
            }
        }
    }


    /* set movable object positions */
    Mattoc.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH);
    HitMattoc.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH);

    HorBar.GB_SetXY(PUZZLE_POSX-8,PUZZLE_POSY + mapY * CELLLENGTH-1);
    VertBar.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY-8);

    Erase.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH-5,PUZZLE_POSY + mapY * CELLLENGTH+10);
    EraseBlock.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH-5,PUZZLE_POSY + mapY * CELLLENGTH+10);

    Check.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH+12);

    /* draw movable objects */
    if (hit == 0 && erase == 0 && check == 0 && hitcheck == 0) {
        Mattoc.GB_ShowSprite(0,(MattocShowFrame/2)%4);
        SDL_Delay(30);
        MattocShowFrame++;
    }
}

void Game::ProcessLogic() {
    int	dx = 0,
        dy = 0;
    bool
        hit = false,
        mark = false;

    /* process input */
    if(GB_GetKey(SDLK_LEFT) == 1)
        dx = -1;
    else if (GB_GetKey(SDLK_RIGHT) == 1)
        dx = 1;
    else if (GB_GetKey(SDLK_UP) == 1)
        dy = -1;
    else if (GB_GetKey(SDLK_DOWN) == 1)
        dy = 1;
    else if(GB_GetKey(SDLK_RCTRL) == 1)     /* mark as isBomb */
        hit = true;
    else if(GB_GetKey(SDLK_RSHIFT) == 1)    /* mark as isNotBomb */
        mark = true;

    /* movement logic */
    if (mapX + dx < level_size &&
        mapX + dx >= 0)
        mapX += dx;
    if (mapY + dy < level_size &&
        mapY + dy >= 0)
        mapY += dy;

    /* this resets key presses? */
    GB_GetEvents();

    /* hit/mark logic: in tempMap, X == marked (as isNotBomb), H == hit (as isBomb), . == clear */
    if (currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] == 'H') {}    /* we cannot mark spots that are already hit */
    else if (mark) {
        if (currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] == 'X')
            currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] = '.';
        else
            currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] = 'X';
    }
    else if (hit) {                                 /* HIT */
        if (currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] == 'X')             /* was marked -> unmarked */
            currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] = '.';
        else if (currentPuzzle->Map[mapX*currentPuzzle->Width + mapY] == '#')      /* if correct -> hit */
            currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] = 'H';
        else if (currentPuzzle->Map[mapX*currentPuzzle->Width + mapY] == '.')      /* if incorrect -> marked */
            currentPuzzle->BoardState[mapX*currentPuzzle->Width + mapY] = 'X';
    }

    /* ANIMATIONS

    if(hit == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);   // %5
    }
    if(erase == 1) {
        if(tempMap[mapY][mapX] == ' ') {
            EraseBlock.GB_ShowSprite(0,EraseBlockShowFrame);   // %4
        } else {
            //	Erase.GB_ShowSprite(0,EraseShowFrame);   // %4
        }
    }
    if(hitcheck == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);   // %7
    }
    if(check == 1) {
        Check.GB_ShowSprite(0,CheckShowFrame);  // %6
    }

    */
}

void Game::Initialize() {

    /* Initiate audio, video and the text */

    GB_SetupSDL_Video();
    GB_SetupSDL_Audio();
    GB_LoadTextBitmap();

    FIFTEEN.GB_LoadSprite("gfx/FIFTEEN-grid.bmp",1);
    FIFTEEN.GB_SetColorKey(255,0,255);

    PushedBlock.GB_LoadSprite("gfx/pushed_block.bmp", 1);
    CheckedBlock.GB_LoadSprite("gfx/checked_block.bmp",1);

    HorBar.GB_LoadSprite("gfx/horcursor.bmp", 1);       // Load horizontal bar
    HorBar.GB_SetColorKey(255,0,255);

    VertBar.GB_LoadSprite("gfx/vertcursor.bmp", 1);       // Load vertical bar
    VertBar.GB_SetColorKey(255,0,255);

    Mattoc.GB_LoadSprite("gfx/mattoc.bmp", 1, 4);
    Mattoc.GB_SetColorKey(255,0,255);

    HitMattoc.GB_LoadSprite("gfx/hitmattoc2.bmp", 1, 5);
    HitMattoc.GB_SetColorKey(255,0,255);

    Check.GB_LoadSprite("gfx/check.bmp", 1, 7);
    Check.GB_SetColorKey(255,0,255);

    Erase.GB_LoadSprite("gfx/erase.bmp", 1, 4);
    Erase.GB_SetColorKey(255,0,255);

    EraseBlock.GB_LoadSprite("gfx/erase_block.bmp", 1, 4);
    EraseBlock.GB_SetColorKey(255,0,255);

    BG.GB_LoadBackground("gfx/FIFTEEN.bmp");

    Quit.GB_LoadSprite("gfx/quit.bmp", 1, 5);
    Quit.GB_SetColorKey(255,0,255);
    Quit.GB_SetXY(486,400);
}

Game::Game() {

    std::stringstream puzzleInitializer;
    puzzleInitializer <<
        "##.#.#.###.#.#." <<
        "#.#.#.#.#......" <<
        "###############" <<
        "#.#.#.#.#......" <<
        "###....##......" <<
        "#.#######......" <<
        "###....##......" <<
        "#.#....##......" <<
        "###....##......" <<
        "#.......#......" <<
        "#.#.#.........." <<
        "#.......#......" <<
        ".#.#..........." <<
        ".#.......#....." <<
        "#.#.....#......";

    currentPuzzle = new Puzzle(15, 15, puzzleInitializer.str());

    level_size = 15;
    mapX = 0;
    mapY = 0;
    hit = 0;
    erase = 0;
    hitcheck = 0;
    check = 0;
    quit = 0;

    MattocShowFrame = 0;
    HitMattocShowFrame = 0;
    EraseShowFrame = 0;
    CheckShowFrame = 0;
    EraseBlockShowFrame = 0;
}
Game::~Game() {
    if (currentPuzzle)
        delete currentPuzzle;
}

void Game::DoMainLoop() {
    BG.GB_ShowBackground();

    ProcessLogic();

    DrawStreaks();

    ProcessDrawing();
}

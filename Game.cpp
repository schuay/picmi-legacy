#include "Game.h"
#include <vector>
#include <sstream>
#include <iostream>

#define CELLLENGTH 12
#define PUZZLE_POSX 117
#define PUZZLE_POSY 107

void Game::DrawStreaks() {
    int i, j, lenOfCurrRowStreak, lenOfCurrColStreak;
    
    std::vector<int>
            rowStreaks[level_size],
            colStreaks[level_size];
    
    /* calculate the numbers to show in rows and columns*/
    for(i=0;i<level_size;i++) {
        lenOfCurrRowStreak = 0;
        lenOfCurrColStreak = 0;
        
        for(j=0;j<level_size;j++) {

            /* rows */
            if (puzzleMap[i][j]=='#')
                lenOfCurrRowStreak++;
            else if (lenOfCurrRowStreak > 0) {
                rowStreaks[i].push_back(lenOfCurrRowStreak);
                lenOfCurrRowStreak=0;
            }

            /* cols */
            if (puzzleMap[j][i]=='#')
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

void Game::DrawPuzzle() {

    FIFTEEN.GB_SetXY(PUZZLE_POSX,PUZZLE_POSY);
    FIFTEEN.GB_ShowSprite(0,0);

    for(int yy=0;yy<level_size;yy++) {
        for(int xx=0;xx<level_size;xx++) {

            if(tempMap[yy][xx] == '#') {
                PushedBlock.GB_SetXY(PUZZLE_POSX+xx*CELLLENGTH,PUZZLE_POSY+yy*CELLLENGTH);
                PushedBlock.GB_ShowSprite(0,0);
            }

            if(tempMap[yy][xx] == 'X') {
                CheckedBlock.GB_SetXY(PUZZLE_POSX+xx*CELLLENGTH,PUZZLE_POSY+yy*CELLLENGTH);
                CheckedBlock.GB_ShowSprite(0,0);
            }
        }
    }
}

void Game::DrawMattoc() {
    int	dx = 0,
        dy = 0;

    /* movement logic */
    if(GB_GetKey(SDLK_LEFT) == 1)
        dx = -1;
    else if (GB_GetKey(SDLK_RIGHT) == 1)
        dx = 1;
    else if (GB_GetKey(SDLK_UP) == 1)
        dy = -1;
    else if (GB_GetKey(SDLK_DOWN) == 1)
        dy = 1;

    if (mapX + dx < level_size &&
        mapX + dx >= 0)
        mapX += dx;
    if (mapY + dy < level_size &&
        mapY + dy >= 0)
        mapY += dy;

    /* VertBar_Position... ? */

    /* marking logic */

    if(GB_GetKey(SDLK_RCTRL) == 1) {    /* mark as isBomb */
    }
    else if(GB_GetKey(SDLK_RSHIFT) == 1) {   /* mark as isNotBomb */
    }

    /* this resets key presses? */
    GB_GetEvents();


    /* set movable object positions */
    Mattoc.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH);
    HitMattoc.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH);

    HorBar.GB_SetXY(PUZZLE_POSX-8,PUZZLE_POSY + mapY * CELLLENGTH-1);
    VertBar.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY-8);

    Erase.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH-5,PUZZLE_POSY + mapY * CELLLENGTH+10);
    EraseBlock.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH-5,PUZZLE_POSY + mapY * CELLLENGTH+10);

    Check.GB_SetXY(PUZZLE_POSX + mapX * CELLLENGTH,PUZZLE_POSY + mapY * CELLLENGTH+12);

    /* draw movable objects */
    if(hit == 0 && erase == 0 && check == 0 && hitcheck == 0) {
        Mattoc.GB_ShowSprite(0,(MattocShowFrame/2)%4);
        SDL_Delay(30);
        MattocShowFrame++;
    }

    /*

    if(hit == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);
        SDL_Delay(50);
        HitMattocShowFrame++;
        if(HitMattocShowFrame == 5) {
            hit = 0;
            HitMattocShowFrame = 0;
        }
    }


    if(erase == 1) {
        if(tempMap[mapY][mapX] == ' ') {
            EraseBlock.GB_ShowSprite(0,EraseBlockShowFrame);
            SDL_Delay(50);
            EraseBlockShowFrame++;
            if(EraseBlockShowFrame == 4) {
                erase = 0;
                EraseBlockShowFrame = 0;
            }
        } else {
            //	Erase.GB_ShowSprite(0,EraseShowFrame);
            //	SDL_Delay(50);
            //	EraseShowFrame++;
            //		if(hit == 1) {
            //			EraseShowFrame = 0;
            //			erase = 0;
            //		}
            //
            //		if(EraseShowFrame == 4) {
            //			erase = 0;
            //			EraseShowFrame = 0;
            //		}
            tempMap[mapY][mapX] = ' ';
        }
    }

    if(hitcheck == 1) {
        HitMattoc.GB_ShowSprite(0,HitMattocShowFrame);
        SDL_Delay(50);
        HitMattocShowFrame++;
        if(HitMattocShowFrame == 7) {
            hitcheck = 0;
            HitMattocShowFrame = 0;
            check = 1;
        }
    }

    if(check == 1) {
        Check.GB_ShowSprite(0,CheckShowFrame);
        SDL_Delay(40);
        CheckShowFrame++;
        if(CheckShowFrame == 6) {
            check = 0;
            CheckShowFrame = 0;
            tempMap[mapY][mapX] = 'X';
        }
    }

    HorBar.GB_ShowSprite(0,0);
    VertBar.GB_ShowSprite(0,0);

    if(check == 0 && hitcheck == 0 && erase == 0) GB_GetEvents();

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

    puzzleMap = {
        "##.#.#.###.#.#.",
        "#.#.#.#.#......",
        "###############",
        "#.#.#.#.#......",
        "###....##......",
        "#.#######......",
        "###....##......",
        "#.#....##......",
        "###....##......",
        "#.......#......",
        "#.#.#..........",
        "#.......#......",
        ".#.#...........",
        ".#.......#.....",
        "#.#.....#......"};

    level_size = 15;
    mapX = 0;
    mapY = 0;
    hit = 0;
    erase = 0;
    hitcheck = 0;
    check = 0;
    quit = 0;

    for (int i=0;i<level_size;i++)
        for (int j=0;j<level_size;j++)
            tempMap[i][j] = '.';

    MattocShowFrame = 0;
    HitMattocShowFrame = 0;
    EraseShowFrame = 0;
    CheckShowFrame = 0;
    EraseBlockShowFrame = 0;
}
Game::~Game() {}

void Game::DoMainLoop() {
    BG.GB_ShowBackground();
    DrawStreaks();
    DrawPuzzle();
    DrawMattoc();
}

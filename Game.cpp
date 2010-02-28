#include "Game.h"
#include <vector>
#include <sstream>
#include <iostream>

#define CELLLENGTH 12

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
                    Puzzle_PositionX-10*out.str().length()-5,
                    Puzzle_PositionY+i*CELLLENGTH-3);
    }

    /* draw col streaks */
    for (i=0;i<level_size;i++) {
        std::stringstream out;

        for (j=0;j<colStreaks[i].size();j++)
            out << colStreaks[i][j] << ' ';

        GB_DrawTextVert(out.str().c_str(),
                    Puzzle_PositionX+i*CELLLENGTH-4,
                    Puzzle_PositionY-10*out.str().length()-5);
    }
}

void Game::DrawPuzzle() {

    FIFTEEN.GB_SetXY(Puzzle_PositionX,Puzzle_PositionY);
    FIFTEEN.GB_ShowSprite(0,0);

    for(int yy=0;yy<level_size;yy++) {
        for(int xx=0;xx<level_size;xx++) {

        // Kika in på låtsaskartan vart vi har slagit in
        // klossen och kika ifall vi träffat rätt

            if(tempMap[yy][xx] == '#') {
                PushedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                PushedBlock.GB_ShowSprite(0,0);
            }

            if(tempMap[yy][xx] == 'X') {
                CheckedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                CheckedBlock.GB_ShowSprite(0,0);
            }
        }
    }
}

void Game::DrawMattoc() {
	int	newx, newy, newvert_x, newhor_y, newhit;

		if(GB_GetKey(SDLK_LEFT) == 1) {
			if(Mattoc_PositionX != Puzzle_PositionX) {
				newx = Mattoc_PositionX-12;
				mapX = mapX--;
			}
			else newx = Mattoc_PositionX;
			if(VertBar_PositionX != Puzzle_PositionX) newvert_x = Mattoc_PositionX-12;
			else newvert_x = Mattoc_PositionX;
			Mattoc_PositionX = newx;
			VertBar_PositionX = newvert_x;
		}

		if(GB_GetKey(SDLK_RIGHT) == 1) {
			if(Mattoc_PositionX != Puzzle_PositionX+level_size*12-12) {
				newx = Mattoc_PositionX+12;
				mapX = mapX++;

			}
			else newx = Mattoc_PositionX;
			if(VertBar_PositionX != Puzzle_PositionX+level_size*12-12) newvert_x = Mattoc_PositionX+12;
                        else newvert_x = Mattoc_PositionX-1;
			Mattoc_PositionX = newx;
			VertBar_PositionX = newvert_x;
		}

		if(GB_GetKey(SDLK_UP) == 1) {
			if(Mattoc_PositionY != Puzzle_PositionY-12) {
				newy = Mattoc_PositionY-12;
				mapY = mapY--;
			}
			else newy = Mattoc_PositionY;
			if(HorBar_PositionY != Puzzle_PositionY) newhor_y = Mattoc_PositionY;
			else newhor_y = Mattoc_PositionY+12;
			Mattoc_PositionY = newy;
			HorBar_PositionY = newhor_y;
		}

		if(GB_GetKey(SDLK_DOWN) == 1) {
			if(Mattoc_PositionY != Puzzle_PositionY+level_size*12-28) {
				newy = Mattoc_PositionY+12;
				mapY = mapY++;
			}
			else newy = Mattoc_PositionY;
			if(HorBar_PositionY != Puzzle_PositionY+level_size-12) newhor_y = Mattoc_PositionY+12;
			else newhor_y = Mattoc_PositionY+12;
			Mattoc_PositionY = newy;
			HorBar_PositionY = newhor_y;
		}

		if(GB_GetKey(SDLK_RCTRL) == 1 && !GB_GetKey(SDLK_RSHIFT)) {
			for(int i=0;i<level_size;i++) {
				realX = Puzzle_PositionX+mapX*12;
				realY = Puzzle_PositionY+mapY*12;
				if(puzzleMap[mapY][mapX] != '#') {

					if(tempMap[mapY][mapX] == '#') {
						tempMap[mapY][mapX] = ' ';
						break;
					} else {
						tempMap[mapY][mapX] = '#';
						break;
					}

				} else {
					if(tempMap[mapY][mapX] == '#') {
						tempMap[mapY][mapX] = ' ';
						break;
					} else {
						tempMap[mapY][mapX] = '#';
						break;
					}
				}
			}

			if(tempMap[mapY][mapX] != '#') 	erase = 1;
			else if(puzzleMap[mapY][mapX] != '#') {
				hitcheck = 1;
				tempMap[mapY][mapX] = '#';
			} else hit = 1;
            GB_GetEvents();
		}

		if(GB_GetKey(SDLK_RSHIFT) == 1 && !GB_GetKey(SDLK_RCTRL)) {
			if (tempMap[mapY][mapX] == 'X') erase = 1;
			else if (tempMap[mapY][mapX] != 'X') check = 1;
            GB_GetEvents();
		}

	Mattoc.GB_SetXY(Mattoc_PositionX,Mattoc_PositionY);
	HorBar.GB_SetXY(Puzzle_PositionX-8,HorBar_PositionY-1);
	VertBar.GB_SetXY(VertBar_PositionX,Puzzle_PositionY-8);
	HitMattoc.GB_SetXY(Mattoc_PositionX-20,Mattoc_PositionY-12);
	Erase.GB_SetXY(Mattoc_PositionX-5,Mattoc_PositionY+10);
	EraseBlock.GB_SetXY(Mattoc_PositionX-5,Mattoc_PositionY+10);
	Check.GB_SetXY(Mattoc_PositionX,Mattoc_PositionY+12);

	if(hit == 0 && erase == 0 && check == 0 && hitcheck == 0) {
        Mattoc.GB_ShowSprite(0,(MattocShowFrame/2)%4);
        SDL_Delay(30);
        MattocShowFrame++;
	}

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

    Puzzle_PositionX = 117;
    Puzzle_PositionY = 107;
    Mattoc_PositionX = Puzzle_PositionX;
    Mattoc_PositionY = Puzzle_PositionY;
    VertBar_PositionX = Puzzle_PositionX;
    HorBar_PositionY = Puzzle_PositionY;
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

void Game::DoMainLoop() {
    BG.GB_ShowBackground();
    DrawStreaks();
    DrawPuzzle();
    DrawMattoc();
}

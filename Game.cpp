#include "Game.h"

#define LEVEL 10

void Game::CalcPuzzle(int level) {
        int rows, i, j, x, y, col[100][20], col_len[100]; char row[100][100];
        char s[10];

        int level_size = 0;

	// Definera storleken på pusslet - 5x5, 10x10, 15x15

        if(level >= 1) level_size = 5;
        if(level >= 5) level_size = 10;
        if(level >= 10) level_size = 15;

        // Kalkylera horisontellt
	// puzzleMap = char med pussel, se Levels.cpp

        for(i=0;i<level_size;i++) {
            int cnt = 0;
            char *p=row[i];
            for(j=0;j<=level_size;j++) {
                if (j<level_size && puzzleMap[i][j]=='#') {
                    cnt++;
                }
                else if (cnt) {
                    if (cnt>=10) *p++=cnt/10+'0';
                    *p++=cnt%10+'0';
                    cnt=0;
                }
                *p=0;
            }
        }

        // Kalkylera vertikalt

        for(i=0;i<level_size;i++) {
            col_len[i]=0; // antalet tal i den här kolumnen
            int cnt=0;
            for(j=0;j<=level_size;j++) {
                if (j<level_size && puzzleMap[j][i]=='#') cnt++;
                else if (cnt) {
                       col[i][col_len[i]++]=cnt;
                        cnt=0;
                }
            }
        }

        // Fixa till vertikalt och skriv ut

        for(i=0;i<level_size;i++) {
            if (!col_len[i]) col[i][col_len[i]++]=0;

            for(j=0;j<col_len[i];j++) {
                char *p=s;

                if (col[i][j]>=10) *p++=col[i][j]/10+'0';

                *p++=col[i][j]%10+'0';
                *p=0;
                if (col[i][j]>=10) {
                    x=Puzzle_PositionX+i*12-9;
                } else {
                    x=Puzzle_PositionX+i*12-3;
                }

                y=Puzzle_PositionY+j*12-col_len[i]*12-12;

                // TODO: Kolla ifall col[] innehåller nummer större än 10,
                // flytta numret aningen åt vänster och siffrorna ihop

                GB_DrawText(s, x, y);
            }
        }

        // Om en rad är helt tom, skriv ut 0

        for(i=0;i<level_size;i++) {
            if (!row[i][0]) { row[i][0]='0'; row[i][1]=0; }
        }

        // Skriv ut horizontellt pussel


	for(i=0;i<level_size;i++) {
	// Om innehållet i row[] innehåller nummer som är större än 10,
	// skriv ut siffrorna närmre varandra -- Omvandla row till int för
	// att kika

		GB_DrawText(("%s\n",row[i]),Puzzle_PositionX-10*strlen(row[i])-12,Puzzle_PositionY+i*12-3);
	}
}

void Game::DrawPuzzle(int level) {
    int level_size = 0;

        // Rita ut alla block
	// Räkna ut vilken level det är och rita sedan ut bakgrund och nät

	if(level >= 10)
	{
		FIFTEEN.GB_SetXY(Puzzle_PositionX,Puzzle_PositionY);
		FIFTEEN.GB_ShowSprite(0,0);
	}

    for(int yy=0;yy<level_size;yy++) {
        for(int xx=0;xx<level_size;xx++) {

        // Kika in på låtsaskartan vart vi har slagit in
        // klossen och kika ifall vi träffat rätt

            if(TEMPMAP[yy][xx] == '#') {
                PushedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                PushedBlock.GB_ShowSprite(0,0);
            }

            if(TEMPMAP[yy][xx] == 'X') {
                CheckedBlock.GB_SetXY(Puzzle_PositionX+xx*12,Puzzle_PositionY+yy*12);
                CheckedBlock.GB_ShowSprite(0,0);
            }
        }
    }
}

void Game::DrawMattoc(int level) {
	int	newx, newy, newvert_x, newhor_y, newhit;

        if(level >= 1) level_size = 5;
        if(level >= 5) level_size = 10;
        if(level >= 10) level_size = 15;

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

					if(TEMPMAP[mapY][mapX] == '#') {
						TEMPMAP[mapY][mapX] = ' ';
						break;
					} else {
						TEMPMAP[mapY][mapX] = '#';
						break;
					}

				} else {
					if(TEMPMAP[mapY][mapX] == '#') {
						TEMPMAP[mapY][mapX] = ' ';
						break;
					} else {
						TEMPMAP[mapY][mapX] = '#';
						break;
					}
				}
			}

			if(TEMPMAP[mapY][mapX] != '#') 	erase = 1;
			else if(puzzleMap[mapY][mapX] != '#') {
				hitcheck = 1;
				TEMPMAP[mapY][mapX] = '#';
			} else hit = 1;
            GB_GetEvents();
		}

		if(GB_GetKey(SDLK_RSHIFT) == 1 && !GB_GetKey(SDLK_RCTRL)) {
			if (TEMPMAP[mapY][mapX] == 'X') erase = 1;
			else if (TEMPMAP[mapY][mapX] != 'X') check = 1;
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
        if(TEMPMAP[mapY][mapX] == ' ') {
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
            TEMPMAP[mapY][mapX] = ' ';
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
			TEMPMAP[mapY][mapX] = 'X';
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
       "## # # ### # # ",
       "# # # # #      ",
       "###############",
       "# # # # #      ",
       "###    ##      ",
       "# #######      ",
       "###    ##      ",
       "# #    ##      ",
       "###    ##      ",
       "#       #      ",
       "# # #          ",
       "#       #      ",
       " # #           ",
       " #       #     ",
       "# #     #      ",
       "# #     #      "};

    Puzzle_PositionX = 117;
    Puzzle_PositionY = 107;
    Mattoc_PositionX = Puzzle_PositionX;
    Mattoc_PositionY = Puzzle_PositionY;
    VertBar_PositionX = Puzzle_PositionX;
    HorBar_PositionY = Puzzle_PositionY;
    level_size = 0;
    mapX = 0;
    mapY = 0;
    hit = 0;
    erase = 0;
    hitcheck = 0;
    check = 0;
    cnt = 0;
    quit = 0;

    MattocShowFrame = 0;
    HitMattocShowFrame = 0;
    EraseShowFrame = 0;
    CheckShowFrame = 0;
    EraseBlockShowFrame = 0;
}

void Game::DoMainLoop() {
    BG.GB_ShowBackground();
    CalcPuzzle(LEVEL);
    DrawPuzzle(LEVEL);
    DrawMattoc(LEVEL);
}

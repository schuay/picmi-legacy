#include "GameBlade.h"

// My own includes

#include "Variables.cpp"
#include "Levels.cpp"
#include "Puzzle.cpp"

void DrawMattoc(int level) {
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
				if(puzz_3[mapY][mapX] != '#') {

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
			else if(puzz_3[mapY][mapX] != '#') {
				hitcheck = 1;
				TEMPMAP[mapY][mapX] = '#';
			} else hit = 1;	
		GB_GetEvents();
		}

		if(GB_GetKey(SDLK_RSHIFT) == 1 && !GB_GetKey(SDLK_RCTRL)) {
			if(TEMPMAP[mapY][mapX] == 'X') erase = 1;
			else if(TEMPMAP[mapY][mapX] != 'X') check = 1;
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

int intro(void) {
double i;

Start.GB_SetXY(100,100);

Start.GB_ShowSprite(0,0);

}

int main(void) {

	// Initiate audio, video and the text

	GB_SetupSDL_Video();
	GB_SetupSDL_Audio();
	GB_LoadTextBitmap();
	
	char TEMPMAP[level_size][level_size];
	
	FOUR.GB_LoadSprite("gfx/FOUR.bmp",1);
	TEN.GB_LoadSprite("gfx/TEN.BMP",1);	
	SIXTEEN.GB_LoadSprite("gfx/FIFTEEN-grid.bmp",1);
	SIXTEEN.GB_SetColorKey(255,0,255);

	Block.GB_LoadSprite("gfx/block.bmp", 1);
	Block.GB_SetColorKey(255,0,255);
	PushedBlock.GB_LoadSprite("gfx/pushed_block.bmp", 1);
	CheckedBlock.GB_LoadSprite("gfx/checked_block.bmp",1);
	
	HorBar.GB_LoadSprite("gfx/horcursor.bmp", 1);       // Load horizontal bar
//	HorBar.GB_SetAlpha(100);
	HorBar.GB_SetColorKey(255,0,255);
	
	VertBar.GB_LoadSprite("gfx/vertcursor.bmp", 1);       // Load vertical bar
//	VertBar.GB_SetAlpha(100);
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

	Title.GB_LoadSprite("gfx/title.bmp", 1);

 	Start.GB_LoadSprite("gfx/start.bmp", 1, 6);
	Start.GB_SetColorKey(255,0,255);
//	Start.GB_EnableSmoothing();

	BG.GB_LoadBackground("gfx/FIFTEEN.bmp");

 	Quit.GB_LoadSprite("gfx/quit.bmp", 1, 5);
	Quit.GB_SetColorKey(255,0,255);
	Quit.GB_SetXY(486,400);



	Black.GB_LoadSprite("gfx/black.bmp", 1);

	Bip.GB_LoadSound("sfx/bip.wav");
	Hit.GB_LoadSound("sfx/hit.wav");

	animatestart = 1;
	animatequit = 0;

	while(!GB_QuitEvent() && !GB_GetKey(SDLK_ESCAPE)) {
		GB_ClearScreen();



		if(startlir == 1) {
			BG.GB_ShowBackground();
			CalcPuzzle(10);
			DrawPuzzle(10);

			DrawMattoc(10);

		} else {

		startlir = 1;

		}


		SDL_Flip(Screen);
		GB_WaitFrame();
	}

	GB_Quit();

	return 0;
}

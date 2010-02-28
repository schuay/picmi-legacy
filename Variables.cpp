#ifndef VARIABLES
#define VARIABLES

#include "GB_Sprites.h"

int             Puzzle_PositionX = 117, Puzzle_PositionY = 107,
		Mattoc_PositionX = Puzzle_PositionX,
		Mattoc_PositionY = Puzzle_PositionY,
                VertBar_PositionX = Puzzle_PositionX,
		HorBar_PositionY = Puzzle_PositionY,

		Locked_X, Locked_Y,
		plane,
                level, level_size = 0, mapX = 0, mapY = 0, realX, realY,
                miss, hit = 0, erase = 0, hitcheck = 0, check = 0,
		cnt = 0, startlir = 0, start = 0, quit = 0, direction = 0,
		animatestart, animatequit,
		count, tempcount, done;
char            TEMPMAP[15][16];
unsigned char   MattocShowFrame = 0, HitMattocShowFrame = 0,
		EraseShowFrame = 0, CheckShowFrame = 0,
		EraseBlockShowFrame = 0,
		StartShowFrame = 0, QuitShowFrame = 0;

GB_Sprite Black;
GB_Background BG;

GB_Sprite FOUR, TEN, SIXTEEN;

GB_Sprite Block;
GB_Sprite PushedBlock;
GB_Sprite CheckedBlock;

GB_Sprite Mattoc;
GB_Sprite HitMattoc;
GB_Sprite Erase;
GB_Sprite EraseBlock;
GB_Sprite Check;

GB_Sprite HorBar;
GB_Sprite VertBar;

GB_Sprite Start;
GB_Sprite Quit;
GB_Sprite Title;

GB_Sound Bip;
GB_Sound Hit;

#endif

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "GameBlade.h"
#include "Game.h"

int main(void) {

    Game game;
    game.Initialize();  /* initialize video/audio subsystems, load sprites, etc... */

        while(!game.GetQuit()) {
		GB_ClearScreen();

		game.DoMainLoop();

		SDL_Flip(Screen);
		GB_WaitFrame();
	}

	GB_Quit();

	return 0;
}


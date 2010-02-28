#include "GameBlade.h"
#include "Game.h"

int main(void) {

    Game game;
    game.Initialize();  /* initialize video/audio subsystems, load sprites, etc... */

	while(!GB_QuitEvent() && !GB_GetKey(SDLK_ESCAPE)) {
		GB_ClearScreen();

		game.DoMainLoop();

		SDL_Flip(Screen);
		GB_WaitFrame();
	}

	GB_Quit();

	return 0;
}


/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_gamemanager.h"
namespace BoardGame {
void GameManager::GameOver() {

    painter->Paint();

    SDL_Delay(1000);

    /* empty event loop, then wait for user input */
    SDL_Event ev;
    while (SDL_PollEvent(&ev) == 1) {}

    while (!game->Quit) {
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_QUIT)
            game->Quit = true;
    }
}

void GameManager::MainLoop() {

    while (!game->Quit) {
        inputhandler->HandleInput();
        painter->Paint();

        SDL_Delay(30);  /* relinquish cpu time we don't need */

        if (game->GameLost())
            GameOver();
        else if (game->GameWon())
            GameOver();
    }

    /* BEGIN TEMP CODE for stats tests */
    StatsManager m;
    boost::shared_ptr<StatsElement> e(game->GetStats());
    m.Add(e);

    printf("\n"
           "Games played: %u\n"
           "Games won: %u\n"
           "Games lost: %u\n"
           "Games aborted: %u\n",
           m.GetPlayedCount(e->Type()),
           m.GetWonCount(e->Type()),
           m.GetLostCount(e->Type()),
           m.GetAbortedCount(e->Type()));

    if (e->resolution == GR_WON)
        printf("\n"
               "Rank: %u\n",
               m.GetRankInCurrentCat());

    m.Write();
    /* END TEMP CODE */
}

void GameManager::InitSystems() {
    if (SDL_Init(SDL_INIT_VIDEO) == -1 )
        throw Exception(SDL_GetError());

    SDL_WM_SetCaption(WINDOWCAPTION, NULL);
}
void GameManager::Initialize(BoardSettings &s) {

    InitSystems();

    /* create game objects */
    if (s.GameType == GT_PICROSS) {
        game = new Picross(s);
        painter = new PicPainter(game, s);
        inputhandler = new PicInputHandler(game);
    }
    else if (s.GameType == GT_MINESWEEPER) {
        game = new Sweeper(s);
        painter = new SweepPainter(game, s);
        inputhandler = new SweepInputHandler(game);
    }
}

GameManager::GameManager() {
    game = NULL;
    painter = NULL;
    inputhandler = NULL;
}
GameManager::~GameManager() {
    if (game)
        delete game;
    if (painter)
        delete painter;
    if (inputhandler)
        delete inputhandler;

    SDL_Quit();
}
}

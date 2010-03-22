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
void GameManager::GameWon() {

    SDL_Delay(1000);

    /* empty event loop, then wait for user input */
    SDL_Event ev;
    while (SDL_PollEvent(&ev) == 1) {}

    while (!game->Quit) {
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_QUIT)
            game->Quit = true;
    }

    printf("\n-----------------------------\n\n"
           "Game solved in %u s!\n\n"
           "------------------------------\n",
           game->GetElapsedTime());
}

void GameManager::MainLoop() {

    while (!game->Quit) {
        inputhandler->HandleInput();
        painter->Paint();

        SDL_Delay(30);  /* relinquish cpu time we don't need */

        if (game->GameWon())
            GameWon();
    }
}

void GameManager::InitSystems() {
    if (SDL_Init(SDL_INIT_VIDEO) == -1 )
        throw Exception(SDL_GetError());

    SDL_WM_SetCaption(WINDOWCAPTION, NULL);
}

GameManager::GameManager(BoardSettings &s) {
    game = NULL;
    painter = NULL;
    inputhandler = NULL;

    InitSystems();

    //TEMP
    s.GameType = BoardSettings::Minesweeper;
    s.Difficulty = 10;

    /* create game objects */
    if (s.GameType == BoardSettings::Picross) {
        game = new Picross(s);
        painter = new PicPainter(game, s.BackgroundPath);
        inputhandler = new PicInputHandler(game);
    }
    else if (s.GameType == BoardSettings::Minesweeper) {
        game = new Sweeper(s);
        painter = new SweepPainter(game, s.BackgroundPath);
        inputhandler = new SweepInputHandler(game);
    }
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

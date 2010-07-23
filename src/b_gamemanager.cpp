/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#include "b_gamemanager.h"

namespace BoardGame {

void GameManager::GameOver() {

    /* paint final game state */
    painter->Paint();

    /* load and write stats */
    StatsManager m;
    m.Add(game->GetStats());
    m.Write();

    /* empty event loop */
//    SDL_Event ev;
//    while (SDL_PollEvent(&ev) == 1) {}

//    /* display stats */
//    painter->PaintGameOverScreen(m.AggregateStats());

//    /* wait for user input */
//    while (true) {
//        SDL_WaitEvent(&ev);
//        if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_r) {
//            retry = true;
//            break;
//        }
//        else if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_QUIT)
//            break;
//    }
}

void GameManager::MainLoop() {

    while (!game->GetQuit()) {
        inputhandler->HandleInput();
        painter->Paint();

        game->GameLost();   /* todo: merge these and give them a reasonable name */
        game->GameWon();    /* they now set game.quit automatically */

        sf::Sleep(0.030f);
    }

    GameOver();
}

void GameManager::InitSystems() {

    app.reset(new sf::RenderWindow());

}
void GameManager::Initialize(BoardSettings &s) {

    InitSystems();

    retry = false;

    /* create game objects */
    if (s.GameType == GT_PICROSS) {
        game.reset(new Picross(s));
        painter.reset(new PicPainter(app, game, s));
        inputhandler.reset(new PicInputHandler(app, game));
    }
//    else if (s.GameType == GT_MINESWEEPER) {
//        game.reset(new Sweeper(s));
//        painter.reset(new SweepPainter(app, game, s));
//        inputhandler.reset(new SweepInputHandler(app, game));
//    }
}

}

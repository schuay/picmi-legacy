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
    sf::Event ev;
    while (app->pollEvent(ev)) { }

    /* display stats */
    painter->PaintGameOverScreen(m.AggregateStats());

    /* wait for user input */
    while (true) {
        app->waitEvent(ev);

        if (ev.type == sf::Event::KeyPressed ||
            ev.type == sf::Event::MouseButtonPressed ||
            ev.type == sf::Event::Closed)
            break;
    }

    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::R)
        retry = true;
}

void GameManager::MainLoop() {

    while (!game->GetQuit()) {
        inputhandler->HandleInput();
        painter->Paint();

        game->DetectAndHandleGameOver();

        sf::sleep(sf::seconds(0.030f));
    }

    GameOver();
}

void GameManager::Initialize(BoardSettings &s) {

    app.reset(new sf::RenderWindow());

    /* create game objects */
    if (s.GameType == GT_PICROSS) {
        game.reset(new Picross(s));
        painter.reset(new PicPainter(app, game, s));
    }
    else if (s.GameType == GT_MINESWEEPER) {
        game.reset(new Sweeper(s));
        painter.reset(new SweepPainter(app, game, s));
    }
}
void GameManager::PrepareGame(BoardSettings &s) {

    retry = false;

    if (s.GameType == GT_PICROSS) {
        game.reset(new Picross(s));
        inputhandler.reset(new PicInputHandler(app, game));
    }
    else if (s.GameType == GT_MINESWEEPER) {
        game.reset(new Sweeper(s));
        inputhandler.reset(new SweepInputHandler(app, game));
    }

    painter->ResetGame(game);
}

}

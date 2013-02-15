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

#include "b_painter.h"

namespace BoardGame {

    Painter::Painter(shared_ptr<sf::RenderWindow> &application) {

        app = application;

    }

    void Painter::LoadCustomBackground(std::string path) {
    
        sprBackground.Load( path, 0);

    }

    void Painter::PaintBackground() {

        sprBackground.Blit(app, sf::Vector2i(0,0));

    }

    void Painter::InitSystems() {

        app->create(sf::VideoMode(nativeWidth, nativeHeight), WINDOWTITLE);

        sf::VideoMode mode = sf::VideoMode::getDesktopMode();

        app->setPosition(sf::Vector2i((mode.width - nativeWidth) / 2, (mode.height - nativeHeight) / 2));

    }

    void Painter::PaintGameOverScreen(StatsCollection c) {

        /* clone original state of screen */

        sf::Texture tex;
        tex.update(*app.get());

        sf::Sprite originalScreen(tex);
        originalScreen.setScale(nativeWidth / (float)tex.getSize().x, nativeHeight / (float)tex.getSize().y);

        /* construct a shade overlay */

        sf::RectangleShape shadeOverlay = sf::RectangleShape(sf::Vector2f(nativeWidth, nativeHeight));
        shadeOverlay.setFillColor(sf::Color::Black);



        std::string infoText = GetGameOverText(c);

        sf::Vector2i p( nativeWidth / 2, (nativeHeight - txt.HeightOf(infoText)) / 2);

        /* fade in text overlay over 100 frames */
        for (int i = 1; i < 100; i++) {

            /* check for user input during fade to allow early fade abort */
            /* ugly because 'painter' shouldn't know about input..  */
            /* necessary because game over has its own loop within the main loop.. this should be fixed sometime */
            sf::Event ev;
            while (app->pollEvent(ev))
                if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::MouseButtonPressed || ev.type == sf::Event::Closed)
                    return;

            shadeOverlay.setFillColor(sf::Color(255, 255, 255, i * 2));

            app->draw(originalScreen);
            app->draw(shadeOverlay);
            txt.Blit(app, infoText, p, sf::Color(255, 255, 255, (( i * 127 ) / 100) * 2 ), FT_NORMAL, TJ_CENTER);

            app->display();
        }
    }
    void Painter::PaintPauseScreen() {

        sf::Vector2i p(nativeWidth / 2, nativeHeight / 2);

        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(nativeWidth, nativeHeight));
        rect.setFillColor(sf::Color::Black);
        app->draw(rect);

        txt.Blit(app, "PAUSED (press p to continue)", p, sf::Color::White, FT_BOLD, TJ_CENTER);
    }
}

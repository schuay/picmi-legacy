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

        app->Create(sf::VideoMode(nativeWidth, nativeHeight), WINDOWTITLE);

        sf::VideoMode mode = sf::VideoMode::GetDesktopMode();

        app->SetPosition((mode.Width - nativeWidth) / 2, (mode.Height - nativeHeight) / 2);

    }

    void Painter::PaintGameOverScreen(StatsCollection c) {

        /* clone original state of screen */

        sf::Image img;
        img.CopyScreen(*app.get());

        sf::Sprite originalScreen(img);
        originalScreen.SetScale(nativeWidth / (float)img.GetWidth(), nativeHeight / (float)img.GetHeight());

        /* construct a shade overlay */

        sf::Shape shadeOverlay = sf::Shape::Rectangle(
                0, 0, nativeWidth, nativeHeight, sf::Color::Black);



        std::string infoText = GetGameOverText(c);

        sf::Vector2i p( nativeWidth / 2, (nativeHeight - txt.HeightOf(infoText)) / 2);

        /* fade in text overlay over 100 frames */
        for (int i = 1; i < 100; i++) {

            /* check for user input during fade to allow early fade abort */
            /* ugly because 'painter' shouldn't know about input..  */
            /* necessary because game over has its own loop within the main loop.. this should be fixed sometime */
            sf::Event ev;
            while (app->PollEvent(ev))
                if (ev.Type == sf::Event::KeyPressed || ev.Type == sf::Event::MouseButtonPressed || ev.Type == sf::Event::Closed)
                    return;

            shadeOverlay.SetColor(sf::Color(255, 255, 255, i * 2));

            app->Draw(originalScreen);
            app->Draw(shadeOverlay);
            txt.Blit(app, infoText, p, sf::Color(255, 255, 255, (( i * 127 ) / 100) * 2 ), FT_NORMAL, TJ_CENTER);

            app->Display();
        }
    }
    void Painter::PaintPauseScreen() {

        sf::Vector2i p(nativeWidth / 2, nativeHeight / 2);

        app->Draw(sf::Shape::Rectangle(
                0, 0, nativeWidth, nativeHeight, sf::Color::Black));

        txt.Blit(app, "PAUSED (press p to continue)", p, sf::Color::White, FT_BOLD, TJ_CENTER);
    }
}

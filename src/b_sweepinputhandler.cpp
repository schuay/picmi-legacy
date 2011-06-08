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

#include "b_sweepinputhandler.h"
namespace BoardGame {
    SweepInputHandler::SweepInputHandler(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p) :
            InputHandler(application)
    {
        game = dynamic_cast<Sweeper*>(p.get());

        if (!game)
            throw Exception("Game object not set");
    }

    int SweepInputHandler::HandleMouseEvent(int x, int y, sf::Mouse::Button btn, sf::Event::EventType event) {

        sf::Vector2f mousePos = app->ConvertCoords(x, y);

        sf::Vector2i newLocation(
                (mousePos.x - game->PixOffsetX()) / game->CellLength(),
                (mousePos.y - game->PixOffsetY()) / game->CellLength());

        /* only handle mouse events in game board area */
        if (!game->IsInBounds(newLocation))
            return OP_NONE;

        game->TrySetLocation(newLocation);

        if (event == sf::Event::MouseMoved)
            return OP_NONE;

        if (btn == sf::Mouse::Left)
            return S_OP_EXPOSE;
        else if (btn == sf::Mouse::Right)
            return S_OP_MARK;
        else if (btn == sf::Mouse::Middle)
            return S_OP_TENTATIVE;

        return OP_NONE;
    }
    void SweepInputHandler::HandleInput() {
        sf::Event ev;

        while (app->PollEvent(ev)) {
            int dx = 0, dy = 0, op = OP_NONE;

            /* get input... */

            switch (ev.Type) {
            case sf::Event::KeyPressed:
                switch (ev.Key.Code) {
                case sf::Key::Escape:
                    game->SetResolution(GR_ABORTED);
                    break;
                case sf::Key::P:
                    game->SetPaused(!game->GetPaused());
                    break;
                case sf::Key::Num7:
                case sf::Key::Y:
                    dx = -1;
                    dy = -1;
                    break;
                case sf::Key::Num9:
                case sf::Key::U:
                    dx = 1;
                    dy = -1;
                    break;
                case sf::Key::Num1:
                case sf::Key::B:
                    dx = -1;
                    dy = 1;
                    break;
                case sf::Key::Num3:
                case sf::Key::N:
                    dx = 1;
                    dy = 1;
                    break;
                case sf::Key::Num4:
                case sf::Key::H:
                case sf::Key::A:
                case sf::Key::Left:
                    dx = -1;
                    break;
                case sf::Key::Num6:
                case sf::Key::L:
                case sf::Key::D:
                case sf::Key::Right:
                    dx = 1;
                    break;
                case sf::Key::Num8:
                case sf::Key::K:
                case sf::Key::W:
                case sf::Key::Up:
                    dy = -1;
                    break;
                case sf::Key::Num2:
                case sf::Key::J:
                case sf::Key::S:
                case sf::Key::Down:
                    dy = 1;
                    break;
                case sf::Key::Num5:
                case sf::Key::LControl:
                case sf::Key::RControl:
                    op = S_OP_MARK;
                    break;
                case sf::Key::Num0:
                case sf::Key::Space:
                    op = S_OP_EXPOSE;
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                op = HandleMouseEvent(ev.MouseButton.X, ev.MouseButton.Y, ev.MouseButton.Button, ev.Type);
                break;
            case sf::Event::MouseMoved:
                op = HandleMouseEvent(ev.MouseMove.X, ev.MouseMove.Y, sf::Mouse::Left, ev.Type);
                break;
            case sf::Event::Closed:
                game->SetResolution(GR_ABORTED);
                break;
            default:
                break;
            }

            /* perform actual logic... */

            if (dx || dy)
                game->TrySetLocationRel(dx, dy);

            if (op != OP_NONE)
                game->DoOp(op);
        }
    }
}

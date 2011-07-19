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

        if (!game) {
            throw Exception("Game object not set");
        }

        dragHelper.setLockToLine(false);
    }

    int SweepInputHandler::HandleMouseEvent(int x, int y, sf::Mouse::Button btn, sf::Event::EventType event) {

        sf::Vector2f mousePos = app->ConvertCoords(x, y);
        sf::Vector2i newLocation(
                (mousePos.x - game->PixOffsetX()) / game->CellLength(),
                (mousePos.y - game->PixOffsetY()) / game->CellLength());
        int op = S_OP_NONE;

        /* only handle mouse events in game board area */
        if (!game->IsInBounds(newLocation)) {
            return S_OP_NONE;
        }

        if (btn == sf::Mouse::Left) {
            op = S_OP_EXPOSE;
        } else if (btn == sf::Mouse::Right) {
            op = S_OP_MARK;
        } else if (btn == sf::Mouse::Middle) {
            op = S_OP_TENTATIVE;
        }

        switch (event) {
        case sf::Event::MouseButtonPressed:
            dragHelper.begin(newLocation, btn, op);
            break;
        case sf::Event::MouseMoved:
            if (btn == sf::Mouse::Right) {    /* only run drag logic if a mousebutton is pressed, otherwise only set location */
                newLocation = dragHelper.update(newLocation);
                if (dragHelper.nothingTobeDone()) {
                    return S_OP_NONE;
                }
            } else {
                op = S_OP_NONE;
            }
            break;
        default:
            break;
        }

        game->TrySetLocation(newLocation);

        return op;
    }
    void SweepInputHandler::HandleInput() {
        sf::Event ev;

        while (app->PollEvent(ev)) {
            int dx = 0, dy = 0, op = OP_NONE;

            /* get input... */

            switch (ev.Type) {
            case sf::Event::KeyPressed:
                switch (ev.Key.Code) {
                case sf::Keyboard::Escape:
                    game->SetResolution(GR_ABORTED);
                    break;
                case sf::Keyboard::P:
                    game->SetPaused(!game->GetPaused());
                    break;
                case sf::Keyboard::Num7:
                case sf::Keyboard::Y:
                    dx = -1;
                    dy = -1;
                    break;
                case sf::Keyboard::Num9:
                case sf::Keyboard::U:
                    dx = 1;
                    dy = -1;
                    break;
                case sf::Keyboard::Num1:
                case sf::Keyboard::B:
                    dx = -1;
                    dy = 1;
                    break;
                case sf::Keyboard::Num3:
                case sf::Keyboard::N:
                    dx = 1;
                    dy = 1;
                    break;
                case sf::Keyboard::Num4:
                case sf::Keyboard::H:
                case sf::Keyboard::A:
                case sf::Keyboard::Left:
                    dx = -1;
                    break;
                case sf::Keyboard::Num6:
                case sf::Keyboard::L:
                case sf::Keyboard::D:
                case sf::Keyboard::Right:
                    dx = 1;
                    break;
                case sf::Keyboard::Num8:
                case sf::Keyboard::K:
                case sf::Keyboard::W:
                case sf::Keyboard::Up:
                    dy = -1;
                    break;
                case sf::Keyboard::Num2:
                case sf::Keyboard::J:
                case sf::Keyboard::S:
                case sf::Keyboard::Down:
                    dy = 1;
                    break;
                case sf::Keyboard::Num5:
                case sf::Keyboard::LControl:
                case sf::Keyboard::RControl:
                    op = S_OP_MARK;
                    break;
                case sf::Keyboard::Num0:
                case sf::Keyboard::Space:
                    op = S_OP_EXPOSE;
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                op = HandleMouseEvent(ev.MouseButton.X, ev.MouseButton.Y, ev.MouseButton.Button, ev.Type);
                break;
            case sf::Event::MouseButtonReleased:
                dragHelper.reset();
                break;
            case sf::Event::MouseMoved:
                op = HandleMouseEvent(ev.MouseMove.X, ev.MouseMove.Y, dragHelper.getButton(), ev.Type);
                break;
            case sf::Event::Closed:
                game->SetResolution(GR_ABORTED);
                break;
            default:
                break;
            }

            /* perform actual logic... */

            if (dx || dy) {
                game->TrySetLocationRel(dx, dy);
            }

            if (op != OP_NONE) {
                game->DoOp(op);
            }
        }
    }
}

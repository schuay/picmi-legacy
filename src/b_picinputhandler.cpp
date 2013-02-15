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

#include "b_picinputhandler.h"
namespace BoardGame {
PicInputHandler::PicInputHandler(shared_ptr<sf::RenderWindow> &application, shared_ptr<BoardGame> &p) :
        InputHandler(application)
{
    game = dynamic_cast<Picross*>(p.get());

    if (!game) {
        throw Exception("Game object not set");
    }
}

int PicInputHandler::HandleMouseEvent(int x, int y, const sf::Mouse::Button btn, const sf::Event::EventType event) {

    sf::Vector2f mousePos = app->convertCoords(sf::Vector2i(x, y));
    sf::Vector2i newLocation(
            (mousePos.x - game->PixOffsetX()) / game->CellLength(),
            (mousePos.y - game->PixOffsetY()) / game->CellLength());
    int op = OP_NONE;

    /* only handle mouse events in game board area */
    if (!game->IsInBounds(newLocation)) {
        return OP_NONE;
    }

    switch (event) {
    case sf::Event::MouseButtonPressed:
        if (btn == sf::Mouse::Left) {
            op = (game->GetStateAt(newLocation) == BOARD_CLEAN) ? OP_FORCE_HIT : OP_FORCE_HIT2CLEAR;
        } else if (btn == sf::Mouse::Right) {
            op = (game->GetStateAt(newLocation) == BOARD_CLEAN) ? OP_FORCE_MARK : OP_FORCE_MARK2CLEAR;
        }
        dragHelper.begin(newLocation, btn, op);
        break;
    case sf::Event::MouseMoved:
        if (btn == sf::Mouse::Left || btn == sf::Mouse::Right) {    /* only run drag logic if a mousebutton is pressed, otherwise only set location */
            newLocation = dragHelper.update(newLocation);
            if (dragHelper.nothingTobeDone()) {
                return OP_NONE;
            }
        }
        break;
    default:
        break;
    }

    game->TrySetLocation(newLocation);

    if (btn == sf::Mouse::Left || btn == sf::Mouse::Right) {
        return dragHelper.getOperation();
    }

    return OP_NONE;
}
void PicInputHandler::HandleInput() {
    sf::Event ev;

    while (app->pollEvent(ev)) {
        int dx = 0, dy = 0, op = OP_NONE;

        /* get input... */

        switch (ev.type) {
        case sf::Event::KeyPressed:
            switch (ev.key.code) {
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
            case sf::Keyboard::Num0:
            case sf::Keyboard::Space:
                op = OP_HIT;
                break;
            case sf::Keyboard::Num5:
            case sf::Keyboard::RControl:
            case sf::Keyboard::LControl:
                op = OP_MARK;
                break;
            case sf::Keyboard::Z:
                op = OP_UNDO;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            op = HandleMouseEvent(ev.mouseButton.x, ev.mouseButton.y, ev.mouseButton.button, ev.type);
            break;
        case sf::Event::MouseButtonReleased:
            dragHelper.reset();
            break;
        case sf::Event::MouseMoved:
            op = HandleMouseEvent(ev.mouseMove.x, ev.mouseMove.y, dragHelper.getButton(), ev.type);
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

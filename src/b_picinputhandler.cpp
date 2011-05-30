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

    if (!game)
        throw Exception("Game object not set");

    dragDirection = DRAG_UNDEF;
    dragOperation = DRAG_UNDEF;
    lmbPressed = false;
    rmbPressed = false;

}

int PicInputHandler::HandleMouseEvent(int x, int y, const sf::Mouse::Button btn, const sf::Event::EventType event) {

    sf::Vector2f mousePos = app->ConvertCoords(x, y);

    Point newLocation(
            (mousePos.x - game->PixOffsetX()) / game->CellLength(),
            (mousePos.y - game->PixOffsetY()) / game->CellLength());

    /* only handle mouse events in game board area */
    if (!game->IsInBounds(newLocation))
        return OP_NONE;

    switch (event) {
    case sf::Event::MouseButtonPressed:
        lastClickLocation = newLocation;    /* remember where the first click happened so we can limit movement to that row/column during mouse drags */
        dragDirection = DRAG_UNDEF;         /* reset drag direction */
        lastDragLocation = newLocation;     /* remember last handled tile so we only to a single op per tile on drags */

        if (btn == sf::Mouse::Left) {
            dragOperation = (game->GetStateAt(newLocation) == BOARD_CLEAN) ? OP_FORCE_HIT : OP_FORCE_HIT2CLEAR;
            lmbPressed = true;
        } else if (btn == sf::Mouse::Right) {
            dragOperation = (game->GetStateAt(newLocation) == BOARD_CLEAN) ? OP_FORCE_MARK : OP_FORCE_MARK2CLEAR;
            rmbPressed = true;
        }

        break;
    case sf::Event::MouseMoved:
        if (btn == sf::Mouse::Left || btn == sf::Mouse::Right) {    /* only run drag logic if a mousebutton is pressed, otherwise only set location */
            if ( newLocation != lastClickLocation && dragDirection == DRAG_UNDEF ) { /* calc drag direction */
                unsigned int diffX = abs(lastClickLocation.x - newLocation.x);
                unsigned int diffY = abs(lastClickLocation.y - newLocation.y);
                if (diffX < diffY)
                    dragDirection = DRAG_VER;
                else if (diffX > diffY)
                    dragDirection = DRAG_HOR;
                else
                    dragDirection = DRAG_HOR;
            }

            if (dragDirection == DRAG_HOR)   /* adjust newLocation according to dragDirection */
                newLocation.y = game->GetLocation().y;
            else if (dragDirection == DRAG_VER)
                newLocation.x = game->GetLocation().x;

            if (lastDragLocation == newLocation)
                return OP_NONE; /* tile already handled, nothing to be done */
            else {
                lastDragLocation = newLocation;
            }
        }
        break;
    default:
        break;
    }

    game->TrySetLocation(newLocation);

    if (btn == sf::Mouse::Left || btn == sf::Mouse::Right) {
        return dragOperation;
    }

    return OP_NONE;
}
void PicInputHandler::HandleInput() {
    sf::Event ev;
    sf::Mouse::Button btn;

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
            case sf::Key::Num0:
            case sf::Key::Space:
                op = OP_HIT;
                break;
            case sf::Key::Num5:
            case sf::Key::RControl:
            case sf::Key::LControl:
                op = OP_MARK;
                break;
            case sf::Key::Z:
                op = OP_UNDO;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            op = HandleMouseEvent(ev.MouseButton.X, ev.MouseButton.Y, ev.MouseButton.Button, ev.Type);
            break;
        case sf::Event::MouseButtonReleased:
            if (ev.MouseButton.Button == sf::Mouse::Left)
                lmbPressed = false;
            else if (ev.MouseButton.Button == sf::Mouse::Right)
                rmbPressed = false;
            break;
        case sf::Event::MouseMoved:;

            if (lmbPressed)
                btn = sf::Mouse::Left;
            else if (rmbPressed)
                btn = sf::Mouse::Right;
            else btn = sf::Mouse::ButtonCount;

            op = HandleMouseEvent(ev.MouseMove.X, ev.MouseMove.Y, btn, ev.Type);
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

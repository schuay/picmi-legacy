/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_INPUTHANDLER_H
#define B_INPUTHANDLER_H
namespace BoardGame {
class InputHandler
{
public:
    virtual void HandleInput() = 0;
};
}
#endif // B_INPUTHANDLER_H

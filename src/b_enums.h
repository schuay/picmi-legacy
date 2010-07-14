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

#ifndef B_ENUMS_H
#define B_ENUMS_H

enum FontTypeEnum {
    FT_NORMAL,
    FT_BOLD,
    FT_ITALIC
};

enum SpriteJustifyEnum {
    SJ_LEFTTOP,
    SJ_LEFTBOTTOM,
    SJ_RIGHTTOP,
    SJ_RIGHTBOTTOM
};

enum TextJustifyEnum {
    TJ_LEFT,
    TJ_CENTER,
    TJ_RIGHT
};

enum GameTypeEnum {
    GT_PICROSS,
    GT_MINESWEEPER,
    GT_TETRIS
};

enum GameResolutionEnum {
    GR_INPROGRESS,
    GR_ABORTED,
    GR_LOST,
    GR_WON
};

enum MovementDirectionEnum {
    MD_LEFT,
    MD_RIGHT,
    MD_DOWN,
    MD_UP
};

#endif // B_ENUMS_H

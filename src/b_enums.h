/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_ENUMS_H
#define B_ENUMS_H

enum GameTypeEnum {
    GT_PICROSS,
    GT_MINESWEEPER
};

enum GameResolutionEnum {
    GR_INPROGRESS,
    GR_ABORTED,
    GR_LOST,
    GR_WON
};

#endif // B_ENUMS_H

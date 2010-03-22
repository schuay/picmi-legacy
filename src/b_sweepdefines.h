/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPDEFINES_H
#define B_SWEEPDEFINES_H

#define S_MAP_NONE        0 /* map state defines for interfacing with frontends */
#define S_MAP_BOMB        9

#define S_BOARD_EXPOSED   0 /* board state defines for interfacing with frontends */
#define S_BOARD_EXPOSED_1 1
#define S_BOARD_EXPOSED_2 2
#define S_BOARD_EXPOSED_3 3
#define S_BOARD_EXPOSED_4 4
#define S_BOARD_EXPOSED_5 5
#define S_BOARD_EXPOSED_6 6
#define S_BOARD_EXPOSED_7 7
#define S_BOARD_EXPOSED_8 8
#define S_BOARD_CLEAN     9
#define S_BOARD_MARKED    10
#define S_BOARD_TENTATIVE 11

#define S_OP_NONE         0 /* defines for game actions, NONE */
#define S_OP_EXPOSE       1 /* uncover a tile */
#define S_OP_MARK         2 /* mark a bomb */
#define S_OP_TENTATIVE    3 /* tentative mark */

#endif // B_SWEEPDEFINES_H

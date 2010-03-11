/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_PICDEFINES_H
#define B_PICDEFINES_H

#define MAP_FALSE       0 /* map state defines for interfacing with frontends */
#define MAP_TRUE        1

#define BOARD_CLEAN     0 /* board state defines for interfacing with frontends */
#define BOARD_MARKED    1
#define BOARD_HIT       2

#define OP_NONE         0 /* defines for game actions, NONE, HIT (uncover a tile), MARK (mark a tile as empty) */
#define OP_HIT          1
#define OP_MARK         2

#define PUZ_RAND        1 /* defines for used puzzle type */
#define PUZ_STAT        0

#endif // B_PICDEFINES_H

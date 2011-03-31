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

#ifndef B_PICDEFINES_H
#define B_PICDEFINES_H

#define MAP_FALSE           0 /* map state defines for interfacing with frontends */
#define MAP_TRUE            1

#define BOARD_CLEAN         0 /* board state defines for interfacing with frontends */
#define BOARD_MARKED        1
#define BOARD_HIT           2

#define OP_NONE             0 /* defines for game actions, NONE, HIT (uncover a tile), MARK (mark a tile as empty) */
#define OP_HIT              1
#define OP_MARK             2
#define OP_FORCE_MARK2CLEAR 3 /* used for drag operation locking - only MARK -> CLEAR allowed */
#define OP_FORCE_MARK       4 /* used for drag operation locking - only CLEAR -> MARK allowed */
#define OP_UNDO             5
#define OP_FORCE_HIT        6 /* used for drag operation locking - only CLEAR -> HIT allowed */
#define OP_FORCE_HIT2CLEAR  7 /* used for drag operation locking - only HIT -> CLEAR allowed */

#endif // B_PICDEFINES_H

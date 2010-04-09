/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_STATSCOLLECTION_H
#define B_STATSCOLLECTION_H

#include "b_statselement.h"

namespace BoardGame {
    struct StatsCollection {

        unsigned int
                PlayedCount,
                WonCount,
                LostCount,
                AbortedCount,
                Rank,
                BestTime;
    };
}

#endif // B_STATSCOLLECTION_H

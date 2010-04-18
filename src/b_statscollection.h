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
        StatsCollection() {
            PlayedCount = 0;
            WonCount = 0;
            LostCount = 0;
            AbortedCount = 0;
            Rank = 0;
            BestTime = 0;
            CurrentTime = 0;

            for (int i = 0; i < 5; i++)
                Top5Time[i] = 0;
        }

        unsigned int
                PlayedCount,
                WonCount,
                LostCount,
                AbortedCount,
                Rank,
                BestTime,
                CurrentTime;

        unsigned int
                Top5Time[5];

        QDateTime
                Top5DateTime[5];

        GameResolutionEnum
                CurrentResolution;

        float WonPercentage() {
            return (PlayedCount == 0 ? 0.0f : WonCount * 100 / (float) PlayedCount);
        }
        float LostPercentage() {
            return (PlayedCount == 0 ? 0.0f : LostCount * 100 / (float) PlayedCount);
        }
        float AbortedPercentage() {
            return (PlayedCount == 0 ? 0.0f : AbortedCount * 100 / (float) PlayedCount);
        }
    };
}

#endif // B_STATSCOLLECTION_H

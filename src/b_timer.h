/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_PICTIMER_H
#define B_PICTIMER_H

#include <time.h>
namespace BoardGame {
class Timer
{
public:
    Timer();

    void Start();
    void Stop();

    void AddPenalty();

    unsigned int GetTime();
    unsigned int GetRealTime();
    unsigned int GetPenaltyTime();

private:
    bool
            started,
            stopped;

    unsigned int
            startTime,
            finishTime,
            penaltyTime,
            penaltyMultiplier;

    static const unsigned int
            basePenaltyTime = 120;
};
}
#endif // B_PICTIMER_H

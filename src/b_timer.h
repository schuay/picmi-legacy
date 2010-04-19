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
    void Pause(bool isPaused);

    void AddPenalty();

    unsigned int GetTime() const;
    unsigned int GetRealTime() const;
    unsigned int GetPenaltyTime() const;

private:
    bool
            started,
            stopped,
            paused;

    unsigned int
            startTime,
            finishTime,
            pauseTime,
            penaltyTime,
            penaltyMultiplier;

    static const unsigned int
            basePenaltyTime = 120;
};
}
#endif // B_PICTIMER_H

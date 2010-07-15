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

#ifndef B_PICTIMER_H
#define B_PICTIMER_H

#include <ctime>
#include <SDL/SDL.h>

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

    unsigned int GetTicks() const;

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

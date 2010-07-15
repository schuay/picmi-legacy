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

#include "b_timer.h"

namespace BoardGame {

Timer::Timer()
{
    started = false;
    stopped = false;
    paused = false;

    startTime = 0;
    finishTime = 0;
    pauseTime = 0;
    penaltyTime = 0;
    penaltyMultiplier = 1;
}

void Timer::Start() {
    startTime = time(NULL);
    started = true;
}
void Timer::Stop() {
    finishTime = time(NULL);
    stopped = true;
}
void Timer::Pause(bool isPaused) {
    if (isPaused == paused)
        return;

    if (isPaused) {
        paused = true;
        pauseTime += time(NULL) - startTime;
    }
    else {
        paused = false;
        startTime = time(NULL);
    }
}

void Timer::AddPenalty() {
    if (!stopped)
        penaltyTime += basePenaltyTime * penaltyMultiplier++;
}

unsigned int Timer::GetTime() const {
    if (!started)
        return 0;

    return GetRealTime() + penaltyTime;
}
unsigned int Timer::GetRealTime() const {

    if (!started)
        return 0;

    if (stopped)
        return finishTime - startTime + pauseTime;

    return time(NULL) - startTime + pauseTime;
}

unsigned int Timer::GetPenaltyTime() const {
    return penaltyTime;
}

unsigned int Timer::GetTicks() const {
    return SDL_GetTicks();
}

}

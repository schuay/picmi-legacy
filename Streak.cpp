#include "Streak.h"

Streak::Streak(unsigned int l)
{
    length = l;
    Solved = false;
}

unsigned int Streak::GetLength() {
    return length;
}

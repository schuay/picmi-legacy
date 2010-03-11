#include "b_picstreak.h"

PicStreak::PicStreak(unsigned int l)
{
    length = l;
    Solved = false;
}

unsigned int PicStreak::GetLength() {
    return length;
}

#include "b_picsettings.h"

PicSettings::PicSettings()
{
    /* set default values */
    Map = "";
    Path = "";

    Type = PUZ_RAND;
    Difficulty = 55;

    NoHintsMode = false;
    LoadRandomFromPath = false;

    x = 15;
    y = 15;
}

bool PicSettings::Validate() {
    if (Map.length() != x*y)
        return false;

    if (Type == PUZ_STAT && Path.length() == 0)
        return false;

    if (Type != PUZ_STAT && Type != PUZ_RAND)
        return false;

    if (Difficulty < 1 || Difficulty > 99)
        return false;

    return true;
}

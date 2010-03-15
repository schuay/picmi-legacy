/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PICSETTINGS_H
#define PICSETTINGS_H

#include <string>
#include <cstdlib>

#include "b_picdefines.h"

class PicSettings
{
public:
    PicSettings();
    bool Validate();

    std::string
            Map,
            Path;

    int
            Type,
            Difficulty;

    bool
            NoHintsMode,
            LoadRandomFromPath;

    unsigned int
            x,
            y;
};

#endif // PICSETTINGS_H

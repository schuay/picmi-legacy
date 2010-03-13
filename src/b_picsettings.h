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

#include "b_picdefines.h"

class PicSettings
{
public:
    PicSettings();

    std::string puzMap;

    std::string fileName;

    int puzType;
    int puzDifficulty;

    bool noHintsMode;

    unsigned int x;
    unsigned int y;
};

#endif // PICSETTINGS_H

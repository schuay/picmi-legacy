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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>

#include "b_picdefines.h"
#include "b_exception.h"

namespace BoardGame {
class BoardSettings
{
public:
    BoardSettings();
    bool Validate();
    void Load();
    void Save();

    std::string
            Map,
            PuzzlePath,
            BackgroundPath;

    int
            Type,
            Difficulty;

    bool
            NoHintsMode,
            LoadRandomFromPath;

    unsigned int
            x,
            y;

private:
    void CheckForConfDir();
    void HandleConfLine(std::string line);

    std::string
            basePath,
            defaultPuzzlePath,
            confFilePath;
};
}
#endif // PICSETTINGS_H

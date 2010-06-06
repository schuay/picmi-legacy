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
#include "b_enums.h"

namespace BoardGame {
class BoardSettings
{
public:
    BoardSettings(GameTypeEnum t);
    bool Validate() const;
    void Load();
    void Save();

    std::string
            Map,
            BackgroundPath;

    int
            Difficulty;

    bool
            NoHintsMode,
            UseCustomBG,
            EnableSolver;

    unsigned int
            x,
            y;

    GameTypeEnum GameType;

private:
    void CheckForConfDir();
    void HandleConfLine(const std::string line);

    void SetDefaultValues();
    static std::string TypeToStr(GameTypeEnum t) { if (t == GT_PICROSS) return "picross"; else return "minesweeper"; }

    std::string
            basePath,
            confFilePath;
};
}
#endif // PICSETTINGS_H

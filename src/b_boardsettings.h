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
    enum GameTypeEnum {
        Picross,
        Minesweeper
    };

    BoardSettings(GameTypeEnum t);
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

    GameTypeEnum GameType;

private:
    void CheckForConfDir();
    void HandleConfLine(const std::string line);

    void SetDefaultValues();
    static std::string TypeToStr(GameTypeEnum t) { if (t == Picross) return "picross"; else return "minesweeper"; }

    std::string
            basePath,
            defaultPuzzlePath,
            confFilePath;
};
}
#endif // PICSETTINGS_H

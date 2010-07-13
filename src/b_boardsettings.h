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
    static std::string TypeToStr(GameTypeEnum t) {
        switch (t) {
        case GT_PICROSS: return "picross";
        case GT_MINESWEEPER: return "minesweeper";
        case GT_TETRIS: return "tetris";
        default: throw Exception("Invalid game type specified.");
        }
    }

    std::string
            basePath,
            confFilePath;
};
}
#endif // PICSETTINGS_H

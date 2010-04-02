#include "b_boardsettings.h"
namespace BoardGame {
BoardSettings::BoardSettings(GameTypeEnum t)
{
    /* set default values */

    basePath = std::string(getenv("HOME")) + "/.config/tuxpicross/";
    confFilePath = basePath + TypeToStr(t) + ".conf";
    defaultPuzzlePath = basePath + "puzzles/";

    Map = "";
    PuzzlePath = defaultPuzzlePath;
    BackgroundPath = "";

    Type = PUZ_RAND;
    Difficulty = 55;

    NoHintsMode = false;
    LoadRandomFromPath = false;

    GameType = t;

    x = 15;
    y = 15;
}

bool BoardSettings::Validate() {
    if (Map.length() != x*y)
        return false;

    if (Type == PUZ_STAT && PuzzlePath.length() == 0)
        return false;

    if (Type != PUZ_STAT && Type != PUZ_RAND)
        return false;

    if (Difficulty < 1 || Difficulty > 99)
        return false;

    return true;
}

void BoardSettings::Load() {
    CheckForConfDir();

    std::ifstream read(confFilePath.c_str());
    if (!read.is_open())
        return;

    std::string line;
    while (!read.eof()) {
        getline(read,line);
        HandleConfLine(line);
    }

    read.close();
}
void BoardSettings::HandleConfLine(const std::string line) {

    /* skip empty lines */
    if (line.length() == 0)
        return;

    /* skip comment lines */
    if (line.substr(0,1) == "#")
        return;

    std::size_t pos = line.find("=");

    /* skip malformed lines */
    if (pos == std::string::npos ||
        pos == 0 ||
        pos == line.length() - 1)
        return;

    std::string
            settingType = line.substr(0, pos),
            settingValue = line.substr(pos + 1);

    try {
        if      (settingType == "PUZZLEPATH")
            PuzzlePath = settingValue;
        else if (settingType == "BGPATH")
            BackgroundPath = settingValue;
        else if (settingType == "TYPE")
            Type = atoi(settingValue.c_str());
        else if (settingType == "WIDTH")
            x = atoi(settingValue.c_str());
        else if (settingType == "HEIGHT")
            y = atoi(settingValue.c_str());
        else if (settingType == "DIFFICULTY")
            Difficulty = atoi(settingValue.c_str());
        else if (settingType == "NOHINTSMODE")
            NoHintsMode = atoi(settingValue.c_str());
        else if (settingType == "GAMETYPE")
            GameType = static_cast<BoardSettings::GameTypeEnum>(
                    atoi(settingValue.c_str()));
    }
    catch (std::exception) {
        printf("Invalid settings value, ignored. Setting type: %s, Setting value: %s ",
               settingType.c_str(), settingValue.c_str());
    }
}

void BoardSettings::Save() {
    CheckForConfDir();

    std::ofstream write(confFilePath.c_str());
    if (!write.is_open())
        throw Exception("Could not open conf file.");

    write << "# TUX PICROSS CONFIG FILE" << std::endl;
    write << "PUZZLEPATH=" << PuzzlePath << std::endl;
    write << "BGPATH=" << BackgroundPath<< std::endl;
    write << "TYPE=" << Type << std::endl;
    write << "WIDTH=" << x << std::endl;
    write << "HEIGHT=" << y << std::endl;
    write << "DIFFICULTY=" << Difficulty << std::endl;
    write << "NOHINTSMODE=" << NoHintsMode << std::endl;
    write << "GAMETYPE=" << GameType << std::endl;

    write.close();
}
void BoardSettings::CheckForConfDir() {

    DIR* d = opendir(basePath.c_str());

    if (!d) {
        int success = mkdir(basePath.c_str(), S_IRWXU);
        if (success != 0)
            throw Exception("Could not find or create default conf dir.");
    }
    else
        closedir(d);
}
}

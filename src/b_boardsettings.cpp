#include "b_boardsettings.h"
namespace BoardGame {
BoardSettings::BoardSettings(GameTypeEnum t)
{
    GameType = t;
    SetDefaultValues();
}

void BoardSettings::SetDefaultValues() {

    basePath = std::string(getenv("HOME")) + "/.config/picmi/";
    confFilePath = basePath + TypeToStr(GameType) + ".conf";

    UseCustomBG = false;
    EnableSolver = true;

    if (GameType == GT_PICROSS) {
        Map = "";
        BackgroundPath = "";

        Difficulty = 55;

        NoHintsMode = false;

        x = 15;
        y = 15;
    }
    else if (GameType == GT_MINESWEEPER) {
        Map = "";
        BackgroundPath = "";

        Difficulty = 20;

        NoHintsMode = false;

        x = 20;
        y = 20;
    }
}

bool BoardSettings::Validate() const {
    if (Map.length() != x*y)
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
        if (settingType == "BGPATH")
            BackgroundPath = settingValue;
        else if (settingType == "WIDTH")
            x = atoi(settingValue.c_str());
        else if (settingType == "HEIGHT")
            y = atoi(settingValue.c_str());
        else if (settingType == "DIFFICULTY")
            Difficulty = atoi(settingValue.c_str());
        else if (settingType == "NOHINTSMODE")
            NoHintsMode = atoi(settingValue.c_str());
        else if (settingType == "GAMETYPE")
            GameType = static_cast<GameTypeEnum>(
                    atoi(settingValue.c_str()));
        else if (settingType == "USECUSTOMBG")
            UseCustomBG = atoi(settingValue.c_str());
        else if (settingType == "ENABLESOLVER")
            EnableSolver = atoi(settingValue.c_str());
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

    write << "# PICMI CONFIG FILE" << std::endl;
    write << "BGPATH=" << BackgroundPath<< std::endl;
    write << "WIDTH=" << x << std::endl;
    write << "HEIGHT=" << y << std::endl;
    write << "DIFFICULTY=" << Difficulty << std::endl;
    write << "NOHINTSMODE=" << NoHintsMode << std::endl;
    write << "GAMETYPE=" << GameType << std::endl;
    write << "USECUSTOMBG=" << UseCustomBG << std::endl;
    write << "ENABLESOLVER=" << EnableSolver << std::endl;

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

#include "b_picsettings.h"

PicSettings::PicSettings()
{
    /* set default values */

    basePath = std::string(getenv("HOME")) + "/.config/tuxpicross/";
    confFilePath = basePath + "tuxpicross.conf";
    defaultPuzzlePath = basePath + "puzzles/";

    Map = "";
    PuzzlePath = defaultPuzzlePath;
    BackgroundPath = "";

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

    if (Type == PUZ_STAT && PuzzlePath.length() == 0)
        return false;

    if (Type != PUZ_STAT && Type != PUZ_RAND)
        return false;

    if (Difficulty < 1 || Difficulty > 99)
        return false;

    return true;
}

void PicSettings::Load() {
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
void PicSettings::HandleConfLine(std::string line) {

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
    }
    catch (std::exception) {
        printf("Invalid settings value, ignored. Setting type: %s, Setting value: %s ",
               settingType.c_str(), settingValue.c_str());
    }
}

void PicSettings::Save() {
    CheckForConfDir();

    std::ofstream write(confFilePath.c_str());
    if (!write.is_open())
        throw PicException("Could not open conf file.");

    write << "# TUX PICROSS CONFIG FILE" << std::endl;
    write << "PUZZLEPATH=" << PuzzlePath << std::endl;
    write << "BGPATH=" << BackgroundPath<< std::endl;
    write << "TYPE=" << Type << std::endl;
    write << "WIDTH=" << x << std::endl;
    write << "HEIGHT=" << y << std::endl;
    write << "DIFFICULTY=" << Difficulty << std::endl;
    write << "NOHINTSMODE=" << NoHintsMode << std::endl;

    write.close();
}
void PicSettings::CheckForConfDir() {

    DIR* d = opendir(basePath.c_str());

    if (!d) {
        int success = mkdir(basePath.c_str(), S_IRWXU);
        if (success != 0)
            throw PicException("Could not find or create default conf dir.");
    }
    else
        closedir(d);
}

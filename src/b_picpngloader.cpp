/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picpngloader.h"

PicPngLoader::PicPngLoader() { 
    std::string path = getenv("HOME");

    defaultPath = path + "/.config/tuxpicross/puzzles/";

    DIR* d = opendir(defaultPath.c_str());

    if (!d) {
        int success = mkdir(defaultPath.c_str(), S_IRWXU);
        if (success != 0)
            throw PicException("Could not create directory " + defaultPath);
    }
    else
        closedir(d);
}
PicPngLoader::PicPngLoader(std::string defpath) {

    defaultPath = defpath;

    DIR* d = opendir(defpath.c_str());

    if (!d) {
        int success = mkdir(defpath.c_str(), S_IRWXU);
        if (success != 0)
            throw PicException("Could not create directory " + defpath);
    }
    else
        closedir(d);
}

void PicPngLoader::Convert(std::string path, std::string filename, int threshold) {

    std::string fullfilename = path + "/" + filename;
    std::string newfilename = defaultPath + "/" + filename;

    Magick::Image img(fullfilename.c_str());
    Magick::Image imgCopy(img);     /* copy the image right away to make sure we don't modify the original */


    Magick::Color white("white");

    imgCopy.backgroundColor(white); /* white background (for transparent images) */
    imgCopy.opacity(0);             /* remove transparency */
    imgCopy.threshold(threshold);   /* set threshold from which to turn pixels white */

    imgCopy.write(newfilename);
}
void PicPngLoader::ConvertPath(std::string path, int threshold) {

    DIR* d = opendir(path.c_str());
    struct dirent *ep;

    if (!d)
        throw PicException("Dir could not be opened");

    while ( (ep = readdir(d)) ) {
        if (ep->d_type != DT_REG)
            continue;

        std::string filename = ep->d_name;
        int l = filename.length();

        if (l < 5)      /* we need at least 5 chars to store extension + name */
            continue;

        std::string ext = filename.substr(filename.length() - 4, 4);

        if (ext != ".png" && ext != ".xbm")  /* for now, limit to png (even though we could process all formats) */
            continue;

        Convert(path, filename, threshold);
    }

    closedir(d);
}

void PicPngLoader::Load(BoardSettings& settings) {

    Magick::Image img(settings.PuzzlePath.c_str());

    unsigned int
            w = img.columns(),
            h = img.rows();

    std::string Map = "";
    Magick::ColorMono currentPixel;
    bool currentColor;

    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < w; j++) {
            currentPixel = img.pixelColor(j,i);
            currentColor = currentPixel.mono();
            if (currentColor)
                Map += PIC_MAP_FALSE;
            else
                Map += PIC_MAP_TRUE;
        }
    }

    settings.Type = PUZ_STAT;
    settings.Map = Map;
    settings.x = w;
    settings.y = w;
}
void PicPngLoader::LoadRandom(BoardSettings &settings) {
    DIR* d = opendir(settings.PuzzlePath.c_str());
    struct dirent *ep;

    if (!d)
        throw PicException("Dir could not be opened");

    std::vector<std::string> v;

    while ( (ep = readdir(d)) ) {
        if (ep->d_type != DT_REG)
            continue;

        std::string filename = ep->d_name;
        int l = filename.length();

        if (l < 5)      /* we need at least 5 chars to store extension + name */
            continue;

        std::string ext = filename.substr(filename.length() - 4, 4);

        if (ext != ".png" && ext != ".xbm")  /* for now, limit to png (even though we could process all formats) */
            continue;

        v.push_back(settings.PuzzlePath + "/" + filename);
    }

    closedir(d);

    if (v.size() == 0)
        throw PicException("No files found in directory");

    srand(time(NULL));

    settings.PuzzlePath = v[rand() % v.size()];
    settings.LoadRandomFromPath = false;

    Load(settings);
}

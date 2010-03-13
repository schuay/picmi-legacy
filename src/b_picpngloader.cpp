/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picpngloader.h"

PicPngLoader::PicPngLoader(std::string defpath) {
    /* TODO: remember defaultpath, if it doesn't exist create it */

    defaultPath = defpath;
}

void PicPngLoader::ConvertPNG(std::string path, std::string filename, int threshold) {

    std::string fullfilename = path + "/" + filename;
    std::string newfilename = defaultPath + filename;

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

    while (ep = readdir(d)) {
        if (ep->d_type != DT_REG)
            continue;

        std::string filename = ep->d_name;
        int l = filename.length();

        if (l < 5)      /* we need at least 5 chars to store extension + name */
            continue;

        std::string ext = filename.substr(filename.length() - 4, 4);

        if (ext != ".png" && ext != ".xbm")  /* for now, limit to png (even though we could process all formats) */
            continue;

        ConvertPNG(path, filename, threshold);
    }

    closedir(d);
}

PicSettings PicPngLoader::LoadPicross(std::string filename) {

    std::string fullfilename = defaultPath + filename;

    Magick::Image img(fullfilename.c_str());

    unsigned int
            w = img.columns(),
            h = img.rows();

    std::string Map = "";
    Magick::ColorMono currentPixel;
    bool currentColor;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            currentPixel = img.pixelColor(j,i);
            currentColor = currentPixel.mono();
            if (currentColor)
                Map += '#'; /* TODO: convert this to use the same variable as Picross class MAP_TRUE mapTrue */
            else
                Map += '.'; /* TODO: convert this to use the same variable as Picross class MAP_FALSE mapFalse */
        }
    }

    PicSettings s;
    s.puzType = PUZ_STAT;
    s.puzMap = Map;
    s.x = w;
    s.y = w;

    return s;
}

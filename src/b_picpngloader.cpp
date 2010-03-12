/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picpngloader.h"

PicPngLoader::PicPngLoader() {}

Picross* PicPngLoader::LoadPNG(std::string filename, int threshold) {

    Magick::Image img(filename.c_str());
    Picross *p = NULL;
    unsigned int w, h;

    w = img.columns();
    h = img.rows();

    Magick::Image imgCopy(img);

    Magick::Color white("white");

    imgCopy.backgroundColor(white);
    imgCopy.opacity(50);
    imgCopy.threshold(30000);
    imgCopy.write("newImg.png");

    return p;
}

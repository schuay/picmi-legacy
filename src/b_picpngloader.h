/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_PICPNGLOADER_H
#define B_PICPNGLOADER_H

#include <ImageMagick/Magick++.h>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "b_picsettings.h"
#include "b_picexception.h"

#define PIC_MAP_FALSE '.'   //these defines exist because i haven't figured out how
#define PIC_MAP_TRUE '#'    //picpngloader and picross should relate

class PicPngLoader
{
public:
    PicPngLoader();
    PicPngLoader(std::string defpath);

    /* load a png image, use threshold to convert to black+white */
    void ConvertPNG(std::string path, std::string filename, int threshold);
    void ConvertPath(std::string path, int threshold);

    void LoadPicross(PicSettings& settings);
private:

    std::string defaultPath;
};

#endif // B_PICPNGLOADER_H

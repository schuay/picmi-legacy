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
#include <ImageMagick/Magick++/Color.h>
#include <ImageMagick/Magick++/Image.h>
#include <string>

#include "b_picross.h"

class PicPngLoader
{
public:
    PicPngLoader();

    /* load a png image, use threshold to convert to black+white */
    Picross *LoadPNG(std::string filename, int threshold);
};

#endif // B_PICPNGLOADER_H

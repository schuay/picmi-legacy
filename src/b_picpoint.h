/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef POINT_H
#define POINT_H

class PicPoint
{
public:
    PicPoint();
    PicPoint(PicPoint *p);
    PicPoint(unsigned int _x, unsigned int _y);

    bool operator==(PicPoint const &p);
    bool operator!=(PicPoint const &p);
    PicPoint& operator=(PicPoint const &rhs);

    unsigned int
            x,
            y;
};

#endif // POINT_H

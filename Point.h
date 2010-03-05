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

class Point
{
public:
    Point();
    Point(unsigned int _x, unsigned int _y);

    bool operator==(Point const &p);
    bool operator!=(Point const &p);
    Point& operator=(Point const &rhs);

    unsigned int
            x,
            y;
};

#endif // POINT_H

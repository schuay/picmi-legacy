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

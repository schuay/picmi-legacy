/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef STREAK_H
#define STREAK_H
namespace BoardGame {
class PicStreak
{
public:
    PicStreak(unsigned int l);

    unsigned int GetLength() const { return length; }
    bool Solved;

private:
    unsigned int length;
};
}
#endif // STREAK_H

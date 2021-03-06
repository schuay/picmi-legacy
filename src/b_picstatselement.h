/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#ifndef B_PICSTATSELEMENT_H
#define B_PICSTATSELEMENT_H

#include "b_statselement.h"

namespace BoardGame {
class PicStatsElement : public StatsElement
{
public:
    PicStatsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    unsigned int
            nrOfBoxes;

    virtual GameTypeEnum Type() const { return GT_PICROSS; }

    virtual unsigned int Difficulty() const { return (nrOfBoxes * 100) / (height * width); }
    virtual float Efficiency() const { return nrOfBoxes / (float)playedTime; }

    virtual QString TypeStr() const { return "PicStatisticsElement"; }
    static QString ClassToStr() { return "PicStatisticsElement"; }
};
}

#endif // B_PICSTATSELEMENT_H

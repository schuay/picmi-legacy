/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
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

    virtual unsigned int Difficulty() const { return nrOfBoxes / (height * width); }
    virtual float Efficiency() const { return nrOfBoxes / (float)playedTime; }

    virtual QString TypeStr() const { return "PicStatisticsElement"; }
    static QString ClassToStr() { return "PicStatisticsElement"; }
};
}

#endif // B_PICSTATSELEMENT_H

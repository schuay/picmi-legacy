/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_SWEEPSTATISTICSELEMENT_H
#define B_SWEEPSTATISTICSELEMENT_H

#include "b_statselement.h"

namespace BoardGame {
class SweepStatsElement : public StatsElement
{
public:
    SweepStatsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    unsigned int
            totalBombCount,
            markedBombCount;

    virtual GameTypeEnum Type() const { return GT_MINESWEEPER; }

    virtual unsigned int Difficulty() const { return (totalBombCount * 100) / (height * width); }
    virtual float Efficiency() const { return totalBombCount / (float)playedTime; }

    virtual QString TypeStr() const { return "SweepStatisticsElement"; }
    static QString ClassToStr() { return "SweepStatisticsElement"; }
};
}

#endif // B_SWEEPSTATISTICSELEMENT_H

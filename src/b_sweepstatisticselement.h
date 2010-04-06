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

#include "b_statisticselement.h"

class SweepStatisticsElement : public StatisticsElement
{
public:
    SweepStatisticsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    unsigned int
            totalBombCount,
            markedBombCount;

    virtual QString type() const { return "SweepStatisticsElement"; }
    static QString ClassToStr() { return "SweepStatisticsElement"; }
};

#endif // B_SWEEPSTATISTICSELEMENT_H

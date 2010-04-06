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

#include "b_statisticselement.h"

class PicStatsElement : public StatisticsElement
{
public:
    PicStatsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    unsigned int
            nrOfBoxes;

    virtual QString type() const { return "PicStatisticsElement"; }
    static QString ClassToStr() { return "PicStatisticsElement"; }
};

#endif // B_PICSTATSELEMENT_H

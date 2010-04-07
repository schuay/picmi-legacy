/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweepstatselement.h"

namespace BoardGame {
SweepStatsElement::SweepStatsElement() :
        StatsElement()
{
    totalBombCount = 0;
    markedBombCount = 0;
}

void SweepStatsElement::FromXml(QDomElement node) {
    StatsElement::FromXml(node);

    totalBombCount = node.attribute("totalBombCount", "0").toInt();
    markedBombCount = node.attribute("markedBombCount", "0").toInt();
}

QXmlStreamAttributes SweepStatsElement::ToXml() {

    StatsElement::ToXml();

    QString name, val;

    name = "totalBombCount";
    val.setNum(totalBombCount);
    attributes.append(name, val);

    name = "markedBombCount";
    val.setNum(markedBombCount);
    attributes.append(name, val);

    return attributes;
}
}

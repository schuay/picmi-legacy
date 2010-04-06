/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_sweepstatisticselement.h"

SweepStatisticsElement::SweepStatisticsElement() :
        StatisticsElement()
{
    totalBombCount = 0;
    markedBombCount = 0;
}

void SweepStatisticsElement::FromXml(QDomElement node) {
    StatisticsElement::FromXml(node);

    totalBombCount = node.attribute("totalBombCount", "0").toInt();
    markedBombCount = node.attribute("markedBombCount", "0").toInt();
}

QXmlStreamAttributes SweepStatisticsElement::ToXml() {

    StatisticsElement::ToXml();

    QString name, val;

    name = "totalBombCount";
    val.setNum(totalBombCount);
    attributes.append(name, val);

    name = "markedBombCount";
    val.setNum(markedBombCount);
    attributes.append(name, val);

    return attributes;
}

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

void SweepStatisticsElement::FromXml(QXmlStreamAttributes attributes) {
    StatisticsElement::FromXml(attributes);

    for (int i = 0; i < attributes.count(); i++) {
        QXmlStreamAttribute a = attributes.at(i);

        if (a.name() == "totalBombCount")
            totalBombCount = a.value().toString().toInt();
        else if (a.name() == "markedBombCount")
            markedBombCount = a.value().toString().toInt();
    }
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

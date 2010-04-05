/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_statisticselement.h"

StatisticsElement::StatisticsElement()
{
    width = 0;
    height = 0;

    difficulty = 0;

    playedTime = 0;
    resolution = GR_ABORTED;
}

void StatisticsElement::FromXml(QXmlStreamAttributes attributes) {
    for (int i = 0; i < attributes.count(); i++) {
        QXmlStreamAttribute a = attributes.at(i);

        if (a.name() == "width")
            width = a.value().toString().toInt();
        else if (a.name() == "height")
            height = a.value().toString().toInt();
        else if (a.name() == "difficulty")
            difficulty = a.value().toString().toInt();
        else if (a.name() == "playedTime")
            playedTime = a.value().toString().toInt();
        else if (a.name() == "resolution")
            resolution = static_cast<GameResolutionEnum>(a.value().toString().toInt());
    }

}
QXmlStreamAttributes StatisticsElement::ToXml() {

    attributes.clear();

    QString name, val;

    name = "width";
    val.setNum(width);
    attributes.append(name, val);

    name = "height";
    val.setNum(height);
    attributes.append(name, val);

    name = "difficulty";
    val.setNum(difficulty);
    attributes.append(name, val);

    name = "playedTime";
    val.setNum(playedTime);
    attributes.append(name, val);

    name = "resolution";
    val.setNum(resolution);
    attributes.append(name, val);

    return attributes;
}

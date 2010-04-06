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

    playedTime = 0;
    resolution = GR_ABORTED;
}

void StatisticsElement::FromXml(QDomElement node) {
    width = node.attribute("width","0").toInt();
    height = node.attribute("height","0").toInt();
    playedTime = node.attribute("playedTime","0").toInt();
    resolution = static_cast<GameResolutionEnum>(node.attribute("resolution","0").toInt());
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

    name = "playedTime";
    val.setNum(playedTime);
    attributes.append(name, val);

    name = "resolution";
    val.setNum(resolution);
    attributes.append(name, val);

    return attributes;
}

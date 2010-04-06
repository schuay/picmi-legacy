/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picstatselement.h"

PicStatsElement::PicStatsElement()
{
    nrOfBoxes = 0;
}

void PicStatsElement::FromXml(QDomElement node) {
    StatsElement::FromXml(node);

    nrOfBoxes = node.attribute("nrOfBoxes", "0").toInt();
}

QXmlStreamAttributes PicStatsElement::ToXml() {

    StatsElement::ToXml();

    QString name, val;

    name = "nrOfBoxes";
    val.setNum(nrOfBoxes);
    attributes.append(name, val);

    return attributes;
}

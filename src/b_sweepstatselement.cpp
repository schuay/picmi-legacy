/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

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

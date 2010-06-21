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

#include "b_picstatselement.h"

namespace BoardGame {
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
}

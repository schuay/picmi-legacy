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

#include "b_statselement.h"

namespace BoardGame {
StatsElement::StatsElement() : dateFormat("yyyyMMddhhmm")
{
    width = 0;
    height = 0;

    playedTime = 0;
    resolution = GR_ABORTED;

    datetime = QDateTime::currentDateTime();
}

void StatsElement::FromXml(QDomElement node) {
    width = node.attribute("width","0").toInt();
    height = node.attribute("height","0").toInt();
    playedTime = node.attribute("playedTime","0").toInt();
    resolution = static_cast<GameResolutionEnum>(node.attribute("resolution","0").toInt());
    datetime = QDateTime::fromString(
            node.attribute("datetime", QDateTime::currentDateTime().toString(dateFormat)), dateFormat);
}
QXmlStreamAttributes StatsElement::ToXml() {

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

    name = "datetime";
    val = datetime.toString(dateFormat);
    attributes.append(name, val);

    return attributes;
}
}

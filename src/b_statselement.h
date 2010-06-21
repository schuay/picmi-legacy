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

#ifndef B_STATISTICSELEMENT_H
#define B_STATISTICSELEMENT_H

#include <QtXml/QXmlStreamAttributes>
#include <QtXml/QDomDocument>
#include <QDateTime>
#include <string>

#include "b_enums.h"

namespace BoardGame {
class StatsElement
{
public:
    StatsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    QDateTime
            datetime;

    unsigned int
            width,
            height;

    unsigned int
            playedTime;

    GameResolutionEnum
            resolution;

    virtual unsigned int Difficulty() const = 0;
    virtual float Efficiency() const = 0;

    virtual GameTypeEnum Type() const = 0;

    virtual QString TypeStr() const { return "StatisticsElement"; }
    static QString ClassToStr() { return  "StatisticsElement"; }

protected:
    QXmlStreamAttributes attributes;

    const QString dateFormat;
};
}
#endif // B_STATISTICSELEMENT_H

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_STATISTICSELEMENT_H
#define B_STATISTICSELEMENT_H

#include <QtXml/QXmlStreamAttributes>
#include <QtXml/QDomDocument>
#include <QDateTime>
#include <string>

#include "b_enums.h"

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

    virtual QString type() const { return "StatisticsElement"; }
    static QString ClassToStr() { return  "StatisticsElement"; }

protected:
    QXmlStreamAttributes attributes;

    const QString dateFormat;
};

#endif // B_STATISTICSELEMENT_H

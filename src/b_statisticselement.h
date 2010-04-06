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
#include <string>

#include "b_enums.h"

class StatisticsElement
{
public:
    StatisticsElement();

    virtual void FromXml(QDomElement node);
    virtual QXmlStreamAttributes ToXml();

    unsigned int
            width,
            height;

    unsigned int
            difficulty;

    unsigned int
            playedTime;

    GameResolutionEnum
            resolution;

    virtual QString type() const { return "StatisticsElement"; }
    static QString ClassToStr() { return  "StatisticsElement"; }

protected:
    QXmlStreamAttributes attributes;
};

#endif // B_STATISTICSELEMENT_H

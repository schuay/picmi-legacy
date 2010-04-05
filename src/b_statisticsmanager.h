/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef B_STATISTICSMANAGER_H
#define B_STATISTICSMANAGER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <QtXml/QXmlStreamReader>
#include <QtXml/QXmlStreamWriter>
#include <QFile>

#include "b_statisticselement.h"
#include "b_sweepstatisticselement.h"

class StatisticsManager
{
public:
    StatisticsManager();

    void Read();
    void Write();
    void Add(boost::shared_ptr<StatisticsElement> e);
private:
    std::vector<boost::shared_ptr<StatisticsElement> > elements;
    QString filePath;
};

#endif // B_STATISTICSMANAGER_H

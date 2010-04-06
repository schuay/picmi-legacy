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
#include <QtXml/QDomDocument>
#include <QtXml/QXmlStreamWriter>
#include <QFile>

#include "b_statselement.h"
#include "b_sweepstatselement.h"

class StatsManager
{
public:
    StatsManager();

    void Read();
    void Write() const;
    void Add(boost::shared_ptr<StatsElement> e);
private:
    std::vector<boost::shared_ptr<StatsElement> > elements;
    QString filePath;
};

#endif // B_STATISTICSMANAGER_H

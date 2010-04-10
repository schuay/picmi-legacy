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

#include "b_picstatselement.h"
#include "b_sweepstatselement.h"
#include "b_exception.h"
#include "b_statscollection.h"

using boost::shared_ptr;

namespace BoardGame {
class StatsManager
{
public:
    StatsManager();

    void Write() const;
    void Add(shared_ptr<StatsElement> e);


    /* aggregate stats (of type matching latestElement) */
    StatsCollection AggregateStats() const;
    
    /* all InCurrentCat functions are based on the type, dimensions, and difficulty
     * of latestElement */

    shared_ptr<StatsElement> /* fastest time within won games */
            GetBestByTimeInCurrentCat() const;

private:
    void Load();

    std::vector<shared_ptr<StatsElement> > elements;
    shared_ptr<StatsElement> latestElement;  /* the most recently added element (= the just completed game) */

    QString filePath;
};
}
#endif // B_STATISTICSMANAGER_H

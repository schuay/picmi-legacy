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

namespace BoardGame {
class StatsManager
{
public:
    StatsManager();

    void Write() const;
    void Add(boost::shared_ptr<StatsElement> e);


    /* stat aggregation functions

       most of the time we will probably use all of them at once, which is inefficient because each
       function loops through all elements -> rewrite them into one function that returns struct?

       additionally, we probably don't want to return a pointer (BestByTime, BestByEfficiency)
     */

    unsigned int /* total count of played games of type t */
            GetPlayedCount(GameTypeEnum t) const;

    unsigned int /* total count of won games of type t */
            GetWonCount(GameTypeEnum t) const;

    unsigned int /* total count of lost games of type t */
            GetLostCount(GameTypeEnum t) const;

    unsigned int /* total count of aborted games of type t */
            GetAbortedCount(GameTypeEnum t) const;


    /* all InCurrentCat functions are based on the type, dimensions, and difficulty
     * of latestElement */

    unsigned int /* rank is calculated by time and only counts won games */
            GetRankInCurrentCat() const;

    boost::shared_ptr<StatsElement> /* fastest time within won games */
            GetBestByTimeInCurrentCat() const;

    boost::shared_ptr<StatsElement>  /* highest efficiency within won games */
            GetBestByEfficiencyInCurrentCat() const;

private:
    void Load();

    std::vector<boost::shared_ptr<StatsElement> > elements;
    boost::shared_ptr<StatsElement> latestElement;  /* the most recently added element (= the just completed game) */

    QString filePath;
};
}
#endif // B_STATISTICSMANAGER_H

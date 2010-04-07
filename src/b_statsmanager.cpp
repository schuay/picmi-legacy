/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_statsmanager.h"

namespace BoardGame {
StatsManager::StatsManager()
{
    filePath = QString(getenv("HOME")) + "/.config/picmi/stats";

    Load();
}

void StatsManager::Load() {
    if (latestElement || elements.size() != 0)
        throw Exception("Stats may only be read once and before Add is called.");

    QFile inFile(filePath);
    inFile.open(QIODevice::ReadOnly);

    QDomDocument xml("stats");

    if (!xml.setContent(&inFile)) {
        inFile.close();
        return;
    }

    inFile.close();

    QDomNode node = xml.firstChild().nextSibling().firstChild();

    while (!node.isNull()) {
        QDomElement el = node.toElement();

        boost::shared_ptr<StatsElement> e;

        if (el.tagName() == PicStatsElement::ClassToStr())
            e.reset(new PicStatsElement);
        else if (el.tagName() == SweepStatsElement::ClassToStr())
            e.reset(new SweepStatsElement);

        if (e) {
            e->FromXml(el);
            Add(e);
        }

        node = node.nextSibling();
    }
}
void StatsManager::Write() const {
    QFile outFile(filePath);
    outFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml(&outFile);

    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("picmi");
    for (unsigned int i = 0; i < elements.size(); i++) {
        xml.writeStartElement(elements.at(i)->TypeStr());
        xml.writeAttributes(elements.at(i)->ToXml());
        xml.writeEndElement();
    }
    xml.writeEndElement();
    xml.writeEndDocument();

    outFile.close();
}

void StatsManager::Add(boost::shared_ptr<StatsElement> e) {
    elements.push_back(e);
    latestElement = e;
}

unsigned int StatsManager::GetPlayedCount(GameTypeEnum t) const {
    unsigned int playedCount = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements.at(i)->Type() == t)
            playedCount++;

    return playedCount;
}
unsigned int StatsManager::GetWonCount(GameTypeEnum t) const {
    unsigned int wonCount = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements.at(i)->Type() == t && elements.at(i)->resolution == GR_WON)
            wonCount++;

    return wonCount;
}
unsigned int StatsManager::GetLostCount(GameTypeEnum t) const {
    unsigned int lostCount = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements.at(i)->Type() == t && elements.at(i)->resolution == GR_LOST)
            lostCount++;

    return lostCount;
}
unsigned int StatsManager::GetAbortedCount(GameTypeEnum t) const {
    unsigned int abortedCount = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
        if (elements.at(i)->Type() == t && elements.at(i)->resolution == GR_ABORTED)
            abortedCount++;

    return abortedCount;
}
unsigned int StatsManager::GetRankInCurrentCat() const {
    unsigned int rank = 1;

    if (!latestElement)
        return 0;

    if (latestElement->resolution != GR_WON)
        return 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        boost::shared_ptr<StatsElement> e(elements.at(i));
        if (e != latestElement &&
            e->resolution   == GR_WON &&
            e->Type()       == latestElement->Type() &&
            e->height       == latestElement->height &&
            e->width        == latestElement->width &&
            e->Difficulty() == latestElement->Difficulty() &&
            e->playedTime    < latestElement->playedTime)
            rank++;
    }

    return rank;
}
boost::shared_ptr<StatsElement> StatsManager::GetBestByTimeInCurrentCat() const {
    unsigned int bestIndex = 0;

    if (!latestElement)
        return boost::shared_ptr<StatsElement>();

    for (unsigned int i = 0; i < elements.size(); i++) {
        boost::shared_ptr<StatsElement> e(elements.at(i));
        if (e->resolution   == GR_WON &&
            e->Type()       == latestElement->Type() &&
            e->height       == latestElement->height &&
            e->width        == latestElement->width &&
            e->Difficulty() == latestElement->Difficulty() &&
            e->playedTime < elements.at(bestIndex)->playedTime)
            bestIndex = i;
    }

    boost::shared_ptr<StatsElement> best(elements.at(bestIndex));

    return best;
}
boost::shared_ptr<StatsElement> StatsManager::GetBestByEfficiencyInCurrentCat() const {
    unsigned int bestIndex = 0;

    if (!latestElement)
        return boost::shared_ptr<StatsElement>();

    for (unsigned int i = 0; i < elements.size(); i++) {
        boost::shared_ptr<StatsElement> e(elements.at(i));
        if (e->resolution   == GR_WON &&
            e->Type()       == latestElement->Type() &&
            e->height       == latestElement->height &&
            e->width        == latestElement->width &&
            e->Difficulty() == latestElement->Difficulty() &&
            e->Efficiency() > elements.at(bestIndex)->Efficiency())
            bestIndex = i;
    }

    boost::shared_ptr<StatsElement> best(elements.at(bestIndex));

    return best;
}
}

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

        shared_ptr<StatsElement> e;

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

    Sort();
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

void StatsManager::Add(shared_ptr<StatsElement> e) {
    elements.push_back(e);
    latestElement = e;

    Sort();
}

shared_ptr<StatsElement> StatsManager::GetBestByTimeInCurrentCat() const {
    int bestIndex = -1;

    if (!latestElement)
        return shared_ptr<StatsElement>();

    for (unsigned int i = 0; i < elements.size(); i++) {
        shared_ptr<StatsElement> e(elements.at(i));
        if (e->resolution   == GR_WON &&
            e->Type()       == latestElement->Type() &&
            e->height       == latestElement->height &&
            e->width        == latestElement->width &&
            e->Difficulty() == latestElement->Difficulty() &&
            (bestIndex == -1 || e->playedTime < elements.at(bestIndex)->playedTime))
            bestIndex = i;
    }

    if (bestIndex == -1)
        return shared_ptr<StatsElement>();

    shared_ptr<StatsElement> best(elements.at(bestIndex));

    return best;
}
StatsCollection StatsManager::AggregateStats() const {
    StatsCollection c;

    if (!latestElement)
        throw Exception("No current stats found.");

    GameTypeEnum t = latestElement->Type();

    unsigned int
            playedCount = 0,
            wonCount = 0,
            lostCount = 0,
            abortedCount = 0,
            rank = (latestElement->resolution == GR_WON ? 1 : 0),
            currentPosition = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        shared_ptr<StatsElement> e(elements.at(i));
        if (e->Type() == t) {
            playedCount++;
            if (elements.at(i)->resolution == GR_WON)
                wonCount++;
            if (elements.at(i)->resolution == GR_LOST)
                lostCount++;
            if (elements.at(i)->resolution == GR_ABORTED)
                abortedCount++;
            if (latestElement->resolution == GR_WON &&
                e->resolution   == GR_WON &&
                e->height       == latestElement->height &&
                e->width        == latestElement->width &&
                e->Difficulty() == latestElement->Difficulty() &&
                e->playedTime    < latestElement->playedTime)

                rank++;
            if (e->resolution   == GR_WON &&
                e->height       == latestElement->height &&
                e->width        == latestElement->width &&
                e->Difficulty() == latestElement->Difficulty() &&
                currentPosition < 5) {

                c.Top5Time[currentPosition] = e->playedTime;
                c.Top5DateTime[currentPosition] = e->datetime;
                currentPosition++;
            }
        }
    }

    c.CurrentResolution = latestElement->resolution;
    c.CurrentTime = latestElement->playedTime;

    c.PlayedCount = playedCount;
    c.WonCount = wonCount;
    c.LostCount = lostCount;
    c.AbortedCount = abortedCount;
    c.Rank = rank;

    shared_ptr<StatsElement> bestByTime = GetBestByTimeInCurrentCat();
    c.BestTime = (bestByTime ? bestByTime->playedTime : 0);

    return c;
}

void StatsManager::Sort() {
    unsigned int nrOfOps;
    shared_ptr<StatsElement> tmp;

    do {
        nrOfOps = 0;
        for (unsigned int i = 0; i < elements.size() - 1; i++)
            if (elements[i]->playedTime > elements[i+1]->playedTime) {
                tmp = elements[i];
                elements[i] = elements[i+1];
                elements[i+1] = tmp;
                nrOfOps++;
            }
    }
    while (nrOfOps != 0);
}
}

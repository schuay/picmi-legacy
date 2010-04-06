/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_statsmanager.h"

StatsManager::StatsManager()
{
    filePath = QString(getenv("HOME")) + "/.config/picmi/stats";
}

void StatsManager::Read() {
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

        if (el.tagName() == StatsElement::ClassToStr())
            e.reset(new StatsElement);
        else if (el.tagName() == SweepStatsElement::ClassToStr())
            e.reset(new SweepStatsElement);

        e->FromXml(el);
        Add(e);

        node = node.nextSibling();
    }
}
void StatsManager::Write() {
    QFile outFile(filePath);
    outFile.open(QIODevice::WriteOnly);

    QXmlStreamWriter xml(&outFile);

    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("picmi");
    for (unsigned int i = 0; i < elements.size(); i++) {
        xml.writeStartElement(elements.at(i)->type());
        xml.writeAttributes(elements.at(i)->ToXml());
        xml.writeEndElement();
    }
    xml.writeEndElement();
    xml.writeEndDocument();

    outFile.close();
}

void StatsManager::Add(boost::shared_ptr<StatsElement> e) {
    elements.push_back(e);
}

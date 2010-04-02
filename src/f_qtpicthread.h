/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef F_QTPICTHREAD_H
#define F_QTPICTHREAD_H

#include <QThread>
#include <string>

#include "b_gamemanager.h"

namespace BoardGame {
class QTPicThread : public QThread
{
    Q_OBJECT
public:
    QTPicThread();
    ~QTPicThread();

    void run();
    void PassSettings(BoardSettings *s);
    void LoadBackground(std::string path);

signals:
    void ExceptionThrown(QString);

private:
    BoardSettings *settings;
};
}
#endif // F_QTPICTHREAD_H

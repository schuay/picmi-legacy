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

#include "f_sdlfrontend.h"

class QTPicThread : public QThread
{
public:
    QTPicThread();
    ~QTPicThread();

    void run();
    void PassSettings(PicSettings *s);
    void LoadBackground(std::string path);

private:
    PicSettings *settings;
};

#endif // F_QTPICTHREAD_H

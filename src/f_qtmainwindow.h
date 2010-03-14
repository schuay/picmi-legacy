/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef F_QTMAINWINDOW_H
#define F_QTMAINWINDOW_H

#include <QMainWindow>

#include "f_qtpicthread.h"

namespace Ui {
    class QTMainWindow;
}

class QTMainWindow : public QMainWindow {
    Q_OBJECT
public:
    QTMainWindow(PicSettings &settings, QWidget *parent = 0);
    ~QTMainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void quit();
    void start();
    void browse();

private:
    Ui::QTMainWindow *ui;

    QTPicThread t;

    void ReadSettings(PicSettings &settings);
    PicSettings* WriteSettings();
};

#endif // F_QTMAINWINDOW_H

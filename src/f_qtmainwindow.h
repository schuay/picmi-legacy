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
#include <QImage>
#include <QPixmap>
#include <QDesktopWidget>

#include "f_qtpicthread.h"
#include "f_qtsettings.h"

namespace Ui {
    class QTMainWindow;
}

namespace BoardGame {

class QTMainWindow : public QMainWindow {
    Q_OBJECT
public:
    QTMainWindow(QWidget *parent = 0);
    ~QTMainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void quit();
    void start();
    void showSettings();
    void gameTypeToogled();
    void unlockGui();

private:
    Ui::QTMainWindow *ui;

    QTPicThread t;
    BoardSettings::GameTypeEnum gameType;

    void setGuiLocked(bool locked);
};

}
#endif // F_QTMAINWINDOW_H

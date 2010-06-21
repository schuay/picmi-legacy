/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#ifndef F_QTMAINWINDOW_H
#define F_QTMAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QDesktopWidget>
#include <QMessageBox>

#include "f_qthelp.h"
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
    void displayException(QString message);
    void showHelp();

private:
    Ui::QTMainWindow *ui;

    QTPicThread t;
    GameTypeEnum gameType;

    void setGuiLocked(bool locked);
};

}
#endif // F_QTMAINWINDOW_H

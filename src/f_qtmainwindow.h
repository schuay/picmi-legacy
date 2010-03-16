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
#include <QFile>
#include <QDir>
#include <QFileDialog>

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
    void setPuzzleFolder();
    void enableGui();
    void radioButtonToggled(bool b);
    void setDefaultBG();
    void setCustomBG();

private:
    Ui::QTMainWindow *ui;

    QTPicThread t;

    QString bgPath;

    QString browse(QFileDialog::FileMode mode);

    void setGuiEnabledState(bool b);

    void ReadSettings(PicSettings &settings);
    PicSettings* WriteSettings();
};

#endif // F_QTMAINWINDOW_H
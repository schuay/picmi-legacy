/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_qtmainwindow.h"
#include "ui_f_qtmainwindow.h"
namespace BoardGame {

QTMainWindow::QTMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTMainWindow)
{
    ui->setupUi(this);

    /* fix window size */
    this->setMinimumHeight(this->size().height());
    this->setMaximumHeight(this->size().height());
    this->setMinimumWidth(this->size().width());
    this->setMaximumWidth(this->size().width());

    /* center window on screen */
    QDesktopWidget desktopWidget;
    QRect desktopRect(desktopWidget.availableGeometry(desktopWidget.primaryScreen()));
    QRect widgetRect(this->rect());
    this->move(desktopRect.center() - widgetRect.center());

    /* connect slots */
    connect(ui->bQuit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->bStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->bSettings, SIGNAL(clicked()), this, SLOT(showSettings()));
    connect(ui->rbPicross, SIGNAL(toggled(bool)), this, SLOT(gameTypeToogled()));
    connect(&t, SIGNAL(finished()), this, SLOT(unlockGui()));
    connect(&t, SIGNAL(ExceptionThrown(QString)), this, SLOT(displayException(QString)));

    /* set game preview images */
    QImage srcPicross(      FILEPREFIX "gfx/scr_picross.png");
    QImage srcMinesweeper(  FILEPREFIX "gfx/scr_minesweeper.png");

    ui->lPicross->setPixmap(QPixmap::fromImage(srcPicross));
    ui->lMinesweeper->setPixmap(QPixmap::fromImage(srcMinesweeper));

    gameType = GT_PICROSS;
}

QTMainWindow::~QTMainWindow()
{
    delete ui;
}

void QTMainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QTMainWindow::gameTypeToogled() {
    bool picrossEnabled;

    if (ui->rbPicross->isChecked()) {
        picrossEnabled = true;
        gameType = GT_PICROSS;
    }
    else {
        picrossEnabled = false;
        gameType = GT_MINESWEEPER;
    }

    ui->lPicross->setEnabled(picrossEnabled);
    ui->lMinesweeper->setEnabled(!picrossEnabled);
}

void QTMainWindow::quit() {
    this->close();
}
void QTMainWindow::start() {
    if (t.isRunning())
        return;

    setGuiLocked(true);

    BoardSettings *settings = new BoardSettings(gameType);
    settings->Load();

    t.PassSettings(settings);
    t.start();
}
void QTMainWindow::showSettings() {
    QTSettings settings(this);
    settings.exec();
}

void QTMainWindow::unlockGui() {
    setGuiLocked(false);
}
void QTMainWindow::setGuiLocked(bool locked) {
    ui->rbMinesweeper->setEnabled(!locked);
    ui->rbPicross->setEnabled(!locked);
    ui->bQuit->setEnabled(!locked);
    ui->bSettings->setEnabled(!locked);
    ui->bStart->setEnabled(!locked);
}
void QTMainWindow::displayException(QString message) {
    QMessageBox::critical(NULL,
                          QString("Error"),
                          message,
                          QMessageBox::Ok,
                          QMessageBox::NoButton);
}
}

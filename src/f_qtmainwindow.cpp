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

QTMainWindow::QTMainWindow(PicSettings &settings, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTMainWindow)
{
    ui->setupUi(this);

    connect(ui->bQuit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->bStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->bChoosePath, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->rbPuzTypeRandom, SIGNAL(toggled(bool)), this, SLOT(radioButtonToggled(bool)));
    connect(&t, SIGNAL(finished()), this, SLOT(enableGui()));

    ReadSettings(settings);
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

void QTMainWindow::ReadSettings(PicSettings &settings) {

    if (settings.Type == PUZ_RAND)
        ui->rbPuzTypeRandom->setChecked(true);
    else
        ui->rbPuzTypeStatic->setChecked(true);

    ui->lePath->setText(settings.Path.c_str());

    ui->sbWidth->setValue(settings.x);
    ui->sbHeight->setValue(settings.y);

    ui->cbNoHintsMode->setChecked(settings.NoHintsMode);

    radioButtonToggled(true);
}
PicSettings* QTMainWindow::WriteSettings() {
    PicSettings *settings = new PicSettings();

    if (ui->rbPuzTypeRandom->isChecked())
        settings->Type = PUZ_RAND;
    else
        settings->Type = PUZ_STAT;

    settings->Path = ui->lePath->displayText().toStdString();

    settings->x = ui->sbWidth->value();
    settings->y = ui->sbHeight->value();

    settings->NoHintsMode = ui->cbNoHintsMode->isChecked();

    return settings;
}

void QTMainWindow::quit() {
    this->close();
}
void QTMainWindow::start() {
    if (t.isRunning())
        return;

    setGuiEnabledState(false);

    t.PassSettings(WriteSettings());
    t.start();
}
void QTMainWindow::browse() {

}
void QTMainWindow::enableGui() {
    setGuiEnabledState(true);
}
void QTMainWindow::radioButtonToggled(bool b) {
    b=true;

    if (ui->rbPuzTypeRandom->isChecked()) {
        ui->lePath->setEnabled(!b);
        ui->bChoosePath->setEnabled(!b);

        ui->sbHeight->setEnabled(b);
        ui->sbWidth->setEnabled(b);
    }
    else {
        b = !b;

        ui->lePath->setEnabled(!b);
        ui->bChoosePath->setEnabled(!b);

        ui->sbHeight->setEnabled(b);
        ui->sbWidth->setEnabled(b);
    }
}

void QTMainWindow::setGuiEnabledState(bool b) {
    ui->rbPuzTypeRandom->setEnabled(b);
    ui->rbPuzTypeStatic->setEnabled(b);
    ui->lePath->setEnabled(b);
    ui->sbWidth->setEnabled(b);
    ui->sbHeight->setEnabled(b);
    ui->cbNoHintsMode->setEnabled(b);
    ui->bChoosePath->setEnabled(b);
    ui->bQuit->setEnabled(b);
    ui->bStart->setEnabled(b);
}

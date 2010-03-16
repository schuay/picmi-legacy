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
    connect(ui->bBrowse, SIGNAL(clicked()), this, SLOT(setPuzzleFolder()));
    connect(ui->rbPuzTypeRandom, SIGNAL(toggled(bool)), this, SLOT(radioButtonToggled(bool)));
    connect(&t, SIGNAL(finished()), this, SLOT(enableGui()));
    connect(ui->bBGCustom, SIGNAL(clicked()), this, SLOT(setCustomBG()));
    connect(ui->bBGDefault, SIGNAL(clicked()), this, SLOT(setDefaultBG()));

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

    ui->sbDifficulty->setValue(settings.Difficulty);

    ui->cbNoHintsMode->setChecked(settings.NoHintsMode);

    setGuiEnabledState(true);
}
PicSettings* QTMainWindow::WriteSettings() {
    PicSettings *settings = new PicSettings();

    if (ui->rbPuzTypeRandom->isChecked())
        settings->Type = PUZ_RAND;
    else
        settings->Type = PUZ_STAT;

    settings->x = ui->sbWidth->value();
    settings->y = ui->sbHeight->value();

    settings->NoHintsMode = ui->cbNoHintsMode->isChecked();

    settings->Difficulty = ui->sbDifficulty->value();


    QString path(ui->lePath->displayText());
    QFile f(path);
    QDir d(path);
    if (path.length() == 0)
        settings->Type = PUZ_RAND;
    else if (d.exists())
        settings->LoadRandomFromPath = true;
    else if (f.exists())
        settings->LoadRandomFromPath = false;
    else
        settings->Type = PUZ_RAND;

    settings->Path = ui->lePath->displayText().toStdString();


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
    t.LoadBackground(bgPath.toStdString());
    t.start();
}
void QTMainWindow::setPuzzleFolder() {
    QString path = browse(QFileDialog::Directory);

    if (path != "")
        ui->lePath->setText(path);
}
void QTMainWindow::enableGui() {
    setGuiEnabledState(true);
}
void QTMainWindow::radioButtonToggled(bool b) {
    setGuiEnabledState(true);
}
void QTMainWindow::setDefaultBG() {
    ui->lblBG->setText("Selected: default");
    bgPath = "";
}
void QTMainWindow::setCustomBG() {
    QString path = browse(QFileDialog::ExistingFile);

    if (path.length() != 0) {
        bgPath = path;
        ui->lblBG->setText("Selected: " + bgPath);
    }
}

void QTMainWindow::setGuiEnabledState(bool b) {
    ui->rbPuzTypeRandom->setEnabled(b);
    ui->rbPuzTypeStatic->setEnabled(b);
    ui->lePath->setEnabled(b);
    ui->sbWidth->setEnabled(b);
    ui->sbHeight->setEnabled(b);
    ui->cbNoHintsMode->setEnabled(b);
    ui->bBrowse->setEnabled(b);
    ui->bQuit->setEnabled(b);
    ui->bStart->setEnabled(b);
    ui->sbDifficulty->setEnabled(b);


    bool randomSelected = ui->rbPuzTypeRandom->isChecked();

    ui->lePath->setEnabled(!randomSelected);
    ui->bBrowse->setEnabled(!randomSelected);

    ui->sbHeight->setEnabled(randomSelected);
    ui->sbWidth->setEnabled(randomSelected);
    ui->sbDifficulty->setEnabled(randomSelected);
}

QString QTMainWindow::browse(QFileDialog::FileMode mode) {
    QFileDialog fd;

    fd.setFileMode(mode);
    fd.setOption(QFileDialog::ReadOnly);

    if (fd.exec())
        return fd.selectedFiles().at(0);
    else
        return "";
}
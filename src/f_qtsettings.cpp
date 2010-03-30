#include "f_qtsettings.h"
#include "ui_f_qtsettings.h"

namespace BoardGame {

QTSettings::QTSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSettings)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(ok()));
}

QTSettings::~QTSettings()
{
    delete ui;
}

void QTSettings::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void QTSettings::ok() {
    this->accept();
}
void QTSettings::cancel() {
    this->reject();
}

//void QTMainWindow::setPuzzleFolder() {
//    QString path = browse(QFileDialog::Directory);
//
//    if (path != "")
//        ui->lePath->setText(path);
//}
//
//void QTMainWindow::setDefaultBG() {
//    bgPath = "";
//}
//void QTMainWindow::setCustomBG() {
//    QString path = browse(QFileDialog::ExistingFile);
//
//    if (path.length() != 0)
//        bgPath = path;
//}
//
//
//QString QTMainWindow::browse(QFileDialog::FileMode mode) {
//    QFileDialog fd;
//
//    fd.setFileMode(mode);
//    fd.setOption(QFileDialog::ReadOnly);
//
//    if (fd.exec())
//        return fd.selectedFiles().at(0);
//    else
//        return "";
//}

//void QTMainWindow::ReadSettings(BoardSettings &settings) {
//
//    if (settings.GameType == settings.Minesweeper)
//        ui->rbMinesweeper->setChecked(true);
//    else
//        ui->rbPicross->setChecked(true);
//
//    if (settings.Type == PUZ_RAND)
//        ui->rbPuzTypeRandom->setChecked(true);
//    else
//        ui->rbPuzTypeStatic->setChecked(true);
//
//    ui->lePath->setText(settings.PuzzlePath.c_str());
//    bgPath = QString(settings.BackgroundPath.c_str());
//
//    ui->sbWidth->setValue(settings.x);
//    ui->sbHeight->setValue(settings.y);
//
//    ui->sbDifficulty->setValue(settings.Difficulty);
//
//    ui->cbNoHintsMode->setChecked(settings.NoHintsMode);
//
//    setGuiEnabledState(true);
//}
//BoardSettings* QTMainWindow::WriteSettings() {
//    BoardSettings *settings = new BoardSettings();
//
//    if (ui->rbMinesweeper->isChecked())
//        settings->GameType = settings->Minesweeper;
//    else
//        settings->GameType = settings->Picross;
//
//    if (ui->rbPuzTypeRandom->isChecked())
//        settings->Type = PUZ_RAND;
//    else
//        settings->Type = PUZ_STAT;
//
//    settings->x = ui->sbWidth->value();
//    settings->y = ui->sbHeight->value();
//
//    settings->NoHintsMode = ui->cbNoHintsMode->isChecked();
//
//    settings->Difficulty = ui->sbDifficulty->value();
//
//    /* test whether path exists and set path */
//    QString path(ui->lePath->displayText());
//    QFile f(path);
//    QDir d(path);
//    if (path.length() == 0)
//        settings->Type = PUZ_RAND;
//    else if (d.exists())
//        settings->LoadRandomFromPath = true;
//    else if (f.exists())
//        settings->LoadRandomFromPath = false;
//    else
//        settings->Type = PUZ_RAND;
//
//    settings->PuzzlePath = path.toStdString();
//
//    /* test whether bgPath exists and set it */
//    QFile bgFile(bgPath);
//    if (bgFile.exists())
//        settings->BackgroundPath = bgPath.toStdString();
//
//    /* save settings to disk */
//    settings->Save();
//
//    return settings;
//}

}

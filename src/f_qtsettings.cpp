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

    picross = new BoardSettings(BoardSettings::Picross);
    minesweeper = new BoardSettings(BoardSettings::Minesweeper);

    picross->Load();
    minesweeper->Load();

    ReadSettings();
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
    WriteSettings();

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

void QTSettings::ReadSettings() {

    /* picross */

    if (picross->Type == PUZ_RAND)
        ui->rbPuzTypeRandom->setChecked(true);
    else
        ui->rbPuzTypeStatic->setChecked(true);

    ui->lePuzzlePath->setText(picross->PuzzlePath.c_str());
    ui->leBGPath->setText(picross->BackgroundPath.c_str());

    ui->sbWidth->setValue(picross->x);
    ui->sbHeight->setValue(picross->y);

    ui->sbDifficulty->setValue(picross->Difficulty);

    ui->cbNoHintsMode->setChecked(picross->NoHintsMode);


    /* minesweeper */

    ui->leBGPath->setText(minesweeper->BackgroundPath.c_str());

    ui->sbWidth->setValue(minesweeper->x);
    ui->sbHeight->setValue(minesweeper->y);

    ui->sbDifficulty->setValue(minesweeper->Difficulty);
}
void QTSettings::WriteSettings() {

    /* picross */

    if (ui->rbPuzTypeRandom->isChecked())
        picross->Type = PUZ_RAND;
    else
        picross->Type = PUZ_STAT;

    picross->x = ui->sbWidth->value();
    picross->y = ui->sbHeight->value();

    picross->NoHintsMode = ui->cbNoHintsMode->isChecked();

    picross->Difficulty = ui->sbDifficulty->value();

    picross->PuzzlePath = ui->lePuzzlePath->text().toStdString();
    picross->BackgroundPath = ui->leBGPath->text().toStdString();


    /* minesweeper */

    minesweeper->x = ui->sbMSWidth->value();
    minesweeper->y = ui->sbMSHeight->value();

    minesweeper->Difficulty = ui->sbMSDifficulty->value();

    minesweeper->BackgroundPath = ui->leMSBGPath->text().toStdString();


    /* save settings to disk */
    picross->Save();
}
}

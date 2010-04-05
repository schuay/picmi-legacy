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
    connect(ui->bBrowseBG, SIGNAL(clicked()), this, SLOT(setBGPath()));
    connect(ui->bMSBrowseBG, SIGNAL(clicked()), this, SLOT(msSetBGPath()));

    picross = new BoardSettings(GT_PICROSS);
    minesweeper = new BoardSettings(GT_MINESWEEPER);

    picross->Load();
    minesweeper->Load();

    ReadSettings();
}

QTSettings::~QTSettings()
{
    delete picross;
    delete minesweeper;
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

void QTSettings::setBGPath() {
    QString path = Browse(QFileDialog::ExistingFile);

    if (path.length() != 0)
        ui->leBGPath->setText(path);
}
void QTSettings::msSetBGPath() {
    QString path = Browse(QFileDialog::ExistingFile);

    if (path.length() != 0)
        ui->leMSBGPath->setText(path);
}


QString QTSettings::Browse(QFileDialog::FileMode mode) {
    QFileDialog fd;

    fd.setFileMode(mode);
    fd.setOption(QFileDialog::ReadOnly);

    if (fd.exec())
        return fd.selectedFiles().at(0);
    else
        return "";
}

void QTSettings::ReadSettings() {

    /* picross */

    ui->leBGPath->setText(picross->BackgroundPath.c_str());

    ui->sbWidth->setValue(picross->x);
    ui->sbHeight->setValue(picross->y);

    ui->sbDifficulty->setValue(picross->Difficulty);

    ui->cbNoHintsMode->setChecked(picross->NoHintsMode);

    ui->cbBackground->setCurrentIndex(picross->UseCustomBG);

    /* minesweeper */

    ui->leMSBGPath->setText(minesweeper->BackgroundPath.c_str());

    ui->sbMSWidth->setValue(minesweeper->x);
    ui->sbMSHeight->setValue(minesweeper->y);

    ui->sbMSDifficulty->setValue(minesweeper->Difficulty);

    ui->cbMSBackground->setCurrentIndex(minesweeper->UseCustomBG);
}
void QTSettings::WriteSettings() {

    /* picross */

    picross->x = ui->sbWidth->value();
    picross->y = ui->sbHeight->value();

    picross->NoHintsMode = ui->cbNoHintsMode->isChecked();

    picross->Difficulty = ui->sbDifficulty->value();

    picross->BackgroundPath = ui->leBGPath->text().toStdString();

    picross->UseCustomBG = ui->cbBackground->currentIndex();

    /* minesweeper */

    minesweeper->x = ui->sbMSWidth->value();
    minesweeper->y = ui->sbMSHeight->value();

    minesweeper->Difficulty = ui->sbMSDifficulty->value();

    minesweeper->BackgroundPath = ui->leMSBGPath->text().toStdString();

    minesweeper->UseCustomBG = ui->cbMSBackground->currentIndex();


    /* save settings to disk */
    picross->Save();
    minesweeper->Save();
}
}

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
    connect(ui->bApplyPreset, SIGNAL(clicked()), this, SLOT(applySettings()));
    connect(ui->bMSApplyPreset, SIGNAL(clicked()), this, SLOT(msApplySettings()));
    connect(ui->bClearStats, SIGNAL(clicked()), this, SLOT(clearStats()));
    connect(ui->bMSClearStats, SIGNAL(clicked()), this, SLOT(msClearStats()));

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

void QTSettings::applySettings() {
    bool
            noHintsMode;
    unsigned int
            difficulty,
            width,
            height;

    switch (ui->cbPreset->currentIndex()) {
    case 0:     /* easy */
        width = height = 10;
        difficulty = 60;
        noHintsMode = false;
        break;
    case 1:     /* medium */
        width = height = 15;
        difficulty = 55;
        noHintsMode = false;
        break;
    case 2:     /* hard */
        width = height = 20;
        difficulty = 50;
        noHintsMode = true;
        break;
    default:
        return;
    }

    ui->sbWidth->setValue(width);
    ui->sbHeight->setValue(height);
    ui->sbDifficulty->setValue(difficulty);
    ui->cbNoHintsMode->setChecked(noHintsMode);
}
void QTSettings::msApplySettings() {
    unsigned int
            difficulty,
            width,
            height;

    switch (ui->cbMSPreset->currentIndex()) {
    case 0:     /* easy */
        width = height = 10;
        difficulty = 13;
        break;
    case 1:     /* medium */
        width = height = 15;
        difficulty = 16;
        break;
    case 2:     /* hard */
        width = height = 20;
        difficulty = 21;
        break;
    case 3:     /* very hard */
        width = 30;
        height = 16;
        difficulty = 35;
        break;
    default:
        return;
    }

    ui->sbMSWidth->setValue(width);
    ui->sbMSHeight->setValue(height);
    ui->sbMSDifficulty->setValue(difficulty);
}

void QTSettings::clearStats() {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(
            this,
            "Clear all statistics?",
            "All picross statistics will be deleted permanently. Continue?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);

    if (ret != QMessageBox::Yes)
        return;

    StatsManager m;
    m.Clear(GT_PICROSS);
    m.Write();
}
void QTSettings::msClearStats() {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(
            this,
            "Clear all statistics?",
            "All minesweeper statistics will be deleted permanently. Continue?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);

    if (ret != QMessageBox::Yes)
        return;

    StatsManager m;
    m.Clear(GT_MINESWEEPER);
    m.Write();
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

    ui->cbMSSolver->setChecked(minesweeper->EnableSolver);
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

    minesweeper->EnableSolver = ui->cbMSSolver->isChecked();


    /* save settings to disk */
    picross->Save();
    minesweeper->Save();
}
}

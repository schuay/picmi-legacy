#include "f_qtsettings.h"
#include "ui_f_qtsettings.h"

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

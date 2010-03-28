#include "f_qtsettings.h"
#include "ui_f_qtsettings.h"

QtSettings::QtSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtSettings)
{
    ui->setupUi(this);
}

QtSettings::~QtSettings()
{
    delete ui;
}

void QtSettings::changeEvent(QEvent *e)
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

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "f_qthelp.h"
#include "ui_f_qthelp.h"

QTHelp::QTHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTHelp)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

QTHelp::~QTHelp()
{
    delete ui;
}

void QTHelp::changeEvent(QEvent *e)
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

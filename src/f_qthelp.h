/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef F_QTHELP_H
#define F_QTHELP_H

#include <QDialog>

namespace Ui {
    class QTHelp;
}

class QTHelp : public QDialog {
    Q_OBJECT
public:
    QTHelp(QWidget *parent = 0);
    ~QTHelp();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QTHelp *ui;
};

#endif // F_QTHELP_H

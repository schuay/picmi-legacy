/***************************************************************************

    Copyright 2010 Jakob Gruber

    This file is part of picmi.

    picmi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    picmi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with picmi.  If not, see <http://www.gnu.org/licenses/>.

 ***************************************************************************/

#ifndef F_QTSETTINGS_H
#define F_QTSETTINGS_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "b_statsmanager.h"
#include "b_boardsettings.h"

namespace Ui {
    class QtSettings;
}

namespace BoardGame {


class QTSettings : public QDialog {
    Q_OBJECT
public:
    QTSettings(QWidget *parent = 0);
    ~QTSettings();

protected:
    void changeEvent(QEvent *e);

private slots:
    void cancel();
    void ok();

    void setBGPath();
    void msSetBGPath();

    void clearStats();
    void msClearStats();

    void applySettings();
    void msApplySettings();

private:
    Ui::QtSettings *ui;

    BoardSettings
            *picross,
            *minesweeper;

    QString Browse(QFileDialog::FileMode mode);

    void ReadSettings();
    void WriteSettings();
};

}
#endif // F_QTSETTINGS_H

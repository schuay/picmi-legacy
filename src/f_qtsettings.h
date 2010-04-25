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

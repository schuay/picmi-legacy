#ifndef F_QTSETTINGS_H
#define F_QTSETTINGS_H

#include <QDialog>

namespace Ui {
    class QtSettings;
}

class QTSettings : public QDialog {
    Q_OBJECT
public:
    QTSettings(QWidget *parent = 0);
    ~QTSettings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtSettings *ui;
};

#endif // F_QTSETTINGS_H

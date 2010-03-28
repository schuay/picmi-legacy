#ifndef F_QTSETTINGS_H
#define F_QTSETTINGS_H

#include <QWidget>

namespace Ui {
    class QtSettings;
}

class QtSettings : public QWidget {
    Q_OBJECT
public:
    QtSettings(QWidget *parent = 0);
    ~QtSettings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtSettings *ui;
};

#endif // F_QTSETTINGS_H

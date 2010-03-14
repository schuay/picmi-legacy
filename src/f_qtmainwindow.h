#ifndef F_QTMAINWINDOW_H
#define F_QTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class QTMainWindow;
}

class QTMainWindow : public QMainWindow {
    Q_OBJECT
public:
    QTMainWindow(QWidget *parent = 0);
    ~QTMainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QTMainWindow *ui;
};

#endif // F_QTMAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LFAMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LFAMMainWindow(QWidget *parent = 0);
    ~LFAMMainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

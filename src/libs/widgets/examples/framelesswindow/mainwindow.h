#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qextFramelessMainwindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QEXTFramelessMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void onTitleDoubleClicked();
    void onWindowStateChanged(bool max);

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

private:
    void initForm();
};

#endif // MAINWINDOW_H

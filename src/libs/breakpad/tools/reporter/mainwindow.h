#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindowPrivate;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

    void start();

    int autoCloseTime() const;
    void setAutoCloseTime(int msecs);

    void setCrashedAppName(const QString &name);
    void setCrashedFilePath(const QString &path);

protected:
    void onAutoCloseTimerTimeout();

private:
    Ui::MainWindow *ui;
    QScopedPointer<MainWindowPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, MainWindow)
    Q_DISABLE_COPY(MainWindow)
};

#endif // _MAINWINDOW_H

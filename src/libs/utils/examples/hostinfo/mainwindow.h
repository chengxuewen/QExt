#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qextHostInfoUtils.h>
#include <qextGlobal.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = QEXT_NULLPTR);
    ~MainWindow();

protected slots:
    void updateCpu(const quint64 &ulPercent);
    void updateMemory(const quint64 &ulIdle, const quint64 &ulTotal, const quint64 &ulPercent);
    void updateDisk(const QList<QExtDiskInfo> &listDiskInfo);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

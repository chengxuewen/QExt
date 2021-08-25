#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qexthostinfoutils.h>
#include <qextglobal.h>



namespace Ui {
class MainWindow;
}

class LFAMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LFAMMainWindow(QWidget *parent = QEXT_DECL_NULLPTR);
    ~LFAMMainWindow();

protected slots:
    void updateCpu(const quint64 &ulPercent);
    void updateMemory(const quint64 &ulIdle, const quint64 &ulTotal, const quint64 &ulPercent);
    void updateDisk(const QList<QEXTDiskInfo> &listDiskInfo);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

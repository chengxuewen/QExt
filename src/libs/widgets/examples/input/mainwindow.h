#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void initForm();
    void returnPressed();
    void accepted();
    void textValueChanged(QString text);
    void fileSelected(QString fileName);
    void receiveValue(const QString &value);
    QString getFileName(const QString &filter, const QString &defaultDir = "", const QString &fileName = "");

private slots:
    void on_btnDialog_clicked();
    void on_btnInputDialog_clicked();
    void on_btnFileDialog_clicked();
    void on_btnSaveDialog_clicked();
    void on_btnSaveDialog2_clicked();
    void on_btnAbout_clicked();
    void on_btnOpen_clicked();
    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

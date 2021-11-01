#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>

class QTKEventAdminBus;

namespace Ui {
class MainWindow;
}

class QTKEventDemo : public QObject
{
    Q_OBJECT

Q_SIGNALS:
    void receiveEventSignal(QVariantList l);
    void updateMessageSignal(QString message);

public Q_SLOTS:
    void receiveEvent(QVariantList l);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QTKEventAdminBus *bus, QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void sendEvent();
    void updateMessage(QString message);
    void connectClient();

protected:
    void changeEvent(QEvent *e);
    void connectEvents();

private:
    Ui::MainWindow *ui;
    QTKEventAdminBus *m_EventBus;
    QTKEventDemo *handler;
};

#endif // MAINWINDOW_H

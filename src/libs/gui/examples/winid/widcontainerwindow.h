#ifndef WIDCONTAINERWINDOW_H
#define WIDCONTAINERWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

namespace Ui {
class widcontainerWindow;
}

class widcontainerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit widcontainerWindow(QWidget *parent = 0);
    ~widcontainerWindow();

    void load();

protected:
    void resizeEvent(QResizeEvent *event);

protected Q_SLOTS:
    void onProcessStarted();
    void onProcessFinished();
    void onProcessFailed();
    void onTimerTimeout();

private:
    Ui::widcontainerWindow *ui;
    QProcess m_process;
    QWidget *m_widget;
    QWindow *m_window;
    QTimer m_timer;
};

#endif // WIDCONTAINERWINDOW_H

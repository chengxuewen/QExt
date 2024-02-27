#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct MainWindowPrivate;

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    virtual ~CMainWindow();

protected slots:
	void onThemeActionTriggered();
	void onStyleManagerStylesheetChanged();
    void onThemeColorButtonClicked();
    void onWidgetButtonClicked();

    void onWarnMsgDialogButtonClicked();
    void onInfoMsgDialogButtonClicked();
    void onCriticalMsgDialogButtonClicked();
    void onQuestionMsgDialogButtonClicked();
    void onAboutMsgDialogButtonClicked();
    void onAboutQtMsgDialogButtonClicked();
    void onColorDialogButtonClicked();
    void onProcessDialogButtonClicked();

protected:
    bool event(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    MainWindowPrivate *d;
    friend struct MainWindowPrivate;// pimpl
};
#endif // CMAINWINDOW_H


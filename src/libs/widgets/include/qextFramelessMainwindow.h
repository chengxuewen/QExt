#ifndef _QEXTFRAMELESSMAINWINDOW_H
#define _QEXTFRAMELESSMAINWINDOW_H

#include <qextWidgetGlobal.h>

#include <QMainWindow>

class QEXTFramelessMainWindowPrivate;
class QEXT_WIDGETS_API QEXTFramelessMainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTFramelessMainWindow)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTFramelessMainWindow)
public:
    explicit QEXTFramelessMainWindow(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTFramelessMainWindow();

    void setPadding(int padding);
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    void setTitleBar(QWidget *titleBar);

signals:
    void titleDoubleClicked();
    void windowStateChanged(bool max);

protected:
    void showEvent(QShowEvent *event) QEXT_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    //Intercepting system events is used to fix a BUG that wakes up the system after sleep
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) QEXT_DECL_OVERRIDE;
#else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) QEXT_DECL_OVERRIDE;
#endif

    //Qt4 spelled
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
    bool winEvent(MSG *message, long *result);
#endif
#endif

    //Event filter recognition drag stretch etc
    void doWindowStateChange(QEvent *event);
    void doResizeEvent(QEvent *event);

    QScopedPointer<QEXTFramelessMainWindowPrivate> dd_ptr;
};

#endif // _QEXTFRAMELESSMAINWINDOW_H

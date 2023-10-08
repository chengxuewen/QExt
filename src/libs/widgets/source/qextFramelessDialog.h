#ifndef _QEXTFRAMELESSDIALOG_H
#define _QEXTFRAMELESSDIALOG_H

#include <qextWidgetGlobal.h>

#include <QDialog>

class QEXTFramelessDialogPrivate;
class QEXT_WIDGETS_API QEXTFramelessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QEXTFramelessDialog(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTFramelessDialog();

public:
    void setPadding(int padding);
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    void setTitleBar(QWidget *titleBar);

signals:
    void titleDoubleClicked();
    void windowStateChanged(bool max);

protected:
    void showEvent(QShowEvent *event) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;

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

    QScopedPointer<QEXTFramelessDialogPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTFramelessDialog)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTFramelessDialog)
};

#endif // _QEXTFRAMELESSDIALOG_H

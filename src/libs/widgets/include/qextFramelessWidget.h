#ifndef _QEXTFRAMELESSWIDGET_H
#define _QEXTFRAMELESSWIDGET_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTFramelessWidgetPrivate;
class QEXT_WIDGETS_API QEXTFramelessWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTFramelessWidget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTFramelessWidget)
public:
    explicit QEXTFramelessWidget(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTFramelessWidget();

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

    QScopedPointer<QEXTFramelessWidgetPrivate> dd_ptr;
};

#endif // _QEXTFRAMELESSWIDGET_H

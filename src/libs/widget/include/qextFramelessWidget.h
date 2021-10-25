#ifndef _QEXTFRAMELESSWIDGET_H
#define _QEXTFRAMELESSWIDGET_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTFramelessWidgetPrivate;
class QEXT_WIDGET_API QEXTFramelessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QEXTFramelessWidget(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTFramelessWidget();

public:
    //设置边距+可拖动+可拉伸
    void setPadding(int padding);
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    //设置标题栏控件
    void setTitleBar(QWidget *titleBar);

signals:
    void titleDoubleClicked();
    void windowStateChanged(bool max);

protected:
    //窗体显示的时候触发
    void showEvent(QShowEvent *event) QEXT_DECL_OVERRIDE;

    //事件过滤器识别拖动拉伸等
    void doWindowStateChange(QEvent *event);
    void doResizeEvent(QEvent *event);
    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;

    //拦截系统事件用于修复系统休眠后唤醒程序的BUG
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) QEXT_DECL_OVERRIDE;
#else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) QEXT_DECL_OVERRIDE;
#endif

    //Qt4的写法
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
    bool winEvent(MSG *message, long *result);
#endif
#endif

    QScopedPointer<QEXTFramelessWidgetPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTFramelessWidget)
    Q_DECLARE_PRIVATE(QEXTFramelessWidget)
};

#endif // _QEXTFRAMELESSWIDGET_H

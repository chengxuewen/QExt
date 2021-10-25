#ifndef _QEXTFRAMELESSWIDGET_H
#define _QEXTFRAMELESSWIDGET_H

#include <qextWidgetGlobal.h>

#include <QWidget>

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

private:
    //边距+可移动+可拉伸
    int m_padding;
    bool m_moveEnable;
    bool m_resizeEnable;

    //标题栏控件
    QWidget *m_titleBar;

    //鼠标是否按下+按下坐标+按下时窗体区域
    bool m_mousePressed;
    QPoint m_mousePoint;
    QRect m_mouseRect;

    //鼠标是否按下某个区域+按下区域的大小
    //依次为 左侧+右侧+上侧+下侧+左上侧+右上侧+左下侧+右下侧
    QList<bool> m_pressedArea;
    QList<QRect> m_pressedRect;

    //记录是否最小化
    bool m_isMin;
    //存储窗体默认的属性
    Qt::WindowFlags m_flags;
};

#endif // _QEXTFRAMELESSWIDGET_H

#ifndef QEXTFRAMELESSMAINWINDOW_P_H
#define QEXTFRAMELESSMAINWINDOW_P_H

#include <qextWidgetGlobal.h>

#include <qextObject_p.h>

#include <QWidget>
#include <QPointer>

class QEXTFramelessMainWindow;
class QEXT_WIDGET_API QEXTFramelessMainWindowPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTFramelessMainWindowPrivate(QEXTFramelessMainWindow *qq);
    ~QEXTFramelessMainWindowPrivate();

    //边距+可移动+可拉伸
    int m_padding;
    bool m_moveEnable;
    bool m_resizeEnable;

    //标题栏控件
    QPointer<QWidget> m_titleBar;

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


private:
    QEXT_DECL_PUBLIC(QEXTFramelessMainWindow)
    QEXT_DISABLE_COPY_MOVE(QEXTFramelessMainWindowPrivate)
};

#endif // QEXTFRAMELESSMAINWINDOW_P_H

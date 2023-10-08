#ifndef _QEXTFRAMELESSWIDGET_P_H
#define _QEXTFRAMELESSWIDGET_P_H

#include <qextFramelessWidget.h>

#include <QWidget>
#include <QRect>

class QEXTFramelessWidget;
class QEXT_WIDGETS_API QEXTFramelessWidgetPrivate
{
public:
    explicit QEXTFramelessWidgetPrivate(QEXTFramelessWidget *q);
    virtual ~QEXTFramelessWidgetPrivate();

    QEXTFramelessWidget * const q_ptr;

    int m_padding;
    bool m_moveEnable;
    bool m_resizeEnable;

    QWidget *m_titleBar;

    bool m_mousePressed;
    QPoint m_mousePoint;
    QRect m_mouseRect;

    QList<bool> m_pressedArea;
    QList<QRect> m_pressedRect;

    bool m_isMin;
    Qt::WindowFlags m_flags;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTFramelessWidgetPrivate)
    QEXT_DECL_PUBLIC(QEXTFramelessWidget)
};

#endif // _QEXTFRAMELESSWIDGET_P_H

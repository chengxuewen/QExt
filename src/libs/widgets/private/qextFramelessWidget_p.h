#ifndef _QEXTFRAMELESSWIDGET_P_H
#define _QEXTFRAMELESSWIDGET_P_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QRect>

class QEXTFramelessWidget;
class QEXT_WIDGETS_API QEXTFramelessWidgetPrivate
{
    Q_DISABLE_COPY(QEXTFramelessWidgetPrivate)
    Q_DECLARE_PUBLIC(QEXTFramelessWidget)
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
};

#endif // _QEXTFRAMELESSWIDGET_P_H

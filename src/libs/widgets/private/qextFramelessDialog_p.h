#ifndef _QEXTFRAMELESSDIALOG_P_H
#define _QEXTFRAMELESSDIALOG_P_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QPoint>
#include <QRect>

class QEXTFramelessDialog;
class QEXT_WIDGETS_API QEXTFramelessDialogPrivate
{
    Q_DISABLE_COPY(QEXTFramelessDialogPrivate)
    Q_DECLARE_PUBLIC(QEXTFramelessDialog)
public:
    explicit QEXTFramelessDialogPrivate(QEXTFramelessDialog *q);
    virtual ~QEXTFramelessDialogPrivate();

    QEXTFramelessDialog * const q_ptr;

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

#endif // _QEXTFRAMELESSDIALOG_P_H

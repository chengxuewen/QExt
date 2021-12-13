#ifndef _QEXTPROGRESSBUTTON_P_H
#define _QEXTPROGRESSBUTTON_P_H

#include <qextWidgetGlobal.h>

class QEXTProgressButton;
class QEXT_WIDGETS_API QEXTProgressButtonPrivate
{
public:
    explicit QEXTProgressButtonPrivate(QEXTProgressButton * q);
    virtual ~QEXTProgressButtonPrivate();

    QEXTProgressButton * const q_ptr;

    int m_lineWidth;
    QColor m_lineColor;
    int m_borderWidth;
    QColor m_borderColor;
    int m_borderRadius;
    QColor m_backgroundColor;

    double m_value;
    int m_status;
    int m_tempWidth;
    QTimer *m_timer;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressButtonPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressButton)
};

#endif // _QEXTPROGRESSBUTTON_P_H

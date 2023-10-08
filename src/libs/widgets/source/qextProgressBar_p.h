#ifndef _QEXTPROGRESSBAR_P_H
#define _QEXTPROGRESSBAR_P_H

#include <qextProgressBar.h>

class QEXTProgressBar;
class QEXT_WIDGETS_API QEXTProgressBarPrivate
{
public:
    explicit QEXTProgressBarPrivate(QEXTProgressBar *q);
    virtual ~QEXTProgressBarPrivate();

    QEXTProgressBar * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    int m_step;
    int m_space;
    int m_radius;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_lineColor;
    QColor m_textColor;

    QColor m_barBackgroundColor;
    QColor m_barColor;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressBarPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressBar)
};

#endif // _QEXTPROGRESSBAR_P_H

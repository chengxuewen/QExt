#ifndef _QEXTPROGRESSRING_P_H
#define _QEXTPROGRESSRING_P_H

#include <qextProgressRing.h>

#include <QColor>
#include <QPropertyAnimation>

class QEXTProgressRing;
class QEXT_WIDGETS_API QEXTProgressRingPrivate
{
public:
    explicit QEXTProgressRingPrivate(QEXTProgressRing *q);
    virtual ~QEXTProgressRingPrivate();

    QEXTProgressRing * const q_ptr;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;
    QString m_text;

    bool m_clipCenter;
    bool m_clockWise;
    bool m_showPercent;

    int m_alarmMode;
    int m_startAngle;
    int m_ringPadding;
    int m_ringWidth;

    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_ringColor;
    QColor m_ringBackgroundColor;
    QColor m_circleColor;

    int m_ringValue1;
    int m_ringValue2;
    int m_ringValue3;

    QColor m_ringColor1;
    QColor m_ringColor2;
    QColor m_ringColor3;

    bool m_animationEnable;
    double m_currentValue;
    QPropertyAnimation *m_animation;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressRingPrivate)
    QEXT_DECL_PUBLIC(QEXTProgressRing)
};


#endif // _QEXTPROGRESSRING_P_H

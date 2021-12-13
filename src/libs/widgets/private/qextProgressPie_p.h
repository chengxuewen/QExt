#ifndef _QEXTPROGRESSPIE_P_H
#define _QEXTPROGRESSPIE_P_H

#include <qextWidgetGlobal.h>
#include <qextProgressPie.h>

class QEXTProgressPie;
class QEXT_WIDGETS_API QEXTProgressPiePrivate
{
public:
    explicit QEXTProgressPiePrivate(QEXTProgressPie *q);
    virtual ~QEXTProgressPiePrivate();

    QEXTProgressPie * const q_ptr;

    QColor m_backgroundColor;
    QColor m_textColor;
    QColor m_baseColor;
    QColor m_innerBackgroundColor;
    QColor m_borderColor;
    QColor m_progressColor;

    double m_minValue;
    double m_maxValue;
    double m_value;
    int m_precision;

    double m_nullPosition;
    double m_outlinePenWidth;
    double m_dataPenWidth;

    QEXTProgressPie::BarStyle m_barStyle;
    QString m_format;
    bool m_clockWise;
    QGradientStops m_gradientData;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressPiePrivate)
    QEXT_DECL_PUBLIC(QEXTProgressPie)
};

#endif // _QEXTPROGRESSPIE_P_H

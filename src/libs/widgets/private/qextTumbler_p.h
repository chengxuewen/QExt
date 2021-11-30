#ifndef _QEXTTUMBLER_P_H
#define _QEXTTUMBLER_P_H

#include <qextWidgetGlobal.h>

#include <QStringList>
#include <QColor>

class QEXTTumbler;
class QEXT_WIDGETS_API QEXTTumblerPrivate
{
    Q_DISABLE_COPY(QEXTTumblerPrivate)
    Q_DECLARE_PUBLIC(QEXTTumbler)
public:
    explicit QEXTTumblerPrivate(QEXTTumbler *q);
    virtual ~QEXTTumblerPrivate();

    QEXTTumbler * const q_ptr;

    QStringList m_valueList;
    int m_currentIndex;
    QString m_currentValue;
    bool m_isHorizontal;

    QColor m_foregroundColor;
    QColor m_backgroundColor;
    QColor m_lineColor;
    QColor m_textColor;

    int m_percent;
    int m_offset;
    bool m_pressed;
    int m_pressedPos;
    int m_currentPos;
};

#endif // _QEXTTUMBLER_P_H

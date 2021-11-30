#ifndef _QEXTNUMBERLCD_P_H
#define _QEXTNUMBERLCD_P_H

#include <qextWidgetGlobal.h>
#include <qextNumberLed.h>

#include <QColor>

class QEXTNumberLed;
class QEXT_WIDGETS_API QEXTNumberLedPrivate
{
    Q_DECLARE_PUBLIC(QEXTNumberLed)
    Q_DISABLE_COPY(QEXTNumberLedPrivate)
public:
    explicit QEXTNumberLedPrivate(QEXTNumberLed *q);
    virtual ~QEXTNumberLedPrivate();

    QEXTNumberLed * const q_ptr;

    int m_number;
    int m_space;

    QColor m_backgroundStartColor;
    QColor m_backgroundEndColor;

    QColor m_numberStartColor;
    QColor m_numberEndColor;

    QEXTNumberLed::Symbol m_symbol;

    bool m_dotVisiable;
    bool m_colonVisiable;
};

#endif // _QEXTNUMBERLCD_P_H

#ifndef _QEXTLED_P_H
#define _QEXTLED_P_H

#include <qextWidgetGlobal.h>

#include <QColor>

class QEXTLed;
class QEXT_WIDGETS_API QEXTLedPrivate
{
    Q_DISABLE_COPY(QEXTLedPrivate)
    Q_DECLARE_PUBLIC(QEXTLed)
public:
    explicit QEXTLedPrivate(QEXTLed *q);
    virtual ~QEXTLedPrivate();

    QEXTLed * const q_ptr;

    QColor m_color;
    bool m_on;
};

#endif // _QEXTLED_P_H

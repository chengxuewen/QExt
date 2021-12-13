#ifndef _QEXTLED_P_H
#define _QEXTLED_P_H

#include <qextWidgetGlobal.h>

#include <QColor>

class QEXTLed;
class QEXT_WIDGETS_API QEXTLedPrivate
{
public:
    explicit QEXTLedPrivate(QEXTLed *q);
    virtual ~QEXTLedPrivate();

    QEXTLed * const q_ptr;

    QColor m_color;
    bool m_on;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTLedPrivate)
    QEXT_DECL_PUBLIC(QEXTLed)
};

#endif // _QEXTLED_P_H

#ifndef _QEXTNUMBERLCD_P_H
#define _QEXTNUMBERLCD_P_H

#include <qextNumberLed.h>

#include <QColor>

class QEXTNumberLed;
class QEXT_WIDGETS_API QEXTNumberLedPrivate
{
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

    bool m_dotVisible;
    bool m_colonVisible;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNumberLedPrivate)
    QEXT_DECL_PUBLIC(QEXTNumberLed)
};

#endif // _QEXTNUMBERLCD_P_H

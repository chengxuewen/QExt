#ifndef _QEXTQMLQUICKBORDERGADGET_P_H
#define _QEXTQMLQUICKBORDERGADGET_P_H

#include <qextQmlQuickGlobal.h>

#include <QColor>

class QEXTQmlQuickBorderGadget;
class QEXT_QUICK_API QEXTQmlQuickBorderGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickBorderGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickBorderGadget)
public:
    explicit QEXTQmlQuickBorderGadgetPrivate(QEXTQmlQuickBorderGadget *q);
    ~QEXTQmlQuickBorderGadgetPrivate();

    bool hasValid();

    QEXTQmlQuickBorderGadget * const q_ptr;

    QColor m_color;
    qreal m_width;
    qreal m_leftWidth;
    qreal m_rightWidth;
    qreal m_topWidth;
    qreal m_bottomWidth;
    bool m_valid;
};

#endif // _QEXTQMLQUICKBORDERGADGET_P_H

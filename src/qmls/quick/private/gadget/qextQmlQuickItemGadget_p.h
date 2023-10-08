#ifndef _QEXTQMLQUICKITEMGADGET_P_H
#define _QEXTQMLQUICKITEMGADGET_P_H

#include <qextQmlQuickGlobal.h>

class QEXTQmlQuickItemGadget;
class QEXT_QUICK_API QEXTQmlQuickItemGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickItemGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickItemGadget)
public:
    explicit QEXTQmlQuickItemGadgetPrivate(QEXTQmlQuickItemGadget *q);
    virtual ~QEXTQmlQuickItemGadgetPrivate();

    QEXTQmlQuickItemGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
};

#endif // _QEXTQMLQUICKITEMGADGET_P_H

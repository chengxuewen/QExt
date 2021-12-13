#ifndef _QEXTITEMGADGET_P_H
#define _QEXTITEMGADGET_P_H

#include <qextQuickGlobal.h>

class QEXTQuickItemGadget;
class QEXT_QUICK_API QEXTQuickItemGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQuickItemGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickItemGadget)
public:
    explicit QEXTQuickItemGadgetPrivate(QEXTQuickItemGadget *q);
    virtual ~QEXTQuickItemGadgetPrivate();

    QEXTQuickItemGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
};



#endif // _QEXTITEMGADGET_P_H

#ifndef _QEXTQUICKITEMGADGET_P_H
#define _QEXTQUICKITEMGADGET_P_H

#include <qextQuickItemGadget.h>

class QEXT_QUICK_API QExtQuickItemGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickItemGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickItemGadget)
public:
    explicit QExtQuickItemGadgetPrivate(QExtQuickItemGadget *q);
    virtual ~QExtQuickItemGadgetPrivate();

    QExtQuickItemGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
};

#endif // _QEXTQUICKITEMGADGET_P_H

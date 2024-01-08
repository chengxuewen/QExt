#ifndef _QEXTQUICKBORDERGADGET_P_H
#define _QEXTQUICKBORDERGADGET_P_H

#include <qextQuickBorderGadget.h>

#include <QColor>

class QEXT_QUICK_API QExtQuickBorderGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickBorderGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickBorderGadget)
public:
    explicit QExtQuickBorderGadgetPrivate(QExtQuickBorderGadget *q);
    ~QExtQuickBorderGadgetPrivate();

    bool hasValid();

    QExtQuickBorderGadget * const q_ptr;

    QColor m_color;
    qreal m_width;
    qreal m_leftWidth;
    qreal m_rightWidth;
    qreal m_topWidth;
    qreal m_bottomWidth;
    bool m_valid;
};

#endif // _QEXTQUICKBORDERGADGET_P_H

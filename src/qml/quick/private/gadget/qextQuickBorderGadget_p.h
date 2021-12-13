#ifndef _QEXTBORDERGADGET_P_H
#define _QEXTBORDERGADGET_P_H

#include <qextQuickGlobal.h>

#include <QColor>

class QEXTQuickBorderGadget;
class QEXT_QUICK_API QEXTQuickBorderGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQuickBorderGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickBorderGadget)
public:
    explicit QEXTQuickBorderGadgetPrivate(QEXTQuickBorderGadget *q);
    ~QEXTQuickBorderGadgetPrivate();

    bool hasValid();

    QEXTQuickBorderGadget * const q_ptr;

    QColor m_color;
    qreal m_width;
    qreal m_leftWidth;
    qreal m_rightWidth;
    qreal m_topWidth;
    qreal m_bottomWidth;
    bool m_valid;
};



#endif // _QEXTBORDERGADGET_P_H

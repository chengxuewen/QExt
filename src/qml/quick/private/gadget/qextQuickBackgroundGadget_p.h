#ifndef _QEXTGADGETBACKGROUND_P_H
#define _QEXTGADGETBACKGROUND_P_H

#include <qextQuickGlobal.h>

#include <QColor>

class QEXTQuickBackgroundGadget;
class QEXT_QUICK_API QEXTQuickBackgroundGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQuickBackgroundGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickBackgroundGadget)
public:
    explicit QEXTQuickBackgroundGadgetPrivate(QEXTQuickBackgroundGadget *q);
    virtual ~QEXTQuickBackgroundGadgetPrivate();

    QEXTQuickBackgroundGadget * const q_ptr;

    QColor m_color;
    qreal m_radius;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_scale;
    bool m_visible;
};



#endif // _QEXTGADGETBACKGROUND_P_H

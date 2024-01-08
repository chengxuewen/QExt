#ifndef _QEXTQUICKGADGETBACKGROUND_P_H
#define _QEXTQUICKGADGETBACKGROUND_P_H

#include <qextQuickBackgroundGadget.h>

#include <QColor>

class QEXT_QUICK_API QExtQuickBackgroundGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickBackgroundGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickBackgroundGadget)
public:
    explicit QExtQuickBackgroundGadgetPrivate(QExtQuickBackgroundGadget *q);
    virtual ~QExtQuickBackgroundGadgetPrivate();

    QExtQuickBackgroundGadget * const q_ptr;

    QColor m_color;
    qreal m_radius;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_scale;
    bool m_visible;
};

#endif // _QEXTQUICKGADGETBACKGROUND_P_H

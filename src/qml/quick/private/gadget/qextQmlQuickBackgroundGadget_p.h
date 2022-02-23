#ifndef _QEXTQMLQUICKGADGETBACKGROUND_P_H
#define _QEXTQMLQUICKGADGETBACKGROUND_P_H

#include <qextQmlQuickGlobal.h>

#include <QColor>

class QEXTQmlQuickBackgroundGadget;
class QEXT_QUICK_API QEXTQmlQuickBackgroundGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickBackgroundGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickBackgroundGadget)
public:
    explicit QEXTQmlQuickBackgroundGadgetPrivate(QEXTQmlQuickBackgroundGadget *q);
    virtual ~QEXTQmlQuickBackgroundGadgetPrivate();

    QEXTQmlQuickBackgroundGadget * const q_ptr;

    QColor m_color;
    qreal m_radius;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_scale;
    bool m_visible;
};

#endif // _QEXTQMLQUICKGADGETBACKGROUND_P_H

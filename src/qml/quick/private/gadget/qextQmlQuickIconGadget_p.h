#ifndef _QEXTQMLQUICKICONGADGET_P_H
#define _QEXTQMLQUICKICONGADGET_P_H

#include <qextQmlQuickGlobal.h>

#include <QColor>

class QEXTQmlQuickIconGadget;
class QEXT_QUICK_API QEXTQmlQuickIconGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickIconGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickIconGadget)
public:
    explicit QEXTQmlQuickIconGadgetPrivate(QEXTQmlQuickIconGadget *q);
    virtual ~QEXTQmlQuickIconGadgetPrivate();

    QEXTQmlQuickIconGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;
};



#endif // _QEXTQMLQUICKICONGADGET_P_H

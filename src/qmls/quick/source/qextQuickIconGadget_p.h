#ifndef _QEXTQUICKICONGADGET_P_H
#define _QEXTQUICKICONGADGET_P_H

#include <qextQuickIconGadget.h>

#include <QColor>

class QEXT_QUICK_API QExtQuickIconGadgetPrivate
{
    Q_DISABLE_COPY(QExtQuickIconGadgetPrivate)
    Q_DECLARE_PUBLIC(QExtQuickIconGadget)
public:
    explicit QExtQuickIconGadgetPrivate(QExtQuickIconGadget *q);
    virtual ~QExtQuickIconGadgetPrivate();

    QExtQuickIconGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;
};



#endif // _QEXTQUICKICONGADGET_P_H

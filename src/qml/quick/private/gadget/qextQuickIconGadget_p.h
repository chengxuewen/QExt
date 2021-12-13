#ifndef _QEXTICONGADGET_P_H
#define _QEXTICONGADGET_P_H

#include <qextQuickGlobal.h>

#include <QColor>

class QEXTQuickIconGadget;
class QEXT_QUICK_API QEXTQuickIconGadgetPrivate
{
    Q_DISABLE_COPY(QEXTQuickIconGadgetPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickIconGadget)
public:
    explicit QEXTQuickIconGadgetPrivate(QEXTQuickIconGadget *q);
    virtual ~QEXTQuickIconGadgetPrivate();

    QEXTQuickIconGadget * const q_ptr;

    qreal m_width;
    qreal m_height;
    int m_type;
    int m_position;
    qreal m_scale;
    QColor m_color;
    QString m_source;
};



#endif // _QEXTICONGADGET_P_H

#ifndef _QEXTICONLABEL_P_H
#define _QEXTICONLABEL_P_H

#include <qextWidgetGlobal.h>
#include <qextIconLabel.h>

class QEXTIconLabel;
class QEXT_WIDGETS_API QEXTIconLabelPrivate
{
    Q_DECLARE_PUBLIC(QEXTIconLabel)
    Q_DISABLE_COPY(QEXTIconLabelPrivate)
public:
    explicit QEXTIconLabelPrivate(QEXTIconLabel *q);
    virtual ~QEXTIconLabelPrivate();

    QEXTIconLabel * const q_ptr;
};

#endif // _QEXTICONLABEL_P_H

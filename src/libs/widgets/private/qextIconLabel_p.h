#ifndef _QEXTICONLABEL_P_H
#define _QEXTICONLABEL_P_H

#include <qextWidgetGlobal.h>
#include <qextIconLabel.h>

class QEXTIconLabel;
class QEXT_WIDGETS_API QEXTIconLabelPrivate
{
public:
    explicit QEXTIconLabelPrivate(QEXTIconLabel *q);
    virtual ~QEXTIconLabelPrivate();

    QEXTIconLabel * const q_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTIconLabelPrivate)
    QEXT_DECL_PUBLIC(QEXTIconLabel)
};

#endif // _QEXTICONLABEL_P_H

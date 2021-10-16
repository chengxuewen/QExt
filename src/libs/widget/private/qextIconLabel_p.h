#ifndef _QEXTICONLABEL_P_H
#define _QEXTICONLABEL_P_H

#include <qextWidgetGlobal.h>
#include <qextIconLabel.h>

#include <qextObject_p.h>

class QEXTIconLabel;
class QEXT_WIDGET_API QEXTIconLabelPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTIconLabelPrivate(QEXTIconLabel *qq);
    ~QEXTIconLabelPrivate();



private:
    QEXT_DECL_PUBLIC(QEXTIconLabel)
    QEXT_DISABLE_COPY_MOVE(QEXTIconLabelPrivate)
};

#endif // _QEXTICONLABEL_P_H

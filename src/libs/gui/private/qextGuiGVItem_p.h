#ifndef _QEXTGUIGVITEM_P_H
#define _QEXTGUIGVITEM_P_H

#include <qextGuiGlobal.h>

class QEXTGuiGVItem;
class QEXT_GUI_API QEXTGuiGVItemPrivate
{
public:
    explicit QEXTGuiGVItemPrivate(QEXTGuiGVItem *q);
    virtual ~QEXTGuiGVItemPrivate();

    QEXTGuiGVItem * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiGVItemPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiGVItem)
};

#endif // _QEXTGUIGVITEM_P_H

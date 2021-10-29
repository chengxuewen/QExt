#ifndef _QEXTGUIITEM_P_H
#define _QEXTGUIITEM_P_H

#include <qextGuiGlobal.h>

class QEXTGuiItem;
class QEXT_GUI_API QEXTGuiItemPrivate
{
public:
    explicit QEXTGuiItemPrivate(QEXTGuiItem *q);
    virtual ~QEXTGuiItemPrivate();

    QEXTGuiItem * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiItemPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiItem)
};

#endif // _QEXTGUIITEM_P_H

#ifndef _QEXTGUIGVVIEW_P_H
#define _QEXTGUIGVVIEW_P_H

#include <qextGuiGlobal.h>

class QEXTGuiGVView;
class QEXT_GUI_API QEXTGuiGVViewPrivate
{
public:
    explicit QEXTGuiGVViewPrivate(QEXTGuiGVView *q);
    virtual ~QEXTGuiGVViewPrivate();

    QEXTGuiGVView * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiGVViewPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiGVView)
};

#endif // _QEXTGUIGVVIEW_P_H

#ifndef _QEXTGUI_P_H
#define _QEXTGUI_P_H

#include <qextGuiGlobal.h>

class QEXTGui;
class QEXT_GUI_API QEXTGuiPrivate
{
public:
    explicit QEXTGuiPrivate(QEXTGui *q);
    virtual ~QEXTGuiPrivate();

    QEXTGui * const q_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiPrivate)
    Q_DECLARE_PUBLIC(QEXTGui)
};

#endif // _QEXTGUI_P_H

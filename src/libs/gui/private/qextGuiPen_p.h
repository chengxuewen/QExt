#ifndef _QEXTGUIPEN_P_H
#define _QEXTGUIPEN_P_H

#include <qextGuiGlobal.h>

#include <QColor>

class QEXTGuiPen;
class QEXT_GUI_API QEXTGuiPenPrivate
{
public:
    explicit QEXTGuiPenPrivate(QEXTGuiPen *q);
    virtual ~QEXTGuiPenPrivate();

    void updateValid();

    QEXTGuiPen * const q_ptr;

    int m_width;
    bool m_valid;
    QColor m_color;

private:
    Q_DISABLE_COPY(QEXTGuiPenPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiPen)
};

#endif // _QEXTGUIPEN_P_H

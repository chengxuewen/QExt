#ifndef _QEXTGUICONTENTS_P_H
#define _QEXTGUICONTENTS_P_H

#include <qextGuiGlobal.h>

class QEXTGuiGVItem;
class QEXTGuiContents;
class QEXT_GUI_API QEXTGuiContentsPrivate
{
public:
    explicit QEXTGuiContentsPrivate(QEXTGuiContents *q);
    virtual ~QEXTGuiContentsPrivate();

    QEXTGuiContents * const q_ptr;

    QEXTGuiGVItem *m_item;
    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;

private:
    Q_DISABLE_COPY(QEXTGuiContentsPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiContents)
};

#endif // _QEXTGUICONTENTS_P_H

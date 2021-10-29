#ifndef _QEXTGUIGVRECTANGLE_P_H
#define _QEXTGUIGVRECTANGLE_P_H

#include <qextGuiGlobal.h>
#include <qextGuiPen.h>
#include <qextGuiGradient.h>
#include <qextGuiGVItem_p.h>

class QEXTGuiGVRectangle;
class QEXT_GUI_API QEXTGuiGVRectanglePrivate : public QEXTGuiGVItemPrivate
{
public:
    explicit QEXTGuiGVRectanglePrivate(QEXTGuiGVRectangle *q);
    ~QEXTGuiGVRectanglePrivate();

    QEXTGuiPen *pen();
    void setPaintMargin(qreal margin);

    QEXTGuiGradient *m_gradient;
    QEXTGuiPen *m_pen;
    QColor m_color;
    qreal m_radius;
    qreal m_paintmargin;
    QPixmap m_rectImage;

    static int sm_doUpdateSlotIdx;

private:
    Q_DISABLE_COPY(QEXTGuiGVRectanglePrivate)
    Q_DECLARE_PUBLIC(QEXTGuiGVRectangle)
};

#endif // _QEXTGUIGVRECTANGLE_P_H

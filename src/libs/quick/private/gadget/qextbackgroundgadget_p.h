#ifndef _QEXTGADGETBACKGROUND_P_H
#define _QEXTGADGETBACKGROUND_P_H

#include <qextquickglobal.h>

#include <qextObject_p.h>

#include <QColor>



class QEXTBackgroundGadget;
class QEXT_QUICK_API QEXTBackgroundGadgetPrivate: public QEXTObjectPrivate
{
public:
    explicit QEXTBackgroundGadgetPrivate(QEXTBackgroundGadget *qq);
    ~QEXTBackgroundGadgetPrivate();

    QColor m_color;
    qreal m_radius;
    qreal m_width;
    qreal m_height;
    qreal m_opacity;
    qreal m_scale;
    bool m_visible;

private:
    QEXT_DECL_PUBLIC(QEXTBackgroundGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTBackgroundGadgetPrivate)
};



#endif // _QEXTGADGETBACKGROUND_P_H

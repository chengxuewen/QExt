#ifndef QEXTBORDERGADGET_P_H
#define QEXTBORDERGADGET_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

#include <QColor>



class QEXTBorderGadget;
class QEXT_QUICK_API QEXTBorderGadgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTBorderGadgetPrivate(QEXTBorderGadget *qq);
    ~QEXTBorderGadgetPrivate();

    bool hasValid();

    QColor m_color;
    qreal m_width;
    qreal m_leftWidth;
    qreal m_rightWidth;
    qreal m_topWidth;
    qreal m_bottomWidth;
    bool m_valid;

private:
    QEXT_DECL_PUBLIC(QEXTBorderGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTBorderGadgetPrivate)
};



#endif // QEXTBORDERGADGET_P_H

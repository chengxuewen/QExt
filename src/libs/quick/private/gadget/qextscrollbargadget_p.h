#ifndef _QEXTSCROLLBARGADGET_P_H
#define _QEXTSCROLLBARGADGET_P_H

#include <qextquickglobal.h>

#include <qextObject_p.h>



class QEXTScrollbarGadget;
class QEXT_QUICK_API QEXTScrollbarGadgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTScrollbarGadgetPrivate(QEXTScrollbarGadget *qq);
    ~QEXTScrollbarGadgetPrivate();

    bool m_horizontal;
    bool m_vertical;
    bool m_autoHide;

private:
    QEXT_DECL_PUBLIC(QEXTScrollbarGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTScrollbarGadgetPrivate)
};



#endif // _QEXTSCROLLBARGADGET_P_H

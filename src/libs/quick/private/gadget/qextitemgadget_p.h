#ifndef QEXTITEMGADGET_P_H
#define QEXTITEMGADGET_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

class QEXTItemGadget;
class QEXT_QUICK_API QEXTItemGadgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTItemGadgetPrivate(QEXTItemGadget *qq);
    ~QEXTItemGadgetPrivate();

    qreal m_width;
    qreal m_height;

private:
    QEXT_DECLARE_PUBLIC(QEXTItemGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTItemGadgetPrivate)
};

#endif // QEXTITEMGADGET_P_H

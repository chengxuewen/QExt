#ifndef QEXTCONTROLBASE_P_H
#define QEXTCONTROLBASE_P_H

#include <qextobject_p.h>

#include <qextcontrolsglobal.h>

#include <QPalette>
#include <QFont>
#include <QRect>



class QEXTControlBase;
class QEXT_CONTROLS_API QEXTControlBasePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTControlBasePrivate(QEXTControlBase *qq);
    ~QEXTControlBasePrivate();

    mutable QPalette pal;
    QRect crect;
    QFont fnt;
    QRect wrect;

private:
    QEXT_DECLARE_PUBLIC(QEXTControlBase)
    QEXT_DISABLE_COPY_MOVE(QEXTControlBasePrivate)
};



#endif // QEXTCONTROLBASE_P_H

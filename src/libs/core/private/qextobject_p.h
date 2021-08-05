#ifndef QEXTOBJECT_P_H
#define QEXTOBJECT_P_H

#include <qextglobal.h>



class QEXTObject;
class QEXT_CORE_API QEXTObjectPrivate
{
public:
    virtual ~QEXTObjectPrivate() {}

protected:
    explicit QEXTObjectPrivate(QEXTObject *qq) : q_ptr(qq) {}
    QEXTObject *q_ptr;

    QEXT_DECLARE_PUBLIC(QEXTObject)
    QEXT_DISABLE_COPY_MOVE(QEXTObjectPrivate)
};



#endif // QEXTOBJECT_P_H

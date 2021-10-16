#ifndef _QEXTOBJECT_P_H
#define _QEXTOBJECT_P_H

#include <qextGlobal.h>

class QEXTObject;
class QEXT_CORE_API QEXTObjectPrivate
{
public:
    virtual ~QEXTObjectPrivate() {}

protected:
    explicit QEXTObjectPrivate(QEXTObject *qq) : q_objPtr(qq) {}
    QEXTObject *q_objPtr;

    QEXT_DECL_PUBLIC(QEXTObject)
    QEXT_DISABLE_COPY_MOVE(QEXTObjectPrivate)
};

#endif // _QEXTOBJECT_P_H

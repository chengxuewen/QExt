#ifndef _QEXTOBJECT_H
#define _QEXTOBJECT_H

#include <qextGlobal.h>

#include <QScopedPointer>

class QEXTObjectPrivate;
class QEXT_CORE_API QEXTObject
{
public:
    QEXTObject();
    virtual ~QEXTObject();

protected:
    explicit QEXTObject(QEXTObjectPrivate &dd);
    
    QScopedPointer<QEXTObjectPrivate> d_objPtr;

private:
    QEXT_DECL_PRIVATE(QEXTObject)
    QEXT_DISABLE_COPY_MOVE(QEXTObject)
};

#endif // _QEXTOBJECT_H

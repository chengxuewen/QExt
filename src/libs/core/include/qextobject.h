#ifndef QEXTOBJECT_H
#define QEXTOBJECT_H

#include <qextglobal.h>

#include <QScopedPointer>

class QEXTObjectPrivate;
class QEXT_CORE_API QEXTObject
{
public:
    QEXTObject(QEXTObject *parent = QEXT_DECL_NULLPTR);
    QEXTObject(QEXTObjectPrivate &dd, QEXTObject *parent = QEXT_DECL_NULLPTR);
    virtual ~QEXTObject();

    QScopedPointer<QEXTObjectPrivate> d_objPtr;

private:
    QEXT_DECL_PRIVATE(QEXTObject)
    QEXT_DISABLE_COPY_MOVE(QEXTObject)
};

#endif // QEXTOBJECT_H

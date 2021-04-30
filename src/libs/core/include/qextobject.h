#ifndef QEXTOBJECT_H
#define QEXTOBJECT_H

#include <qextglobal.h>

#include <QScopedPointer>

class QEXTObjectPrivate;
class QEXT_CORE_API QEXTObject
{
public:
    QEXTObject(QEXTObject *parent = QEXT_NULLPTR);
    QEXTObject(QEXTObjectPrivate &dd, QEXTObject *parent = QEXT_NULLPTR);
    virtual ~QEXTObject();

    QScopedPointer<QEXTObjectPrivate> dd_ptr;

    QEXT_DISABLE_COPY_MOVE(QEXTObject)
    QEXT_DECLARE_PRIVATE(QEXTObject)
};

#endif // QEXTOBJECT_H

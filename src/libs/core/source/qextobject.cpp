#include <qextobject.h>
#include <qextobject_p.h>



QEXTObject::QEXTObject(QEXTObject *parent)
{
    Q_UNUSED(parent);
}

QEXTObject::QEXTObject(QEXTObjectPrivate &dd, QEXTObject *parent)
    : d_objPtr(&dd)
{
    Q_UNUSED(parent);
}

QEXTObject::~QEXTObject()
{

}

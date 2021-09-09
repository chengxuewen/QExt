#include "qextsimpleobject.h"

#include <qextObject_p.h>

class QEXTSimpleObjectPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTSimpleObjectPrivate(QEXTSimpleObject *qq);
    ~QEXTSimpleObjectPrivate();

    QString m_string;

private:
    QEXT_DECL_PUBLIC(QEXTSimpleObject)
    QEXT_DISABLE_COPY_MOVE(QEXTSimpleObjectPrivate)
};

QEXTSimpleObjectPrivate::QEXTSimpleObjectPrivate(QEXTSimpleObject *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTSimpleObjectPrivate::~QEXTSimpleObjectPrivate()
{

}



QEXTSimpleObject::QEXTSimpleObject(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTSimpleObjectPrivate(this)))
{

}

QEXTSimpleObject::~QEXTSimpleObject()
{

}

QString QEXTSimpleObject::string() const
{
    QEXT_DECL_DC(QEXTSimpleObject);
    return d->m_string;
}

void QEXTSimpleObject::setString(const QString &string)
{
    QEXT_DECL_D(QEXTSimpleObject);
    d->m_string = string;
}

#include <qextcontrolbase.h>
#include <qextcontrolbase_p.h>

QEXTControlBasePrivate::QEXTControlBasePrivate(QEXTControlBase *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTControlBasePrivate::~QEXTControlBasePrivate()
{

}



QEXTControlBase::QEXTControlBase(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTControlBasePrivate(this)))
{

}

QEXTControlBase::~QEXTControlBase()
{

}


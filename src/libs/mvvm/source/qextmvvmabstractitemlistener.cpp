#include <qextmvvmabstractitemlistener.h>
#include <qextmvvmabstractitemlistener_p.h>
#include <qextmvvmitem.h>
//#include "qextmvvm"

#include <QDebug>

QEXT_USE_NAMESPACE

QEXTMvvmAbstractItemListenerPrivate::QEXTMvvmAbstractItemListenerPrivate(QEXTMvvmAbstractItemListener *qq)
    : QEXTObjectPrivate(qq)
{
    m_item = QEXT_NULLPTR;
}

QEXTMvvmAbstractItemListenerPrivate::~QEXTMvvmAbstractItemListenerPrivate()
{

}

void QEXTMvvmAbstractItemListenerPrivate::unsubscribeFromCurrent()
{

}



QEXTMvvmAbstractItemListener::QEXTMvvmAbstractItemListener(QEXTMvvmItem *item)
    : QEXTObject(*(new QEXTMvvmAbstractItemListenerPrivate(this)))
{
    this->setItem(item);
}

QEXTMvvmAbstractItemListener::~QEXTMvvmAbstractItemListener()
{
    QEXT_D(QEXTMvvmAbstractItemListener);
           if (d->m_item) {
            d->m_item->model()
           }
}

void QEXTMvvmAbstractItemListener::setItem(QEXTMvvmItem *item)
{

}

void QEXTMvvmAbstractItemListener::setOnItemDestroy(QEXTMvvmItem_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnDataChange(QEXTMvvmItem_int_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnPropertyChange(QEXTMvvmItem_str_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnChildPropertyChange(QEXTMvvmItem_str_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnItemInserted(QEXTMvvmItem_tagrow_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnItemRemoved(QEXTMvvmItem_tagrow_t f)
{

}

void QEXTMvvmAbstractItemListener::setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f)
{

}

QEXTMvvmItem *QEXTMvvmAbstractItemListener::item() const
{

}



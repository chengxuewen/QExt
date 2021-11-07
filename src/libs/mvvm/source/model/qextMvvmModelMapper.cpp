#include <qextMvvmModelMapper.h>
#include <qextMvvmModelMapper_p.h>
#include <qextMvvmTagRow.h>

#include <qextConnection.h>

#include <QMultiMap>


QEXTMvvmModelMapperPrivate::QEXTMvvmModelMapperPrivate(QEXTMvvmModelMapper *q)
    : q_ptr(q)
    , m_active(true)
    , m_model(QEXT_DECL_NULLPTR)
{

}

QEXTMvvmModelMapperPrivate::~QEXTMvvmModelMapperPrivate()
{

}



QEXTMvvmModelMapper::QEXTMvvmModelMapper(QEXTMvvmModel *model)
    : d_ptr(new QEXTMvvmModelMapperPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    d->m_model = model;
}

QEXTMvvmModelMapper::~QEXTMvvmModelMapper()
{

}

QEXTConnection QEXTMvvmModelMapper::addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemAboutToBeInsertedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemInsertedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemAboutToBeRemovedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemRemovedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemDataAboutToBeChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemDataChangedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemAboutToBeDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_itemDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addModelAboutToBeDestroyedListener(QEXTMvvmModelFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_modelAboutToBeDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addModelDestroyedListener(QEXTMvvmModelFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_modelDestroyedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addModelAboutToBeResetedListener(QEXTMvvmModelFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_modelAboutToBeResetedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

QEXTConnection QEXTMvvmModelMapper::addModelResetedListener(QEXTMvvmModelFunction function, void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QEXTConnection connection = d->m_modelResetedSignal.connect(function);
    d->m_lisenterConnectionMap.insert(listener, connection);
    return connection;
}

void QEXTMvvmModelMapper::removeListener(void *listener)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    QList<QEXTConnection> connections = d->m_lisenterConnectionMap.values(listener);
    for (int i = 0; i < connections.size(); ++i)
    {
        QEXTConnection connection = connections.at(i);
        connection.disconnect();
    }
    d->m_lisenterConnectionMap.remove(listener);
}

//! Sets activity flag to given value. Will disable all callbacks if false.

void QEXTMvvmModelMapper::setActive(bool value)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    d->m_active = value;
}


//! Notifies all callbacks subscribed to "item data is changed" event.

void QEXTMvvmModelMapper::callOnDataChange(QEXTMvvmItem* item, int role)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    if (d->m_active)
        d->m_itemDataChangedSignal(item, role);
}

//! Notifies all callbacks subscribed to "item data is changed" event.

void QEXTMvvmModelMapper::callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    if (d->m_active)
        d->m_itemInsertedSignal(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnItemRemoved(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    if (d->m_active)
        d->m_itemRemovedSignal(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnItemAboutToBeRemoved(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow)
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    if (d->m_active)
        d->m_itemAboutToBeRemovedSignal(parent, tagrow);
}

void QEXTMvvmModelMapper::callOnModelDestroyed()
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    d->m_modelDestroyedSignal(d->m_model);
}

void QEXTMvvmModelMapper::callOnModelAboutToBeReset()
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    d->m_modelAboutToBeResetedSignal(d->m_model);
}

void QEXTMvvmModelMapper::callOnModelReset()
{
    QEXT_DECL_D(QEXTMvvmModelMapper);
    d->m_modelResetedSignal(d->m_model);
}

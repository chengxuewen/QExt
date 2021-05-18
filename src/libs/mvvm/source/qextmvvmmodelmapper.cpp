#include "qextmvvmmodelmapper.h"
#include "qextmvvmmodelmapper_p.h"

QEXT_USE_NAMESPACE

QEXTMvvmModelMapperPrivate::QEXTMvvmModelMapperPrivate(QEXTMvvmModelMapper *qq)
    : QEXTObjectPrivate(qq)
{
    m_active = true;
    m_model = QEXT_NULLPTR;
}

QEXTMvvmModelMapperPrivate::~QEXTMvvmModelMapperPrivate()
{

}

void QEXTMvvmModelMapperPrivate::unsubscribe(QEXTMvvmSlot_t client)
{
    m_on_data_change.remove_client(client);
    m_on_item_inserted.remove_client(client);
    m_on_item_removed.remove_client(client);
    m_on_item_about_removed.remove_client(client);
    m_on_model_destroyed.remove_client(client);
    m_on_model_about_reset.remove_client(client);
    m_on_model_reset.remove_client(client);
}



QEXTMvvmModelMapper::QEXTMvvmModelMapper(QEXTMvvmModel *model)
    : QEXTObject(*(new QEXTMvvmModelMapperPrivate(this)))
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_model = model;
}

QEXTMvvmModelMapper::~QEXTMvvmModelMapper()
{

}

void QEXTMvvmModelMapper::setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_data_change.connect(f, client);
}

void QEXTMvvmModelMapper::setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_item_inserted.connect(f, client);
}

void QEXTMvvmModelMapper::setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_item_removed.connect(f, client);
}

void QEXTMvvmModelMapper::setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_item_about_removed.connect(f, client);
}

void QEXTMvvmModelMapper::setOnModelDestroyed(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_model_destroyed.connect(f, client);
}

void QEXTMvvmModelMapper::setOnModelAboutToBeReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_model_about_reset.connect(f, client);
}

void QEXTMvvmModelMapper::setOnModelReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_on_model_reset.connect(f, client);
}

void QEXTMvvmModelMapper::unsubscribe(QEXTMvvmSlot_t client)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->unsubscribe(client);
}

void QEXTMvvmModelMapper::setActive(bool value)
{
    QEXT_D(QEXTMvvmModelMapper);
    d->m_active = value;
}

void QEXTMvvmModelMapper::callOnDataChange(QEXTMvvmItem *item, int role)
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_data_change(item, role);
    }
}

void QEXTMvvmModelMapper::callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_item_inserted(parent, tagrow);
    }
}

void QEXTMvvmModelMapper::callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_item_removed(parent, tagrow);
    }
}

void QEXTMvvmModelMapper::callOnItemAboutToBeRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_item_about_removed(parent, tagrow);
    }
}

void QEXTMvvmModelMapper::callOnModelDestroyed()
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_model_destroyed(d->m_model);
    }
}

void QEXTMvvmModelMapper::callOnModelAboutToBeReset()
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_model_about_reset(d->m_model);
    }
}

void QEXTMvvmModelMapper::callOnModelReset()
{
    QEXT_D(QEXTMvvmModelMapper);
    if (d->m_active) {
        d->m_on_model_reset(d->m_model);
    }
}


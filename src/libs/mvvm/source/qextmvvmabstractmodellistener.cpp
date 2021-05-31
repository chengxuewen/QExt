#include "qextmvvmabstractmodellistener.h"
#include "qextmvvmmodel.h"
#include "qextmvvmmodelmapper.h"

QEXT_USE_NAMESPACE

QEXTMvvmAbstractModelListener::QEXTMvvmAbstractModelListener(QEXTMvvmModel *model)
    : m_model(model)
{
    if (!m_model) {
        qFatal("Error in ModelListenerBase: no model defined");
    }
}

QEXTMvvmAbstractModelListener::~QEXTMvvmAbstractModelListener()
{
    this->unsubscribe();
}

void QEXTMvvmAbstractModelListener::setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnDataChange(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnItemInserted(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnItemRemoved(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnAboutToRemoveItem(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnModelDestroyed(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnModelDestroyed(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnModelAboutToBeReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnModelAboutToBeReset(f, this);
    }
}

void QEXTMvvmAbstractModelListener::setOnModelReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->setOnModelReset(f, this);
    }
}

void QEXTMvvmAbstractModelListener::unsubscribe(QEXTMvvmSlot_t client)
{
    Q_UNUSED(client);
    if (m_model) {
        m_model->mapper()->unsubscribe(this);
    }
}

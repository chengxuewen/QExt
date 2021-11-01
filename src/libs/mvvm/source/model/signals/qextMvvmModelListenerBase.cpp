// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionModel.h>
#include <qextMvvmModelListenerBase.h>
#include <qextMvvmModelMapper.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmModelListenerBase::QEXTMvvmModelListenerBase(QEXTMvvmSessionModel* model) : m_model(model)
{
    if (!m_model)
        throw std::runtime_error("Error in QEXTMvvmModelListenerBase: no model defined");
    setOnModelDestroyed([this](QEXTMvvmSessionModel*) { m_model = nullptr; });
}

QEXTMvvmModelListenerBase::~QEXTMvvmModelListenerBase()
{
    unsubscribe();
}

//! Sets callback to be notified on item's data change. The callback will be called
//! with (QEXTMvvmSessionItem*, data_role).

void QEXTMvvmModelListenerBase::setOnDataChange(ModelView::Callbacks::item_int_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnDataChange(f, this);
}

//! Sets callback to be notified on item insert. The callback will be called with
//! (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes inserted child position.

void QEXTMvvmModelListenerBase::setOnItemInserted(ModelView::Callbacks::item_tagrow_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnItemInserted(f, this);
}

//! Sets callback to be notified on item remove. The callback will be called with
//! (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes child position before the removal.

void QEXTMvvmModelListenerBase::setOnItemRemoved(ModelView::Callbacks::item_tagrow_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnItemRemoved(f, this);
}

//! Sets callback to be notified when the item is about to be removed. The callback will be called
//! with (QEXTMvvmSessionItem* parent, tagrow), where 'tagrow' denotes child position being removed.

void QEXTMvvmModelListenerBase::setOnAboutToRemoveItem(ModelView::Callbacks::item_tagrow_t f,
                                               Callbacks::slot_t)
{
    m_model->mapper()->setOnAboutToRemoveItem(f, this);
}

//! Sets the callback for notifications on model destruction.

void QEXTMvvmModelListenerBase::setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelDestroyed(f, this);
}

//! Sets the callback to be notified before model's full reset (root item recreated).

void QEXTMvvmModelListenerBase::setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelAboutToBeReset(f, this);
}

//! Sets the callback to be notified after model was fully reset (root item recreated).

void QEXTMvvmModelListenerBase::setOnModelReset(ModelView::Callbacks::model_t f, Callbacks::slot_t)
{
    m_model->mapper()->setOnModelReset(f, this);
}

void QEXTMvvmModelListenerBase::unsubscribe(Callbacks::slot_t)
{
    if (m_model)
        m_model->mapper()->unsubscribe(this);
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELMAPPER_H
#define MVVM_SIGNALS_MODELMAPPER_H

#include <memory>
#include <qextMvvmModelListenerInterface.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class SessionModel;

//! Provides notifications on various SessionModel changes.
//! Allows to subscribe to SessionModel's changes, and triggers notifications.

class QEXT_MVVM_API ModelMapper : public ModelListenerInterface
{
public:
    ModelMapper(SessionModel* model);
    ~ModelMapper();

    ModelMapper(const ModelMapper& other) = delete;
    ModelMapper& operator=(const ModelMapper& other) = delete;

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client) override;
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client) override;
    void setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t client) override;
    void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client) override;

    void setActive(bool value);

    void unsubscribe(Callbacks::slot_t client) override;

private:
    friend class SessionModel;
    friend class QEXTMvvmSessionItem;

    void callOnDataChange(QEXTMvvmSessionItem* item, int role);
    void callOnItemInserted(QEXTMvvmSessionItem* parent, TagRow tagrow);
    void callOnItemRemoved(QEXTMvvmSessionItem* parent, TagRow tagrow);
    void callOnItemAboutToBeRemoved(QEXTMvvmSessionItem* parent, TagRow tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

    struct ModelMapperImpl;
    std::unique_ptr<ModelMapperImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELMAPPER_H

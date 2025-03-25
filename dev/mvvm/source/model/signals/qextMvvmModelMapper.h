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

#include <qextMvvmModelListenerInterface.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmSessionModel;

//! Provides notifications on various QExtMvvmSessionModel changes.
//! Allows to subscribe to QExtMvvmSessionModel's changes, and triggers notifications.

class QEXT_MVVM_API QExtMvvmModelMapper : public QExtMvvmModelListenerInterface {
public:
    QExtMvvmModelMapper(QExtMvvmSessionModel* model);
    ~QExtMvvmModelMapper();

    QExtMvvmModelMapper(const QExtMvvmModelMapper& other) = delete;
    QExtMvvmModelMapper& operator=(const QExtMvvmModelMapper& other) = delete;

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
    friend class QExtMvvmSessionModel;
    friend class QExtMvvmSessionItem;

    void callOnDataChange(QExtMvvmSessionItem* item, int role);
    void callOnItemInserted(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);
    void callOnItemRemoved(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);
    void callOnItemAboutToBeRemoved(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

    struct ModelMapperImpl;
    QExtUniquePointer<ModelMapperImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELMAPPER_H

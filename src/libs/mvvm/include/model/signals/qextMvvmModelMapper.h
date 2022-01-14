#ifndef _QEXTMVVMSIGNALSMODELMAPPER_H
#define _QEXTMVVMSIGNALSMODELMAPPER_H

#include <qextMvvmModelListenerInterface.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

//! Provides notifications on various SessionModel changes.
//! Allows to subscribe to SessionModel's changes, and triggers notifications.

class QEXT_MVVM_API QEXTMvvmModelMapper : public QEXTMvvmModelListenerInterface
{
public:
    QEXTMvvmModelMapper(QEXTMvvmSessionModel* model);
    ~QEXTMvvmModelMapper();

    QEXTMvvmModelMapper(const QEXTMvvmModelMapper& other) = delete;
    QEXTMvvmModelMapper& operator=(const QEXTMvvmModelMapper& other) = delete;

    void setOnDataChange(QEXTMvvmCallbacks::item_int_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnItemInserted(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnItemRemoved(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnAboutToRemoveItem(QEXTMvvmCallbacks::item_tagrow_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnModelDestroyed(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnModelAboutToBeReset(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client) override;
    void setOnModelReset(QEXTMvvmCallbacks::model_t f, QEXTMvvmCallbacks::slot_t client) override;

    void setActive(bool value);

    void unsubscribe(QEXTMvvmCallbacks::slot_t client) override;

private:
    friend class QEXTMvvmSessionModel;
    friend class QEXTMvvmSessionItem;

    void callOnDataChange(QEXTMvvmSessionItem* item, int role);
    void callOnItemInserted(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    void callOnItemRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    void callOnItemAboutToBeRemoved(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

    struct ModelMapperImpl;
    std::unique_ptr<ModelMapperImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSIGNALSMODELMAPPER_H

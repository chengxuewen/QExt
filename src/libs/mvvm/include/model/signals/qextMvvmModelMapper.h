#ifndef _QEXTMVVMMODELMAPPER_H
#define _QEXTMVVMMODELMAPPER_H

#include <memory>
#include <qextMvvmModelListenerInterface.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

//! Provides notifications on various QEXTMvvmSessionModel changes.
//! Allows to subscribe to QEXTMvvmSessionModel's changes, and triggers notifications.

class QEXT_MVVM_API QEXTMvvmModelMapper : public QEXTMvvmModelListenerInterface
{
public:
    QEXTMvvmModelMapper(QEXTMvvmSessionModel* model);
    ~QEXTMvvmModelMapper();

    QEXTMvvmModelMapper(const QEXTMvvmModelMapper& other) = delete;
    QEXTMvvmModelMapper& operator=(const QEXTMvvmModelMapper& other) = delete;

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

#endif // _QEXTMVVMMODELMAPPER_H

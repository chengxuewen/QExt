#ifndef QEXTMVVMMODELMAPPER_P_H
#define QEXTMVVMMODELMAPPER_P_H

#include <qextobject_p.h>
#include <qextmvvmglobal.h>
#include <qextmvvmcallback.h>



class QEXTMvvmModel;
class QEXTMvvmModelMapper;
class QEXT_MVVM_API QEXTMvvmModelMapperPrivate : public QEXTObjectPrivate
{
public:
    QEXTMvvmModelMapperPrivate(QEXTMvvmModelMapper *qq);
    ~QEXTMvvmModelMapperPrivate();

    void unsubscribe(QEXTMvvmSlot_t client);

    QEXTMvvmSignal<QEXTMvvmItem_int_t> m_on_data_change;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_item_inserted;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_item_removed;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_item_about_removed;
    QEXTMvvmSignal<QEXTMvvmModel_t> m_on_model_destroyed;
    QEXTMvvmSignal<QEXTMvvmModel_t> m_on_model_about_reset;
    QEXTMvvmSignal<QEXTMvvmModel_t> m_on_model_reset;

    bool m_active;
    QEXTMvvmModel *m_model;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmModelMapper)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmModelMapperPrivate)
};



#endif // QEXTMVVMMODELMAPPER_P_H

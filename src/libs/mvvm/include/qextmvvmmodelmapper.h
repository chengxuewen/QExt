#ifndef QEXTMVVMMODELMAPPER_H
#define QEXTMVVMMODELMAPPER_H

#include <qextmvvmglobal.h>
#include <qextmvvmmodellistenerinterface.h>
#include <qextmvvmtagrow.h>

#include <qextobject.h>



class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmModelMapperPrivate;
class QEXT_MVVM_API QEXTMvvmModelMapper : public QEXTMvvmModelListenerInterface, public QEXTObject
{
public:
    QEXTMvvmModelMapper(QEXTMvvmModel *model);
    ~QEXTMvvmModelMapper();

    void setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnModelDestroyed(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnModelAboutToBeReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void setOnModelReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client) QEXT_OVERRIDE;
    void unsubscribe(QEXTMvvmSlot_t client) QEXT_OVERRIDE;

    void setActive(bool value);

private:
    friend class QEXTMvvmItem;
    friend class QEXTMvvmModel;

    void callOnDataChange(QEXTMvvmItem *item, int role);
    void callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnItemAboutToBeRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

private:
    QEXT_DECLARE_PRIVATE(QEXTMvvmModelMapper)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmModelMapper)
};



#endif // QEXTMVVMMODELMAPPER_H

#ifndef QEXTMVVMABSTRACTMODELLISTENER_H
#define QEXTMVVMABSTRACTMODELLISTENER_H

#include <qextmvvmglobal.h>
#include <qextmvvmmodellistenerinterface.h>



class QEXTMvvmModel;
class QEXT_MVVM_API QEXTMvvmAbstractModelListener : public QEXTMvvmModelListenerInterface
{
public:
    QEXTMvvmAbstractModelListener(QEXTMvvmModel *model);
    ~QEXTMvvmAbstractModelListener() QEXT_OVERRIDE;

    void setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnModelDestroyed(QEXTMvvmModel_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnModelAboutToBeReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void setOnModelReset(QEXTMvvmModel_t f, QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;
    void unsubscribe(QEXTMvvmSlot_t client = QEXT_NULLPTR) QEXT_OVERRIDE;

protected:
    QEXTMvvmModel *m_model;
};



#endif // QEXTMVVMABSTRACTMODELLISTENER_H

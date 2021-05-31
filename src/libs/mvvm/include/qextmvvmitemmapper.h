#ifndef QEXTMVVMITEMMAPPER_H
#define QEXTMVVMITEMMAPPER_H

#include <qextmvvmglobal.h>
#include <qextmvvmitemlistenerinterface.h>
#include <qextmvvmmodellistener.h>

#include <qextobject.h>



class QEXTMvvmItem;
class QEXTMvvmItemMapperPrivate;
class QEXT_MVVM_API QEXTMvvmItemMapper : public QEXTMvvmItemListenerInterface, private QEXTMvvmModelListener<QEXTMvvmModel>, public QEXTObject
{
public:
    QEXTMvvmItemMapper(QEXTMvvmItem *item);
    ~QEXTMvvmItemMapper();

    void setOnItemDestroy(QEXTMvvmItem_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnDataChange(QEXTMvvmItem_int_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnChildPropertyChange(QEXTMvvmItem_str_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnItemInserted(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnItemRemoved(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f, QEXTMvvmSlot_t owner) QEXT_OVERRIDE;
    void unsubscribe(QEXTMvvmSlot_t client) = 0;

    void setActive(bool value);

private:
    friend class QEXTMvvmItem;
    QEXT_DECLARE_PRIVATE(QEXTMvvmItemMapper)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemMapper)
};



#endif // QEXTMVVMITEMMAPPER_H

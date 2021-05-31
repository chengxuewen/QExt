#ifndef QEXTMVVMABSTRACTITEMLISTENER_H
#define QEXTMVVMABSTRACTITEMLISTENER_H

#include <qextmvvmglobal.h>
#include <qextmvvmcallback.h>

#include <qextobject.h>



class QEXTMvvmItem;
class QEXTMvvmAbstractItemListenerPrivate;
class QEXT_MVVM_API QEXTMvvmAbstractItemListener : public QEXTObject
{
public:
    explicit QEXTMvvmAbstractItemListener(QEXTMvvmItem *item = QEXT_NULLPTR);
    virtual ~QEXTMvvmAbstractItemListener();

    void setItem(QEXTMvvmItem *item);

    void setOnItemDestroy(QEXTMvvmItem_t f);
    void setOnDataChange(QEXTMvvmItem_int_t f);
    void setOnPropertyChange(QEXTMvvmItem_str_t f);
    void setOnChildPropertyChange(QEXTMvvmItem_str_t f);
    void setOnItemInserted(QEXTMvvmItem_tagrow_t f);
    void setOnItemRemoved(QEXTMvvmItem_tagrow_t f);
    void setOnAboutToRemoveItem(QEXTMvvmItem_tagrow_t f);

protected:
    virtual void subscribe() {}   //! For necessary manipulations on new item.
    virtual void unsubscribe() {} //! For necessary manipulations on unsubscription.
    QEXTMvvmItem *item() const;

private:
    QEXT_DECLARE_PRIVATE(QEXTMvvmAbstractItemListener)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmAbstractItemListener)
};



#endif // QEXTMVVMABSTRACTITEMLISTENER_H

#ifndef QEXTMVVMABSTRACTITEMLISTENER_P_H
#define QEXTMVVMABSTRACTITEMLISTENER_P_H

#include <qextmvvmglobal.h>

#include <qextobject_p.h>



class QEXTMvvmItem;
class QEXTMvvmAbstractItemListener;
class QEXT_MVVM_API QEXTMvvmAbstractItemListenerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTMvvmAbstractItemListenerPrivate(QEXTMvvmAbstractItemListener *qq);
    ~QEXTMvvmAbstractItemListenerPrivate();

    void unsubscribeFromCurrent();

    QEXTMvvmItem *m_item;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmAbstractItemListener)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmAbstractItemListenerPrivate)
};




#endif // QEXTMVVMABSTRACTITEMLISTENER_P_H

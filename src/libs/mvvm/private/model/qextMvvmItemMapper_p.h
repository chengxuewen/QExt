#ifndef _QEXTMVVMITEMMAPPER_P_H
#define _QEXTMVVMITEMMAPPER_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmModelListener.h>

#include <qextSignal.h>
#include <qextFunction.h>
#include <qextConnection.h>

#include <QMultiMap>

class QEXTMvvmItem;
class QEXTMvvmItemMapper;
class QEXT_MVVM_API QEXTMvvmItemMapperPrivate
{
public:
    explicit QEXTMvvmItemMapperPrivate(QEXTMvvmItemMapper *q);
    virtual ~QEXTMvvmItemMapperPrivate();

    int nestlingDepth(QEXTMvvmItem* item, int level = 0);

    //! Processes signals from the model when item data changed.
    void processDataChange(QEXTMvvmItem* item, int role);

    void processItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);

    void processItemRemoved(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow);

    void processAboutToRemoveItem(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow);

    //! Notifies all callbacks subscribed to "item data is changed" event.
    void callOnDataChange(QEXTMvvmItem *item, int role);

    //! Notifies all callbacks subscribed to "item property is changed" event.
    void callOnPropertyChange(QEXTMvvmItem *item, QString property_name);

    //! Notifies all callbacks subscribed to "child property changed" event.
    void callOnChildPropertyChange(QEXTMvvmItem* item, QString property_name);

    //! Notifies all callbacks subscribed to "on row inserted" event.
    void callOnItemInserted(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow);

    //! Notifies all callbacks subscribed to "on row removed" event.
    void callOnItemRemoved(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow);

    //! Notifies all callbacks subscribed to "on row about to be removed".
    void callOnAboutToRemoveItem(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow);

    QEXTMvvmItemMapper * const q_ptr;

    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemAboutToBeInsertedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemInsertedSignal;

    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemAboutToBeRemovedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemRemovedSignal;

    QEXTSignal<void, QEXTMvvmItem *, QString> m_itemPropertyAboutToBeChangedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QString> m_itemPropertyChangedSignal;

    QEXTSignal<void, QEXTMvvmItem *, QString> m_itemChildPropertyAboutToBeChangedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QString> m_itemChildPropertyChangedSignal;

    QEXTSignal<void, QEXTMvvmItem *, int> m_itemDataAboutToBeChangedSignal;
    QEXTSignal<void, QEXTMvvmItem *, int> m_itemDataChangedSignal;

    QEXTSignal<void, QEXTMvvmItem *> m_itemAboutToBeDestroyedSignal;
    QEXTSignal<void, QEXTMvvmItem *> m_itemDestroyedSignal;

    QEXTSignal<void, QEXTMvvmModel *> m_modelAboutToBeDestroyedSignal;
    QEXTSignal<void, QEXTMvvmModel *> m_modelDestroyedSignal;

    QEXTSignal<void, QEXTMvvmItem *> m_modelAboutToBeResetedSignal;
    QEXTSignal<void, QEXTMvvmItem *> m_modelResetedSignal;

    QMultiMap<void *, QEXTConnection> m_lisenterConnectionMap;

    bool m_active;
    QEXTMvvmItem *m_item;
    QScopedPointer<QEXTMvvmModelListener<QEXTMvvmModel> > m_modelListener;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemMapperPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmItemMapper)
};

#endif // _QEXTMVVMITEMMAPPER_P_H

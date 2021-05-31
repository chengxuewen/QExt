#ifndef QEXTMVVMITEMMAPPER_P_H
#define QEXTMVVMITEMMAPPER_P_H

#include <qextmvvmglobal.h>
#include <qextmvvmcallback.h>
#include <qextmvvmtagrow.h>

#include <qextobject_p.h>



class QEXTMvvmItem;
class QEXTMvvmItemMapper;
class QEXT_MVVM_API QEXTMvvmItemMapperPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTMvvmItemMapperPrivate(QEXTMvvmItemMapper *qq);
    ~QEXTMvvmItemMapperPrivate();

    void unsubscribe(QEXTMvvmSlot_t client);
    int nestlingDepth(QEXTMvvmItem *item, int level = 0);
    void processDataChange(QEXTMvvmItem *item, int role);
    void processItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void processItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void processAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnDataChange(QEXTMvvmItem *item, int role);
    void callOnPropertyChange(QEXTMvvmItem *item, std::string property_name);
    void callOnChildPropertyChange(QEXTMvvmItem *item, std::string property_name);
    void callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnAboutToRemoveItem(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);

    QEXTMvvmSignal<QEXTMvvmItem_int_t> m_on_item_destroy;
    QEXTMvvmSignal<QEXTMvvmItem_int_t> m_on_data_change;
    QEXTMvvmSignal<QEXTMvvmItem_str_t> m_on_property_change;
    QEXTMvvmSignal<QEXTMvvmItem_str_t> m_on_child_property_change;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_item_inserted;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_item_removed;
    QEXTMvvmSignal<QEXTMvvmItem_tagrow_t> m_on_about_to_remove_item;

    bool m_active;
    QEXTMvvmItem *m_item;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmItemMapper)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemMapperPrivate)
};



#endif // QEXTMVVMITEMMAPPER_P_H

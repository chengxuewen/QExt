#ifndef QEXTMVVMITEMCONTAINER_P_H
#define QEXTMVVMITEMCONTAINER_P_H

#include <qextmvvmglobal.h>
#include <qextmvvmitemcontainer.h>
#include <qextmvvmtaginfo.h>

#include <qextobject_p.h>



class QEXTMvvmItem;
class QEXTMvvmTagInfo;
class QEXTMvvmItemContainer;
class QEXT_MVVM_API QEXTMvvmItemContainerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTMvvmItemContainerPrivate(QEXTMvvmItemContainer *qq);
    ~QEXTMvvmItemContainerPrivate();

    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const QEXTMvvmItem *item) const;

    QEXTMvvmTagInfo m_tag_info;
    QEXTMvvmItemContainer::container_t m_items;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmItemContainer)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemContainerPrivate)
};



#endif // QEXTMVVMITEMCONTAINER_P_H

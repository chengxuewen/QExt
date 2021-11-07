#ifndef _QEXTMVVMITEMCONTAINER_P_H
#define _QEXTMVVMITEMCONTAINER_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItemContainer.h>
#include <qextMvvmTagInfo.h>

class QEXTMvvmItemContainer;
class QEXT_MVVM_API QEXTMvvmItemContainerPrivate
{
public:
    explicit QEXTMvvmItemContainerPrivate(QEXTMvvmItemContainer *q);
    virtual ~QEXTMvvmItemContainerPrivate();

    QEXTMvvmItemContainer * const q_ptr;

    QEXTMvvmTagInfo m_tagInfo;
    QEXTMvvmItemContainer::ItemVector m_itemVector;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemContainerPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmItemContainer)
};

#endif // _QEXTMVVMITEMCONTAINER_P_H

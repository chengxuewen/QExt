#ifndef _QEXTMVVMCONTAINERITEM_H
#define _QEXTMVVMCONTAINERITEM_H

#include <qextMvvmCompoundItem.h>

//! Simple container to store any type of children.
//! Used as convenience item to create branch with uniform children beneath.

class QEXT_MVVM_API QEXTMvvmContainerItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString T_ITEMS = "T_ITEMS";

    QEXTMvvmContainerItem(const QString& modelType = QEXTMvvmConstants::ContainerItemType);

    bool empty() const;

    size_t size() const;
};

#endif // _QEXTMVVMCONTAINERITEM_H

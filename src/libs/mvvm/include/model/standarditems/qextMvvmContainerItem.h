#ifndef _QEXTMVVMCONTAINERITEM_H
#define _QEXTMVVMCONTAINERITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

//! Simple container to store any type of children.
//! Used as convenience item to create branch with uniform children beneath.

class QEXT_MVVM_API QEXTMvvmContainerItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string T_ITEMS = "T_ITEMS";

    QEXTMvvmContainerItem(const std::string& modelType = Constants::ContainerItemType);

    bool empty() const;

    size_t size() const;
};

} // namespace ModelView

#endif // _QEXTMVVMCONTAINERITEM_H

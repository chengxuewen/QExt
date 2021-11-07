// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmContainerItem.h>



QEXTMvvmContainerItem::QEXTMvvmContainerItem(const QString& modelType) : QEXTMvvmCompoundItem(modelType)
{
    registerTag(QEXTMvvmTagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}

bool QEXTMvvmContainerItem::empty() const
{
    return childrenCount() == 0;
}

size_t QEXTMvvmContainerItem::size() const
{
    return static_cast<size_t>(childrenCount());
}

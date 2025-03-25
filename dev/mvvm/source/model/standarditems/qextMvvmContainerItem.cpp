// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmContainerItem.h>

using namespace ModelView;

QExtMvvmContainerItem::QExtMvvmContainerItem(const std::string& modelType) : QExtMvvmCompoundItem(modelType)
{
    registerTag(ModelView::QExtMvvmTagInfo::universalTag(T_ITEMS), /*set_as_default*/ true);
}

bool QExtMvvmContainerItem::empty() const
{
    return childrenCount() == 0;
}

size_t QExtMvvmContainerItem::size() const
{
    return static_cast<size_t>(childrenCount());
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCompoundItem.h>
#include <qextMvvmItemUtils.h>

using namespace ModelView;

namespace
{
bool has_custom_display_name(const QEXTMvvmSessionItem* item)
{
    return item->QEXTMvvmSessionItem::displayName() != item->modelType();
}
} // namespace

QEXTMvvmCompoundItem::QEXTMvvmCompoundItem(const std::string& modelType) : QEXTMvvmSessionItem(modelType) {}

std::string QEXTMvvmCompoundItem::displayName() const
{
    if (has_custom_display_name(this))
        return QEXTMvvmSessionItem::displayName();

    int copy_number = QEXTMvvmUtils::CopyNumber(this);
    return copy_number != -1 ? QEXTMvvmSessionItem::displayName() + std::to_string(copy_number)
                             : QEXTMvvmSessionItem::displayName();
}

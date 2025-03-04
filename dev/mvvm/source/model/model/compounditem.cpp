// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/compounditem.h"
#include "model/model/itemutils.h"

using namespace ModelView;

namespace {
bool has_custom_display_name(const QExtMvvmSessionItem* item)
{
    return item->QExtMvvmSessionItem::displayName() != item->modelType();
}
} // namespace

QExtMvvmCompoundItem::QExtMvvmCompoundItem(const std::string& modelType) : QExtMvvmSessionItem(modelType) {}

std::string QExtMvvmCompoundItem::displayName() const
{
    if (has_custom_display_name(this))
        return QExtMvvmSessionItem::displayName();

    int copy_number = Utils::CopyNumber(this);
    return copy_number != -1 ? QExtMvvmSessionItem::displayName() + std::to_string(copy_number)
                             : QExtMvvmSessionItem::displayName();
}

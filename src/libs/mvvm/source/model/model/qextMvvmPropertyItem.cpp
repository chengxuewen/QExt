// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomVariants.h>
#include <qextMvvmTypes.h>
#include <qextMvvmPropertyItem.h>

using namespace ModelView;

PropertyItem::PropertyItem() : QEXTMvvmSessionItem(Constants::PropertyType) {}

PropertyItem* PropertyItem::setDisplayName(const std::string& name)
{
    QEXTMvvmSessionItem::setDisplayName(name);
    return this;
}

PropertyItem* PropertyItem::setLimits(const RealLimits& value)
{
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}

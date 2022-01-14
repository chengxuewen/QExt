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

QEXTMvvmPropertyItem::QEXTMvvmPropertyItem() : QEXTMvvmSessionItem(QEXTMvvmConstants::PropertyType) {}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setDisplayName(const std::string& name)
{
    QEXTMvvmSessionItem::setDisplayName(name);
    return this;
}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setLimits(const QEXTMvvmRealLimits& value)
{
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}

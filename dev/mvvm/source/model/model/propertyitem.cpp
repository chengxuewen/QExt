// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/propertyitem.h"
#include "model/model/mvvm_types.h"

using namespace ModelView;

QExtMvvmPropertyItem::QExtMvvmPropertyItem() : QExtMvvmSessionItem(Constants::PropertyType) {}

QExtMvvmPropertyItem* QExtMvvmPropertyItem::setDisplayName(const std::string& name)
{
    QExtMvvmSessionItem::setDisplayName(name);
    return this;
}

QExtMvvmPropertyItem* QExtMvvmPropertyItem::setLimits(const QExtMvvmRealLimits& value)
{
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}

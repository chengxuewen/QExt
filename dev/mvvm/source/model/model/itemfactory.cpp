// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/itemfactory.h"
#include "model/model/itemcatalogue.h"
#include "model/model/sessionitem.h"

using namespace ModelView;

QExtMvvmItemFactory::QExtMvvmItemFactory(QExtUniquePointer<QExtMvvmItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

void QExtMvvmItemFactory::registerItem(const std::string& modelType, QExtMvvmItemFactoryFunc func,
                               const std::string& label)
{
    m_catalogue->registerItem(modelType, func, label);
}

QExtMvvmItemFactory::~QExtMvvmItemFactory() = default;

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmItemFactory::createItem(const QExtMvvmModelType& modelType) const
{
    return m_catalogue->create(modelType);
}

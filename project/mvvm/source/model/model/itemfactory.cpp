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

ItemFactory::ItemFactory(QExtUniquePointer<ItemCatalogue> catalogue)
    : m_catalogue(std::move(catalogue))
{
}

void ItemFactory::registerItem(const std::string& modelType, item_factory_func_t func,
                               const std::string& label)
{
    m_catalogue->registerItem(modelType, func, label);
}

ItemFactory::~ItemFactory() = default;

QExtUniquePointer<SessionItem> ItemFactory::createItem(const model_type& modelType) const
{
    return m_catalogue->create(modelType);
}

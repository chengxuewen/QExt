// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsonitemcopystrategy.h"
#include "model/factories/itemconverterfactory.h"
#include "model/model/sessionitem.h"
#include <QJsonObject>

using namespace ModelView;

struct JsonItemCopyStrategy::JsonItemCopyStrategyImpl {
    std::unique_ptr<JsonItemConverterInterface> m_converter;
};

JsonItemCopyStrategy::JsonItemCopyStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemCopyStrategyImpl>())
{
    p_impl->m_converter = CreateItemCopyConverter(item_factory);
}

JsonItemCopyStrategy::~JsonItemCopyStrategy() = default;

std::unique_ptr<SessionItem> JsonItemCopyStrategy::createCopy(const SessionItem* item) const
{
    auto json = p_impl->m_converter->to_json(item);
    return p_impl->m_converter->from_json(json);
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsonitembackupstrategy.h"
#include "model/factories/itemconverterfactory.h"
#include "model/model/sessionitem.h"
#include <QJsonObject>

using namespace ModelView;

struct JsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    std::unique_ptr<JsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

JsonItemBackupStrategy::JsonItemBackupStrategy(const ItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemBackupStrategyImpl>())
{
    p_impl->m_converter = CreateItemCloneConverter(item_factory);
}

JsonItemBackupStrategy::~JsonItemBackupStrategy() = default;

std::unique_ptr<SessionItem> JsonItemBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void JsonItemBackupStrategy::saveItem(const SessionItem* item)
{
    p_impl->m_json = p_impl->m_converter->to_json(item);
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmJsonItemBackupStrategy.h>
#include <qextMvvmItemConverterFactory.h>
#include <qextMvvmSessionItem.h>
#include <QJsonObject>

using namespace ModelView;

struct JsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    QExtUniquePointer<QExtMvvmJsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

JsonItemBackupStrategy::JsonItemBackupStrategy(const QExtMvvmItemFactoryInterface* item_factory)
    : p_impl(qextMakeUnique<JsonItemBackupStrategyImpl>())
{
    p_impl->m_converter = qextMvvmCreateItemCloneConverter(item_factory);
}

JsonItemBackupStrategy::~JsonItemBackupStrategy() = default;

QExtUniquePointer<QExtMvvmSessionItem> JsonItemBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void JsonItemBackupStrategy::saveItem(const QExtMvvmSessionItem* item)
{
    p_impl->m_json = p_impl->m_converter->to_json(item);
}

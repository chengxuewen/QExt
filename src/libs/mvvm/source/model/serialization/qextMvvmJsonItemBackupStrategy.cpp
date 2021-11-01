// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonObject>
#include <qextMvvmItemConverterFactory.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmJsonItemBackupStrategy.h>

using namespace ModelView;

struct QEXTMvvmJsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    std::unique_ptr<QEXTMvvmJsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

QEXTMvvmJsonItemBackupStrategy::QEXTMvvmJsonItemBackupStrategy(const QEXTMvvmItemFactoryInterface* item_factory)
    : p_impl(std::make_unique<JsonItemBackupStrategyImpl>())
{
    p_impl->m_converter = CreateItemCloneConverter(item_factory);
}

QEXTMvvmJsonItemBackupStrategy::~QEXTMvvmJsonItemBackupStrategy() = default;

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmJsonItemBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->from_json(p_impl->m_json);
}

void QEXTMvvmJsonItemBackupStrategy::saveItem(const QEXTMvvmSessionItem* item)
{
    p_impl->m_json = p_impl->m_converter->to_json(item);
}

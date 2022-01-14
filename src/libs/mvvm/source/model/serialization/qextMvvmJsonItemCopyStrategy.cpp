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
#include <serialization/qextMvvmJsonItemCopyStrategy.h>

using namespace ModelView;

struct QEXTMvvmJsonItemCopyStrategy::JsonItemCopyStrategyImpl {
    std::unique_ptr<QEXTMvvmJsonItemConverterInterface> m_converter;
};

QEXTMvvmJsonItemCopyStrategy::QEXTMvvmJsonItemCopyStrategy(const QEXTMvvmItemFactoryInterface* item_factory)
    : p_impl(make_unique<JsonItemCopyStrategyImpl>())
{
    p_impl->m_converter = CreateItemCopyConverter(item_factory);
}

QEXTMvvmJsonItemCopyStrategy::~QEXTMvvmJsonItemCopyStrategy() = default;

std::unique_ptr<QEXTMvvmSessionItem> QEXTMvvmJsonItemCopyStrategy::createCopy(const QEXTMvvmSessionItem* item) const
{
    auto json = p_impl->m_converter->to_json(item);
    return p_impl->m_converter->from_json(json);
}

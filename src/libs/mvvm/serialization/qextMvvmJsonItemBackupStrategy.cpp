// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItem.h>
#include <qextMvvmFactory.h>
#include <qextMvvmJsonItemBackupStrategy.h>
#include <qextMvvmJsonItemConverterInterface.h>

#include <QJsonObject>
#include <QScopedPointer>


struct QEXTMvvmJsonItemBackupStrategy::JsonItemBackupStrategyImpl {
    QScopedPointer<QEXTMvvmJsonItemConverterInterface> m_converter;
    QJsonObject m_json;
};

QEXTMvvmJsonItemBackupStrategy::QEXTMvvmJsonItemBackupStrategy(const QEXTMvvmItemFactoryInterface* item_factory)
    : p_impl(new JsonItemBackupStrategyImpl)
{
    p_impl->m_converter.reset(QEXTMvvmFactory::createItemCloneConverter(item_factory));
}

QEXTMvvmJsonItemBackupStrategy::~QEXTMvvmJsonItemBackupStrategy()
{

}

QEXTMvvmItem *QEXTMvvmJsonItemBackupStrategy::restoreItem() const
{
    return p_impl->m_converter->fromJson(p_impl->m_json);
}

void QEXTMvvmJsonItemBackupStrategy::saveItem(const QEXTMvvmItem* item)
{
    p_impl->m_json = p_impl->m_converter->toJson(item);
}

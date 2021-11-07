#include <qextMvvmItem.h>
#include <qextMvvmJsonItemCopyStrategy.h>
#include <qextMvvmJsonItemConverterInterface.h>
#include <qextMvvmFactory.h>

#include <QJsonObject>


struct QEXTMvvmJsonItemCopyStrategy::JsonItemCopyStrategyImpl {
    QScopedPointer<QEXTMvvmJsonItemConverterInterface> m_converter;
};

QEXTMvvmJsonItemCopyStrategy::QEXTMvvmJsonItemCopyStrategy(const QEXTMvvmItemFactoryInterface* item_factory)
    : p_impl(new JsonItemCopyStrategyImpl)
{
    p_impl->m_converter.reset(QEXTMvvmFactory::createItemCopyConverter(item_factory));
}

QEXTMvvmJsonItemCopyStrategy::~QEXTMvvmJsonItemCopyStrategy()
{

}

QEXTMvvmItem *QEXTMvvmJsonItemCopyStrategy::createCopy(const QEXTMvvmItem* item) const
{
    auto json = p_impl->m_converter->toJson(item);
    return p_impl->m_converter->fromJson(json);
}

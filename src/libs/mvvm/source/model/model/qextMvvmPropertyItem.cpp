#include <qextMvvmCustomVariants.h>
#include <qextMvvmConstants.h>
#include <qextMvvmPropertyItem.h>

using namespace ModelView;

QEXTMvvmPropertyItem::QEXTMvvmPropertyItem() : QEXTMvvmSessionItem(Constants::PropertyType) {}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setDisplayName(const std::string& name)
{
    QEXTMvvmSessionItem::setDisplayName(name);
    return this;
}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setLimits(const QEXTMvvmRealLimits& value)
{
    this->setData(value, ItemDataRole::LIMITS);
    return this;
}

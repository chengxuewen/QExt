#include <qextMvvmUtils.h>
#include <qextMvvmConstants.h>
#include <qextMvvmPropertyItem.h>



QEXTMvvmPropertyItem::QEXTMvvmPropertyItem() : QEXTMvvmItem(QEXTMvvmConstants::PropertyType) {}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setDisplayName(const QString& name)
{
    QEXTMvvmItem::setDisplayName(name);
    return this;
}

QEXTMvvmPropertyItem* QEXTMvvmPropertyItem::setLimits(const QEXTMvvmRealLimits& value)
{
    this->setData(value, QEXTMvvmItem::Role_Limits);
    return this;
}

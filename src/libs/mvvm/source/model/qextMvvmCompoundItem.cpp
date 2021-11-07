#include <qextMvvmCompoundItem.h>
#include <qextMvvmUtils.h>

namespace
{
    bool qextMvvmHasCustomDisplayName(const QEXTMvvmItem *item)
    {
        return item->QEXTMvvmItem::displayName() != item->modelType();
    }
} // namespace

QEXTMvvmCompoundItem::QEXTMvvmCompoundItem(const QString &modelType)
    : QEXTMvvmItem(modelType)
{

}

QString QEXTMvvmCompoundItem::displayName() const
{
    if (qextMvvmHasCustomDisplayName(this))
    {
        return QEXTMvvmItem::displayName();
    }

    int copyNumber = QEXTMvvmUtils::copyNumber(this);
    return copyNumber != -1 ? QEXTMvvmItem::displayName() + QString::number(copyNumber) : QEXTMvvmItem::displayName();
}

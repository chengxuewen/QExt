#include <qextMvvmLinkedItem.h>
#include <qextMvvmUtils.h>



namespace
{
const QVariant empty_link = QVariant::fromValue(QString());
}

QEXTMvvmLinkedItem::QEXTMvvmLinkedItem() : QEXTMvvmItem(QEXTMvvmConstants::LinkedItemType)
{
    setData(empty_link);
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void QEXTMvvmLinkedItem::setLink(const QEXTMvvmItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : empty_link);
}

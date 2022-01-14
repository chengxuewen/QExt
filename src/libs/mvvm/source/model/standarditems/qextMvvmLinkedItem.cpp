// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomVariants.h>
#include <qextMvvmLinkedItem.h>

using namespace ModelView;

namespace
{
const QVariant empty_link = QVariant::fromValue(std::string());
}

QEXTMvvmLinkedItem::QEXTMvvmLinkedItem() : QEXTMvvmSessionItem(QEXTMvvmConstants::LinkedItemType)
{
    setData(empty_link);
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void QEXTMvvmLinkedItem::setLink(const QEXTMvvmSessionItem* item)
{
    setData(item ? QVariant::fromValue(item->identifier()) : empty_link);
}

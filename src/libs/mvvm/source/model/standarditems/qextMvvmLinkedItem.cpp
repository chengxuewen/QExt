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
const Variant empty_link = Variant::fromValue(std::string());
}

LinkedItem::LinkedItem() : QEXTMvvmSessionItem(Constants::LinkedItemType)
{
    setData(empty_link);
    setEditable(false); // prevent editing in widgets, link is set programmatically.
}

//! Set link to given item.

void LinkedItem::setLink(const QEXTMvvmSessionItem* item)
{
    setData(item ? Variant::fromValue(item->identifier()) : empty_link);
}

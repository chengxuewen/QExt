// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleitems.h"
#include <QColor>
#include <qextMvvmComboProperty.h>
#include <qextMvvmExternalProperty.h>

namespace
{

const std::string DemoItemType = "DemoItem";
const std::string DemoContainerItemType = "DemoItemContainer";

} // namespace

using namespace ModelView;

namespace DragAndView
{

DemoItem::DemoItem() : QEXTMvvmCompoundItem(DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}

DemoContainerItem::DemoContainerItem() : QEXTMvvmCompoundItem(DemoContainerItemType)
{
    registerTag(QEXTMvvmTagInfo::universalTag(T_ITEMS, {DemoItemType}), /*set_default*/ true);
}

} // namespace DragAndView

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmComboProperty.h>
#include <qextMvvmColorMapItem.h>
#include <qextMvvmData2dItem.h>
#include <qextMvvmLinkedItem.h>
#include <qextMvvmPlotTableItems.h>

using namespace ModelView;

namespace
{
const QEXTMvvmComboProperty gradientCombo =
    QEXTMvvmComboProperty::createFrom({"Grayscale", "Hot", "Cold", "Night", "Candy", "Geography", "Ion",
                               "Thermal", "Polar", "Spectrum", "Jet", "Hues"},
                              "Polar");
}

QEXTMvvmColorMapItem::QEXTMvvmColorMapItem() : QEXTMvvmCompoundItem(Constants::ColorMapItemType)
{
    addProperty<QEXTMvvmLinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<QEXTMvvmTextItem>(P_TITLE)->setDisplayName("Title");
    addProperty(P_GRADIENT, gradientCombo)->setDisplayName("Gradient");
    addProperty(P_INTERPOLATION, true)->setDisplayName("Interpolation");
}

//! Sets link to the data item.

void QEXTMvvmColorMapItem::setDataItem(const QEXTMvvmData2DItem* data_item)
{
    item<QEXTMvvmLinkedItem>(P_LINK)->setLink(data_item);
}

//! Returns data item linked to the given QEXTMvvmColorMapItem.

QEXTMvvmData2DItem* QEXTMvvmColorMapItem::dataItem() const
{
    return item<QEXTMvvmLinkedItem>(P_LINK)->get<QEXTMvvmData2DItem>();
}

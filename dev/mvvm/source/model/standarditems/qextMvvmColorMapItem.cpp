// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmColorMapItem.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmData2DItem.h>
#include <qextMvvmLinkedItem.h>
#include <qextMvvmPlotTableItems.h>

using namespace ModelView;

namespace {
const QExtMvvmComboProperty gradientCombo =
    QExtMvvmComboProperty::createFrom({"Grayscale", "Hot", "Cold", "Night", "Candy", "Geography", "Ion",
                               "Thermal", "Polar", "Spectrum", "Jet", "Hues"},
                              "Polar");
}

QExtMvvmColorMapItem::QExtMvvmColorMapItem() : QExtMvvmCompoundItem(Constants::ColorMapItemType)
{
    addProperty<QExtMvvmLinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<QExtMvvmTextItem>(P_TITLE)->setDisplayName("Title");
    addProperty(P_GRADIENT, gradientCombo)->setDisplayName("Gradient");
    addProperty(P_INTERPOLATION, true)->setDisplayName("Interpolation");
}

//! Sets link to the data item.

void QExtMvvmColorMapItem::setDataItem(const QExtMvvmData2DItem* data_item)
{
    item<QExtMvvmLinkedItem>(P_LINK)->setLink(data_item);
}

//! Returns data item linked to the given QExtMvvmColorMapItem.

QExtMvvmData2DItem* QExtMvvmColorMapItem::dataItem() const
{
    return item<QExtMvvmLinkedItem>(P_LINK)->get<QExtMvvmData2DItem>();
}

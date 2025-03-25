// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGraphItem.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmData1DItem.h>
#include <qextMvvmLinkedItem.h>
#include <qextMvvmPlotTableItems.h>
#include <QColor>

using namespace ModelView;

QExtMvvmGraphItem::QExtMvvmGraphItem(const std::string& QExtMvvmModelType) : QExtMvvmCompoundItem(QExtMvvmModelType)
{
    addProperty<QExtMvvmLinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<QExtMvvmTextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
    addProperty<QExtMvvmPenItem>(P_PEN)->setDisplayName("Pen");
    addProperty(P_DISPLAYED, true)->setDisplayName("Displayed");
}

//! Sets link to the data item.

void QExtMvvmGraphItem::setDataItem(const QExtMvvmData1DItem* data_item)
{
    item<QExtMvvmLinkedItem>(P_LINK)->setLink(data_item);
}

//! Update item from the content of given graph. Link to the data will be set
//! as in given item, other properties copied.

void QExtMvvmGraphItem::setFromGraphItem(const QExtMvvmGraphItem* graph_item)
{
    setDataItem(graph_item->dataItem());
    auto pen = item<QExtMvvmPenItem>(P_PEN);
    auto source_pen = graph_item->item<QExtMvvmPenItem>(P_PEN);
    pen->setProperty(QExtMvvmPenItem::P_COLOR, source_pen->property<QColor>(QExtMvvmPenItem::P_COLOR));
    pen->setProperty(QExtMvvmPenItem::P_STYLE, source_pen->property<QExtMvvmComboProperty>(QExtMvvmPenItem::P_STYLE));
    pen->setProperty(QExtMvvmPenItem::P_WIDTH, source_pen->property<int>(QExtMvvmPenItem::P_WIDTH));
}

//! Returns data item linked to the given QExtMvvmGraphItem.

QExtMvvmData1DItem* QExtMvvmGraphItem::dataItem() const
{
    return item<QExtMvvmLinkedItem>(P_LINK)->get<QExtMvvmData1DItem>();
}

std::vector<double> QExtMvvmGraphItem::binCenters() const
{
    return dataItem() ? dataItem()->binCenters() : std::vector<double>();
}

std::vector<double> QExtMvvmGraphItem::binValues() const
{
    return dataItem() ? dataItem()->binValues() : std::vector<double>();
}

std::vector<double> QExtMvvmGraphItem::binErrors() const
{
    return dataItem() ? dataItem()->binErrors() : std::vector<double>();
}

//! Returns color name in #RRGGBB format.

std::string QExtMvvmGraphItem::colorName() const
{
    return penItem()->colorName();
}

//! Sets named color following schema from https://www.w3.org/TR/css-color-3/#svg-color.
//! e.g. "mediumaquamarine"

void QExtMvvmGraphItem::setNamedColor(const std::string& named_color)
{
    penItem()->setNamedColor(named_color);
}

QExtMvvmPenItem* QExtMvvmGraphItem::penItem() const
{
    return item<QExtMvvmPenItem>(P_PEN);
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <qextMvvmComboProperty.h>
#include <qextMvvmData1DItem.h>
#include <qextMvvmGraphItem.h>
#include <qextMvvmLinkedItem.h>
#include <qextMvvmPlotTableItems.h>

using namespace ModelView;

QEXTMvvmGraphItem::QEXTMvvmGraphItem(const std::string& model_type) : QEXTMvvmCompoundItem(model_type)
{
    addProperty<QEXTMvvmLinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<QEXTMvvmTextItem>(P_GRAPH_TITLE)->setDisplayName("Graph title");
    addProperty<QEXTMvvmPenItem>(P_PEN)->setDisplayName("Pen");
    addProperty(P_DISPLAYED, true)->setDisplayName("Displayed");
}

//! Sets link to the data item.

void QEXTMvvmGraphItem::setDataItem(const QEXTMvvmData1DItem* data_item)
{
    item<QEXTMvvmLinkedItem>(P_LINK)->setLink(data_item);
}

//! Update item from the content of given graph. Link to the data will be set
//! as in given item, other properties copied.

void QEXTMvvmGraphItem::setFromGraphItem(const QEXTMvvmGraphItem* graph_item)
{
    setDataItem(graph_item->dataItem());
    auto pen = item<QEXTMvvmPenItem>(P_PEN);
    auto source_pen = graph_item->item<QEXTMvvmPenItem>(P_PEN);
    pen->setProperty(QEXTMvvmPenItem::P_COLOR, source_pen->property<QColor>(QEXTMvvmPenItem::P_COLOR));
    pen->setProperty(QEXTMvvmPenItem::P_STYLE, source_pen->property<QEXTMvvmComboProperty>(QEXTMvvmPenItem::P_STYLE));
    pen->setProperty(QEXTMvvmPenItem::P_WIDTH, source_pen->property<int>(QEXTMvvmPenItem::P_WIDTH));
}

//! Returns data item linked to the given GraphItem.

QEXTMvvmData1DItem* QEXTMvvmGraphItem::dataItem() const
{
    return item<QEXTMvvmLinkedItem>(P_LINK)->get<QEXTMvvmData1DItem>();
}

std::vector<double> QEXTMvvmGraphItem::binCenters() const
{
    return dataItem() ? dataItem()->binCenters() : std::vector<double>();
}

std::vector<double> QEXTMvvmGraphItem::binValues() const
{
    return dataItem() ? dataItem()->binValues() : std::vector<double>();
}

std::vector<double> QEXTMvvmGraphItem::binErrors() const
{
    return dataItem() ? dataItem()->binErrors() : std::vector<double>();
}

//! Returns color name in #RRGGBB format.

std::string QEXTMvvmGraphItem::colorName() const
{
    return penItem()->colorName();
}

//! Sets named color following schema from https://www.w3.org/TR/css-color-3/#svg-color.
//! e.g. "mediumaquamarine"

void QEXTMvvmGraphItem::setNamedColor(const std::string& named_color)
{
    penItem()->setNamedColor(named_color);
}

QEXTMvvmPenItem* QEXTMvvmGraphItem::penItem() const
{
    return item<QEXTMvvmPenItem>(P_PEN);
}

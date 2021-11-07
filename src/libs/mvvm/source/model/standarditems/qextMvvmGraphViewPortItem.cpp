// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <qextMvvmGraphItem.h>
#include <qextMvvmGraphViewPortItem.h>
#include <QVector>



namespace
{

const double failback_min = 0.0;
const double failback_max = 1.0;

//! Find min and max values along all data points in all graphs.
//! Function 'func' is used to run either through binCenters or binValues.

template <typename T> auto get_min_max(const QVector<QEXTMvvmGraphItem*> &graphs, T func)
{
    QVector<double> values;
    for (auto graph : graphs) {
        const auto array = func(graph);
        std::copy(std::begin(array), std::end(array), std::back_inserter(values));
    }

    auto [xmin, xmax] = std::minmax_element(std::begin(values), std::end(values));
    return xmin != xmax ? QPair<double, double>(*xmin, *xmax) : QPair<double, double>(failback_min, failback_max);
}

} // namespace

QEXTMvvmGraphViewportItem::QEXTMvvmGraphViewportItem(const QString& QString) : QEXTMvvmViewportItem(QString)
{
    register_xy_axes();
    registerTag(QEXTMvvmTagInfo::universalTag(T_ITEMS, {QEXTMvvmConstants::GraphItemType}), /*set_default*/ true);
}

//! Returns the selected graph items.

QVector<QEXTMvvmGraphItem*> QEXTMvvmGraphViewportItem::graphItems() const
{
    return items<QEXTMvvmGraphItem>(T_ITEMS);
}

//! Returns the selected graph items.

QVector<QEXTMvvmGraphItem *> QEXTMvvmGraphViewportItem::visibleGraphItems() const
{
    QVector<QEXTMvvmGraphItem*> all_items = items<QEXTMvvmGraphItem>(T_ITEMS);
    QVector<QEXTMvvmGraphItem*> visible_items;
    std::copy_if(all_items.begin(), all_items.end(), std::back_inserter(visible_items),
                 [](const QEXTMvvmGraphItem* graph_item) {
                     return graph_item->property<bool>(QEXTMvvmGraphItem::P_DISPLAYED);
                 });
    return visible_items;
}

//! Set the graph selection.

void QEXTMvvmGraphViewportItem::setVisible(const QVector<QEXTMvvmGraphItem*>& visible_graph_items)
{
    QVector<QEXTMvvmGraphItem*> output;
    for (auto graph_item : items<QEXTMvvmGraphItem>(T_ITEMS)) {
        if (std::find(visible_graph_items.begin(), visible_graph_items.end(), graph_item)
            != visible_graph_items.end())
            graph_item->setProperty(QEXTMvvmGraphItem::P_DISPLAYED, true);
        else
            graph_item->setProperty(QEXTMvvmGraphItem::P_DISPLAYED, false);
    }
}

//! Reset the graph selection.

void QEXTMvvmGraphViewportItem::setAllVisible()
{
    for (auto graph_item : items<QEXTMvvmGraphItem>(T_ITEMS))
        graph_item->setProperty(QEXTMvvmGraphItem::P_DISPLAYED, true);
}

//! Returns lower, upper range on x-axis occupied by all data points of all graphs.

QPair<double, double> QEXTMvvmGraphViewportItem::dataXAxisRange() const
{
    return get_min_max(visibleGraphItems(), [](QEXTMvvmGraphItem *graph) { return graph->binCenters(); });
}

//! Returns lower, upper range on y-axis occupied by all data points of all graphs.

QPair<double, double> QEXTMvvmGraphViewportItem::dataYAxisRange() const
{
    return get_min_max(visibleGraphItems(), [](QEXTMvvmGraphItem* graph) { return graph->binValues(); });
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmGraphViewPortItem.h>
#include <qextMvvmGraphItem.h>
#include <algorithm>
#include <vector>

using namespace ModelView;

namespace {

const double failback_min = 0.0;
const double failback_max = 1.0;

//! Find min and max values along all data points in all graphs.
//! Function 'func' is used to run either through binCenters or binValues.

template <typename T> std::pair<double, double> get_min_max(const std::vector<QExtMvvmGraphItem*>& graphs, T func)
{
    std::vector<double> values;
    for (auto graph : graphs) {
        const auto array = func(graph);
        std::copy(std::begin(array), std::end(array), std::back_inserter(values));
    }

    auto [xmin, xmax] = std::minmax_element(std::begin(values), std::end(values));
    return xmin != xmax ? std::make_pair(*xmin, *xmax) : std::make_pair(failback_min, failback_max);
}

} // namespace

QExtMvvmGraphViewportItem::QExtMvvmGraphViewportItem(const std::string& QExtMvvmModelType) : QExtMvvmViewportItem(QExtMvvmModelType)
{
    register_xy_axes();
    registerTag(QExtMvvmTagInfo::universalTag(T_ITEMS, {Constants::GraphItemType}), /*set_default*/ true);
}

//! Returns the selected graph items.

std::vector<QExtMvvmGraphItem*> QExtMvvmGraphViewportItem::graphItems() const
{
    return items<QExtMvvmGraphItem>(T_ITEMS);
}

//! Returns the selected graph items.

std::vector<QExtMvvmGraphItem*> QExtMvvmGraphViewportItem::visibleGraphItems() const
{
    std::vector<QExtMvvmGraphItem*> all_items = items<QExtMvvmGraphItem>(T_ITEMS);
    std::vector<QExtMvvmGraphItem*> visible_items;
    std::copy_if(all_items.begin(), all_items.end(), std::back_inserter(visible_items),
                 [](const QExtMvvmGraphItem* graph_item) {
                     return graph_item->property<bool>(QExtMvvmGraphItem::P_DISPLAYED);
                 });
    return visible_items;
}

//! Set the graph selection.

void QExtMvvmGraphViewportItem::setVisible(const std::vector<QExtMvvmGraphItem*>& visible_graph_items)
{
    std::vector<QExtMvvmGraphItem*> output;
    for (auto graph_item : items<QExtMvvmGraphItem>(T_ITEMS)) {
        if (std::find(visible_graph_items.begin(), visible_graph_items.end(), graph_item)
            != visible_graph_items.end())
            graph_item->setProperty(QExtMvvmGraphItem::P_DISPLAYED, true);
        else
            graph_item->setProperty(QExtMvvmGraphItem::P_DISPLAYED, false);
    }
}

//! Reset the graph selection.

void QExtMvvmGraphViewportItem::setAllVisible()
{
    for (auto graph_item : items<QExtMvvmGraphItem>(T_ITEMS))
        graph_item->setProperty(QExtMvvmGraphItem::P_DISPLAYED, true);
}

//! Returns lower, upper range on x-axis occupied by all data points of all graphs.

std::pair<double, double> QExtMvvmGraphViewportItem::data_xaxis_range() const
{
    return get_min_max(visibleGraphItems(), [](QExtMvvmGraphItem* graph) { return graph->binCenters(); });
}

//! Returns lower, upper range on y-axis occupied by all data points of all graphs.

std::pair<double, double> QExtMvvmGraphViewportItem::data_yaxis_range() const
{
    return get_min_max(visibleGraphItems(), [](QExtMvvmGraphItem* graph) { return graph->binValues(); });
}

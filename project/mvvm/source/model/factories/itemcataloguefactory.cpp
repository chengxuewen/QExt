// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/factories/itemcataloguefactory.h"
#include "model/standarditems/standarditemincludes.h"

using namespace ModelView;

std::unique_ptr<ItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<ColorMapItem>();
    result->registerItem<ColorMapViewportItem>();
    result->registerItem<CompoundItem>();
    result->registerItem<ContainerItem>();
    result->registerItem<Data1DItem>();
    result->registerItem<Data2DItem>();
    result->registerItem<FixedBinAxisItem>();
    result->registerItem<GraphItem>();
    result->registerItem<GraphViewportItem>();
    result->registerItem<LinkedItem>();
    result->registerItem<PenItem>();
    result->registerItem<PointwiseAxisItem>();
    result->registerItem<PropertyItem>();
    result->registerItem<SessionItem>();
    result->registerItem<TextItem>();
    result->registerItem<VectorItem>();
    result->registerItem<ViewportAxisItem>();
    return result;
}

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

QExtUniquePointer<QExtMvvmItemCatalogue> ModelView::qextMvvmCreateStandardItemCatalogue()
{
    auto result = qextMakeUnique<QExtMvvmItemCatalogue>();
    result->registerItem<QExtMvvmColorMapItem>();
    result->registerItem<QExtMvvmColorMapViewportItem>();
    result->registerItem<QExtMvvmCompoundItem>();
    result->registerItem<QExtMvvmContainerItem>();
    result->registerItem<QExtMvvmData1DItem>();
    result->registerItem<QExtMvvmData2DItem>();
    result->registerItem<QExtMvvmFixedBinAxisItem>();
    result->registerItem<QExtMvvmGraphItem>();
    result->registerItem<QExtMvvmGraphViewportItem>();
    result->registerItem<QExtMvvmLinkedItem>();
    result->registerItem<QExtMvvmPenItem>();
    result->registerItem<QExtMvvmPointwiseAxisItem>();
    result->registerItem<QExtMvvmPropertyItem>();
    result->registerItem<QExtMvvmSessionItem>();
    result->registerItem<QExtMvvmTextItem>();
    result->registerItem<QExtMvvmVectorItem>();
    result->registerItem<QExtMvvmViewportAxisItem>();
    return result;
}

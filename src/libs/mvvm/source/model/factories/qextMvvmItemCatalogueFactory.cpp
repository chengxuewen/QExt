#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmStandardItemIncludes.h>

using namespace ModelView;

std::unique_ptr<QEXTMvvmItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<QEXTMvvmItemCatalogue>();
    result->registerItem<QEXTMvvmColorMapItem>();
    result->registerItem<QEXTMvvmColorMapViewportItem>();
    result->registerItem<QEXTMvvmCompoundItem>();
    result->registerItem<QEXTMvvmContainerItem>();
    result->registerItem<QEXTMvvmData1DItem>();
    result->registerItem<QEXTMvvmData2DItem>();
    result->registerItem<QEXTMvvmFixedBinAxisItem>();
    result->registerItem<QEXTMvvmGraphItem>();
    result->registerItem<QEXTMvvmGraphViewportItem>();
    result->registerItem<QEXTMvvmLinkedItem>();
    result->registerItem<QEXTMvvmPenItem>();
    result->registerItem<QEXTMvvmPointwiseAxisItem>();
    result->registerItem<QEXTMvvmPropertyItem>();
    result->registerItem<QEXTMvvmSessionItem>();
    result->registerItem<QEXTMvvmTextItem>();
    result->registerItem<QEXTMvvmVectorItem>();
    result->registerItem<QEXTMvvmViewportAxisItem>();
    return result;
}

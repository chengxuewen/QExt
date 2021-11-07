// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include <qextMvvmItemCatalogue.h>



namespace
{
QEXTMvvmItemCatalogue *qextMvvmCreateItemCatalogue()
{
    QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
    result->registerItem<BeamItem>();
    result->registerItem<DistributionNoneItem>();
    result->registerItem<DistributionGaussianItem>();
    result->registerItem<DistributionLogNormalItem>();
    result->registerItem<DistributionTrapezoidItem>();
    result->registerItem<DistributionGroupItem>();
    return result;
}
} // namespace

SampleModel::SampleModel() : QEXTMvvmModel("SampleModel")
{
    setItemCatalogue(qextMvvmCreateItemCatalogue());
    init_model();
}

//! Provides initial model content.

void SampleModel::init_model()
{
    insertItem<BeamItem>();
    insertItem<DistributionGroupItem>();
}

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORCORE_CUSTOMLAYERROWSTRATEGY_H
#define LAYEREDITORCORE_CUSTOMLAYERROWSTRATEGY_H

#include "samplemodel.h"
#include "viewmodel/interfaces/rowstrategyinterface.h"
#include "viewmodel/viewmodel/standardviewitems.h"
#include "viewmodel/viewmodel/viewitem.h"
#include <QStringList>
#include <vector>

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public ModelView::RowStrategyInterface {
public:
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Type"
                             << "Nr."
                             << "Material"
                             << "Thickness";
    }

    std::vector<QExtUniquePointer<ModelView::ViewItem>> constructRow(ModelView::SessionItem* item)
    {
        std::vector<QExtUniquePointer<ModelView::ViewItem>> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        if (auto multilayer = dynamic_cast<MultiLayerItem*>(item)) {
            result.emplace_back(qextMakeUnique<ModelView::ViewLabelItem>(multilayer));
            result.emplace_back(qextMakeUnique<ModelView::ViewDataItem>(
                multilayer->getItem(MultiLayerItem::P_NREPETITIONS)));
            result.emplace_back(
                qextMakeUnique<ModelView::ViewEmptyItem>()); // instead of P_MATERIAL
            result.emplace_back(
                qextMakeUnique<ModelView::ViewEmptyItem>()); // instead of P_THICKNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        if (auto layer = dynamic_cast<LayerItem*>(item)) {
            result.emplace_back(qextMakeUnique<ModelView::ViewLabelItem>(layer));
            result.emplace_back(
                qextMakeUnique<ModelView::ViewEmptyItem>()); // instead of P_NREPETITIONS
            result.emplace_back(
                qextMakeUnique<ModelView::ViewDataItem>(layer->getItem(LayerItem::P_MATERIAL)));
            result.emplace_back(
                qextMakeUnique<ModelView::ViewDataItem>(layer->getItem(LayerItem::P_THICKNESS)));
        }

        return result;
    }
};

#endif // LAYEREDITORCORE_CUSTOMLAYERROWSTRATEGY_H

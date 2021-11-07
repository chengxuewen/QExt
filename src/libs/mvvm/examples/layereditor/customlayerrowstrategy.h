// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMLAYERROWSTRATEGY_H
#define CUSTOMLAYERROWSTRATEGY_H

#include <QStringList>
#include "samplemodel.h"
#include <qextMvvmRowStrategyInterface.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewItem.h>
#include <QVector>

//! Custom strategy to form table rows for nested multilayers and layers.

class CustomLayerRowStrategy : public QEXTMvvmRowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const
    {
        return QStringList() << "Type"
                             << "Nr."
                             << "Material"
                             << "Thickness";
    }

    QVector<QEXTMvvmViewItem *> constructRow(QEXTMvvmItem *item)
    {
        QVector<QEXTMvvmViewItem *> result;

        // multilayer row contains its name, repetion and placeholders (instead of material and
        // thickness)
        MultiLayerItem *multilayer = dynamic_cast<MultiLayerItem *>(item);
        if (multilayer) {
            result.append(new QEXTMvvmViewLabelItem(multilayer));
            result.append(new QEXTMvvmViewDataItem(multilayer->item(MultiLayerItem::P_NREPETITIONS)));
            result.append(new QEXTMvvmViewEmptyItem()); // instead of P_MATERIAL
            result.append(new QEXTMvvmViewEmptyItem()); // instead of P_THICKNESS
        }

        // layer row contains its name, placeholder for repetition, layer material and thickness
        LayerItem *layer = dynamic_cast<LayerItem *>(item);
        if (layer) {
            result.append(new QEXTMvvmViewLabelItem(layer));
            result.append(new QEXTMvvmViewEmptyItem()); // instead of P_NREPETITIONS
            result.append(new QEXTMvvmViewDataItem(layer->item(LayerItem::P_MATERIAL)));
            result.append(new QEXTMvvmViewDataItem(layer->item(LayerItem::P_THICKNESS)));
        }

        return result;
    }
};

#endif //  CUSTOMLAYERROWSTRATEGY_H

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTCOLORMAPCORE_COLORMAPMODEL_H
#define PLOTCOLORMAPCORE_COLORMAPMODEL_H

#include "model/model/sessionmodel.h"

namespace ModelView {
class QExtMvvmContainerItem;
}

namespace PlotColorMap {

//! Main application model to demonstrate how to plot data.

class ColorMapModel : public ModelView::QExtMvvmSessionModel {
public:
    ColorMapModel();

    void updateData(double scale);

private:
    ModelView::QExtMvvmContainerItem* dataContainer();
    void populateModel();
    void addColormap();
};

} // namespace PlotColorMap

#endif // PLOTCOLORMAPCORE_COLORMAPMODEL_H

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef COLORMAPMODEL_H
#define COLORMAPMODEL_H

#include <qextMvvmSessionModel.h>

namespace ModelView
{
class QEXTMvvmContainerItem;
}

namespace PlotColorMap
{

//! Main application model to demonstrate how to plot data.

class ColorMapModel : public ModelView::QEXTMvvmSessionModel
{
public:
    ColorMapModel();

    void update_data(double scale);

private:
    ModelView::QEXTMvvmContainerItem* data_container();
    void init_model();
    void add_colormap();
};

} // namespace PlotColorMap

#endif // COLORMAPMODEL_H

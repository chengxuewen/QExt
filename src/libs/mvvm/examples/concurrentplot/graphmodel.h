// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <qextMvvmSessionModel.h>

namespace ModelView
{
class QEXTMvvmGraphViewportItem;
class QEXTMvvmContainerItem;
} // namespace ModelView

//! Main application model holding data for single graph.
//! Contains few QEXTMvvmData1DItem's, QEXTMvvmGraphItem's and ViewPortItem.

class GraphModel : public ModelView::QEXTMvvmSessionModel
{
public:
    GraphModel();

    void set_data(const std::vector<double>& data);

private:
    void init_model();
    void add_graph(ModelView::QEXTMvvmContainerItem* container, ModelView::QEXTMvvmGraphViewportItem* viewport);
};

#endif // GRAPHMODEL_H

// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PLOTGRAPHSCORE_GRAPHMODEL_H
#define PLOTGRAPHSCORE_GRAPHMODEL_H

#include "model/model/sessionmodel.h"

namespace ModelView {
class QExtMvvmGraphViewportItem;
class QExtMvvmContainerItem;
} // namespace ModelView

namespace PlotGraphs {

//! Main application model to demonstrate how to plot data.
//! Contains few QExtMvvmData1DItem's, QExtMvvmGraphItem's and ViewPortItem. Provides functionality to easily
//! add and remove graphs.

class GraphModel : public ModelView::QExtMvvmSessionModel {
public:
    GraphModel();

    void addGraph();

    void removeGraph();

    void randomizeGraphs();

    void undo();

    void redo();

private:
    ModelView::QExtMvvmGraphViewportItem* viewport();
    ModelView::QExtMvvmContainerItem* dataContainer();

    void populateModel();
};

} // namespace PlotGraphs

#endif // PLOTGRAPHSCORE_GRAPHMODEL_H

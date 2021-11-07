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

#include <qextMvvmModel.h>


class QEXTMvvmGraphViewportItem;
class QEXTMvvmContainerItem;


namespace PlotGraphs
{

//! Main application model to demonstrate how to plot data.
//! Contains few QEXTMvvmData1DItem's, QEXTMvvmGraphItem's and ViewPortItem. Provides functionality to easily
//! add and remove graphs.

class GraphModel : public QEXTMvvmModel
{
public:
    GraphModel();

    void add_graph();

    void remove_graph();

    void randomize_graphs();

    void undo();

    void redo();

private:
    QEXTMvvmGraphViewportItem* viewport();
    QEXTMvvmContainerItem* data_container();

    void init_model();
};

} // namespace PlotGraphs

#endif // GRAPHMODEL_H

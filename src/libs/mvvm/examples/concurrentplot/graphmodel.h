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


//! Main application model holding data for single graph.
//! Contains few QEXTMvvmData1DItem's, QEXTMvvmGraphItem's and ViewPortItem.

class GraphModel : public QEXTMvvmModel
{
public:
    GraphModel();

    void set_data(const QVector<double>& data);

private:
    void init_model();
    void add_graph(QEXTMvvmContainerItem* container, QEXTMvvmGraphViewportItem* viewport);
};

#endif // GRAPHMODEL_H

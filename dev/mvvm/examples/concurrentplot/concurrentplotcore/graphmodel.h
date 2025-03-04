// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CONCURRENTPLOTCORE_GRAPHMODEL_H
#define CONCURRENTPLOTCORE_GRAPHMODEL_H

#include "model/model/sessionmodel.h"

namespace ModelView {
class QExtMvvmGraphViewportItem;
class QExtMvvmContainerItem;
} // namespace ModelView

//! Main application model holding data for single graph. Contains QExtMvvmData1DItem, QExtMvvmGraphItem and
//! ViewPortItem.

class GraphModel : public ModelView::QExtMvvmSessionModel {
public:
    GraphModel();

    void set_data(const std::vector<double>& data);

private:
    void init_model();
    void add_graph(ModelView::QExtMvvmContainerItem* container, ModelView::QExtMvvmGraphViewportItem* viewport);
};

#endif // CONCURRENTPLOTCORE_GRAPHMODEL_H

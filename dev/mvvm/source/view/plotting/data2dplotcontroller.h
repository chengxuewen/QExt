// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H
#define MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H

#include "model/signals/itemlistener.h"
#include <qextMvvmGlobal.h>
#include <memory>

class QCPColorMap;

namespace ModelView {

class QExtMvvmData2DItem;

//! Establish communication between QCPColorMap and QExtMvvmData2DItem.
//! Provide update of data points on QCPColorMap when Graph2DItem is changed.

class QEXT_MVVM_API QExtMvvmData2DPlotController : public QExtMvvmItemListener<QExtMvvmData2DItem> {
public:
    explicit QExtMvvmData2DPlotController(QCPColorMap* color_map);
    ~QExtMvvmData2DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data2DPlotControllerImpl;
    QExtUniquePointer<Data2DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_DATA2DPLOTCONTROLLER_H

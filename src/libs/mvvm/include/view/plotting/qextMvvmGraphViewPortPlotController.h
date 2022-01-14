#ifndef _QEXTMVVMPLOTTINGGRAPHVIEWPORTPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGGRAPHVIEWPORTPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmGraphViewportItem;

//! Establishes communications and mutual updates for GraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in GraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmGraphViewportItem>
{
public:
    explicit QEXTMvvmGraphViewportPlotController(QCustomPlot* plot);
    ~QEXTMvvmGraphViewportPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphViewportPlotControllerImpl;
    std::unique_ptr<GraphViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGGRAPHVIEWPORTPLOTCONTROLLER_H

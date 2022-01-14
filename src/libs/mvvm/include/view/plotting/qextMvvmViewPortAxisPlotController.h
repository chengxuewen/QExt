#ifndef _QEXTMVVMPLOTTINGVIEWPORTAXISPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGVIEWPORTAXISPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPAxis;

namespace ModelView
{

class QEXTMvvmViewportAxisItem;

//! Establishes communication between QCPAxis and ViewportAxisItem.
//! Provide mutual update of axis parameters (min, max, title) for two axes representations.

class QEXT_MVVM_API QEXTMvvmViewportAxisPlotController : public QEXTMvvmItemListener<QEXTMvvmViewportAxisItem>
{
public:
    explicit QEXTMvvmViewportAxisPlotController(QCPAxis* axis);
    ~QEXTMvvmViewportAxisPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

public:
    struct AxesPlotControllerImpl;
    std::unique_ptr<AxesPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGVIEWPORTAXISPLOTCONTROLLER_H

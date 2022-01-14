#ifndef _QEXTMVVMPLOTTINGCOLORSCALEPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGCOLORSCALEPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPColorScale;

namespace ModelView
{

class QEXTMvvmViewportAxisItem;

//! Establishes communication between QCPColorScale and ViewportAxisItem.

class QEXT_MVVM_API QEXTMvvmColorScalePlotController : public QEXTMvvmItemListener<QEXTMvvmViewportAxisItem>
{
public:
    explicit QEXTMvvmColorScalePlotController(QCPColorScale* color_scale);
    ~QEXTMvvmColorScalePlotController() override;

protected:
    void subscribe() override;

public:
    struct ColorScalePlotControllerImpl;
    std::unique_ptr<ColorScalePlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCOLORSCALEPLOTCONTROLLER_H

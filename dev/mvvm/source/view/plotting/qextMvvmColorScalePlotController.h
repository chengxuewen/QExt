// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORSCALEPLOTCONTROLLER_H
#define MVVM_PLOTTING_COLORSCALEPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>
#include <memory>

class QCPColorScale;

namespace ModelView {

class QExtMvvmViewportAxisItem;

//! Establishes communication between QCPColorScale and QExtMvvmViewportAxisItem.

class QEXT_MVVM_API QExtMvvmColorScalePlotController : public QExtMvvmItemListener<QExtMvvmViewportAxisItem> {
public:
    explicit QExtMvvmColorScalePlotController(QCPColorScale* color_scale);
    ~QExtMvvmColorScalePlotController() override;

protected:
    void subscribe() override;

public:
    struct ColorScalePlotControllerImpl;
    QExtUniquePointer<ColorScalePlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORSCALEPLOTCONTROLLER_H

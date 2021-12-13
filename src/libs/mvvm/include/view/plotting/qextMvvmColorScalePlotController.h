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

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCPColorScale;

namespace ModelView
{

class ViewportAxisItem;

//! Establishes communication between QCPColorScale and ViewportAxisItem.

class QEXT_MVVM_API ColorScalePlotController : public ItemListener<ViewportAxisItem>
{
public:
    explicit ColorScalePlotController(QCPColorScale* color_scale);
    ~ColorScalePlotController() override;

protected:
    void subscribe() override;

public:
    struct ColorScalePlotControllerImpl;
    std::unique_ptr<ColorScalePlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORSCALEPLOTCONTROLLER_H
